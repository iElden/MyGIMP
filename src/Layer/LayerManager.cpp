//
// Created by Gegel85 on 06/04/2020.
//

#include <stdexcept>
#include <fstream>
#include <cstring>
#include <SFML/Graphics.hpp>
#include <iostream>
#include "LayerManager.hpp"
#include "../Exceptions.hpp"

namespace Mimp
{
	LayerManager::LayerManager(const std::string &path)
	{
		try {
			this->_loadClassicalImage(path);
		} catch (std::exception &) {
			this->_loadMimpImage(path);
		}
	}

	LayerManager::LayerManager(Vector2<unsigned> size, unsigned int nbOfLayer, const Color &defaultColor)
	{
		this->_layers.reserve(nbOfLayer);
		if (!nbOfLayer)
			throw InvalidArgumentException("Must add at least a single layer");
		while (nbOfLayer--)
			this->_layers.emplace_back(new Layer{size, defaultColor});
	}

	void LayerManager::addLayer(const Layer &layer)
	{
		this->_layers.emplace_back(new Layer(layer));
	}

	void LayerManager::addLayer(Vector2<unsigned> size, const Color &defaultColor)
	{
		this->_layers.emplace_back(new Layer(size, defaultColor));
	}

	Layer &LayerManager::operator[](unsigned int index)
	{
		return *this->_layers.at(index);
	}

	void LayerManager::render(FrameBuffer &buffer) const noexcept
	{
		for (auto &layer : this->_layers)
			if (layer->visible)
				buffer.drawFrameBuffer(layer->pos, layer->buffer);
	}

	Layer &LayerManager::selectLayer(unsigned int layer)
	{
		if (layer >= this->_layers.size())
			throw InvalidArgumentException(
				"Cannot select layer " + std::to_string(layer) + " because there are only " + std::to_string(this->_layers.size()) + " layers."
			);
		this->_selectedLayer = layer;
		return *this->_layers[layer];
	}

	Layer &LayerManager::getSelectedLayer() noexcept
	{
		return *this->_layers[this->_selectedLayer];
	}

	const Layer &LayerManager::getSelectedLayer() const noexcept
	{
		return *this->_layers[this->_selectedLayer];
	}

	void LayerManager::deleteLayer(unsigned int layer)
	{
		if (layer >= this->_layers.size())
			throw OutOfBoundException("Cannot delete layer " + std::to_string(layer) + " because there are only " + std::to_string(this->_layers.size()) + " layers.");
		if (this->_layers.size() == 1)
			throw InvalidArgumentException("Cannot delete layer because there are only a single layer.");
		if (this->_selectedLayer >= layer)
			this->_selectedLayer--;
		this->_layers.erase(this->_layers.begin() + layer);
	}

	void LayerManager::setLayerIndex(unsigned int layerOldIndex, unsigned int layerNewIndex)
	{
		if (layerOldIndex >= this->_layers.size() || layerNewIndex >= this->_layers.size())
			throw OutOfBoundException(
				"Cannot move layer " + std::to_string(layerOldIndex) +
				" to location " + std::to_string(layerNewIndex) +
				" because there are only " + std::to_string(this->_layers.size()) + "layers");

		auto layerIt = this->_layers.begin() + layerOldIndex;
		auto layer = *layerIt;

		this->_layers.erase(layerIt);
		this->_layers.insert(this->_layers.begin() + layerNewIndex, layer);
	}

	std::vector<std::shared_ptr<Layer>>::iterator LayerManager::begin()
	{
		return this->_layers.begin();
	}

	std::vector<std::shared_ptr<Layer>>::iterator LayerManager::end()
	{
		return this->_layers.end();
	}

	bool LayerManager::isValidMimpImage(std::istream &stream)
	{
		unsigned magic = 0;

		stream.seekg(0, std::istream::beg);
		stream.read(reinterpret_cast<char *>(&magic), sizeof(magic));
		return magic == LayerManager::MAGIC_NBR;
	}

	void LayerManager::_loadMimpImage(const std::string &path)
	{
		this->_layers.clear();
		std::ifstream stream{path};

		if (stream.fail())
			throw InvalidImageException("Cannot open file " + path + ": " + strerror(errno));

		stream.seekg (0, std::ifstream::end);
		auto length = stream.tellg();
		char *buffer = new char[length];

		stream.seekg (0, std::ifstream::beg);
		stream.read(buffer, length);
		stream.close();

		if (static_cast<unsigned>(length) < sizeof(MimpImage))
			throw InvalidImageException("Unexpected end of file when parsing header.");

		auto image = reinterpret_cast<MimpImage *>(buffer);

		try {
			if (image->magic != LayerManager::MAGIC_NBR)
				throw InvalidImageException("Invalid magic number.");

			char *currentLayer = reinterpret_cast<char *>(&image->layers);
			std::vector<SavedLayer *> layers;

			layers.reserve(image->nbLayers);
			for (unsigned i = 0; i < image->nbLayers; i++) {
				auto layer = reinterpret_cast<SavedLayer *>(currentLayer);

				if (reinterpret_cast<uintptr_t>(&layer->pixels[layer->size.x * layer->size.y]) > reinterpret_cast<uintptr_t>(&buffer[length]))
					throw InvalidImageException("Unexpected end of file when parsing layer " + std::to_string(layers.size()));

				layers.push_back(layer);
				currentLayer = reinterpret_cast<char *>(&layer->pixels[layer->size.x * layer->size.y]);
			}

			for (auto layer : layers) {
				auto &createdLayer = this->_layers.emplace_back(new Layer{layer->size, layer->pixels});

				createdLayer->visible = layer->attributes.visible;
				createdLayer->locked = layer->attributes.locked;
				createdLayer->pos = layer->pos;
			}
		} catch (...) {
			delete[] buffer;
			throw;
		}

		delete[] buffer;
	}

	void LayerManager::_loadClassicalImage(const std::string &path)
	{
		this->_layers.clear();
		sf::Image image;

		if (!image.loadFromFile(path))
			throw InvalidImageException("Failed to load file " + path);

		Vector2<unsigned> size{
			image.getSize().x,
			image.getSize().y
		};
		auto pixelBuffer = new unsigned[size.x * size.y];

		for (unsigned x = 0; x < size.x; x++)
			for (unsigned y = 0; y < size.y; y++)
				pixelBuffer[x + y * size.x] = Color{
					image.getPixel(x, y).r,
					image.getPixel(x, y).g,
					image.getPixel(x, y).b,
					image.getPixel(x, y).a
				};
		this->_layers.emplace_back(new Layer{size, pixelBuffer});
		delete[] pixelBuffer;
	}

	Vector2<unsigned> LayerManager::getSize() const
	{
		return this->_size;
	}

	void LayerManager::setSize(const Vector2<unsigned> &size)
	{
		this->_size = size;
	}

	void LayerManager::save(const std::string &path) const
	{
		std::ofstream stream{path};

		if (stream.fail())
			throw;

		this->save(stream);
		stream.close();
	}

	void LayerManager::save(std::ostream &stream) const
	{
		size_t bufferSize = sizeof(MimpImage);

		for (auto &layer : this->_layers)
			bufferSize += sizeof(SavedLayer) + sizeof(*SavedLayer::pixels) * layer->getSize().x * layer->getSize().y;

		char *buffer = new char[bufferSize];
		auto image = reinterpret_cast<MimpImage *>(buffer);

		image->magic = LayerManager::MAGIC_NBR;
		image->size = this->_size;
		image->nbLayers = this->_layers.size();

		char *currentLayer = reinterpret_cast<char *>(&image->layers);

		for (auto &layerObject : this->_layers) {
			auto layer = reinterpret_cast<SavedLayer *>(currentLayer);

			layer->size = layerObject->getSize();
			layer->pos = layerObject->pos;
			layer->attributes.visible = layerObject->visible;
			layer->attributes.locked = layerObject->locked;

			std::memcpy(layer->pixels, layerObject->buffer.getBuffer(), layer->size.x * layer->size.y);

			currentLayer = reinterpret_cast<char *>(&layer->pixels[layer->size.x * layer->size.y]);
		}

		stream.write(buffer, bufferSize);
		delete[] buffer;
	}
}