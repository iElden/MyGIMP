//
// Created by Gegel85 on 06/04/2020.
//

#include <stdexcept>
#include <fstream>
#include <cstring>
#include <SFML/Graphics.hpp>
#include <iostream>
#include <chrono>
#include <thread>
#include "LayerManager.hpp"
#include "../Exceptions.hpp"

namespace Mimp
{
	LayerManager::LayerManager(const std::string &path)
	{
		this->loadMimpImage(path);
	}

	LayerManager::LayerManager(Vector2<unsigned> size, unsigned int nbOfLayer, const Color &defaultColor) :
		_size(size)
	{
		this->_layers.reserve(nbOfLayer);
		if (!nbOfLayer)
			throw InvalidArgumentException("Must add at least a single layer");
		for (unsigned i = 0; i < nbOfLayer; i++) {
			auto &layer = this->_layers.emplace_back(new Layer{size, i == 0 ? defaultColor : Color::Transparent});

			sprintf(layer->name, "Layer %u", i);
		}
	}

	Layer &LayerManager::addLayer(const Layer &layer)
	{
		this->_setBusy();

		auto &lay = this->_layers.emplace_back(new Layer(layer));

#ifdef _WIN32
		sprintf(lay->name, "Layer %llu", this->_layers.size() - 1);
#else
		sprintf(lay->name, "Layer %lu", this->_layers.size() - 1);
#endif
		this->_unsetBusy();
		return *lay;
	}

	Layer &LayerManager::addLayer(Vector2<unsigned> size, const Color &defaultColor)
	{
		this->_setBusy();
		auto &layer = this->_layers.emplace_back(new Layer(size, defaultColor));
#ifdef _WIN32
		sprintf(layer->name, "Layer %llu", this->_layers.size() - 1);
#else
		sprintf(layer->name, "Layer %lu", this->_layers.size() - 1);
#endif
		this->_unsetBusy();
		return *layer;
	}

	Layer &LayerManager::operator[](unsigned int index)
	{
		return *this->_layers.at(index);
	}

	std::shared_ptr<Layer> &LayerManager::getLayerPtr(unsigned int index)
	{
		return this->_layers[index];
	}

	void LayerManager::render(FrameBuffer &buffer) const noexcept
	{
		this->_setBusy();
		for (auto &layer : this->_layers)
			if (layer->visible)
				buffer.drawFrameBuffer(layer->pos, layer->buffer, layer->rotation);
		this->_unsetBusy();
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
		this->_setBusy();
		if (this->_selectedLayer >= layer && this->_selectedLayer)
			this->_selectedLayer--;
		this->_layers.erase(this->_layers.begin() + layer);
		this->_unsetBusy();
	}

	void LayerManager::setLayerIndex(unsigned int layerOldIndex, unsigned int layerNewIndex)
	{
		if (layerOldIndex >= this->_layers.size() || layerNewIndex >= this->_layers.size())
			throw OutOfBoundException(
				"Cannot move layer " + std::to_string(layerOldIndex) +
				" to location " + std::to_string(layerNewIndex) +
				" because there are only " + std::to_string(this->_layers.size()) + " layers");

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

	void LayerManager::loadMimpImage(const std::string &path)
	{
		std::ifstream stream{path, std::ifstream::binary};

		if (stream.fail())
			throw InvalidImageException("Cannot open file " + path + ": " + strerror(errno));

		this->_setBusy();
		stream.seekg(0, std::ifstream::end);
		auto length = stream.tellg();
		char *buffer = new char[length];

		stream.seekg (0, std::ifstream::beg);
		stream.read(buffer, length);
		stream.close();

		try {
			if (static_cast<unsigned>(length) < sizeof(MimpImage))
				throw InvalidImageException("Unexpected end of file when parsing header.");

			auto image = reinterpret_cast<MimpImage *>(buffer);

			if (image->magic != LayerManager::MAGIC_NBR)
				throw InvalidImageException("Invalid magic number.");

			char *currentLayer = reinterpret_cast<char *>(&image->layers);
			std::vector<SavedLayer *> layers;

			this->_size = image->size;
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

				std::memcpy(createdLayer->name, layer->name, sizeof(createdLayer->name));
				createdLayer->visible = layer->attributes.visible;
				createdLayer->locked = layer->attributes.locked;
				createdLayer->pos = layer->pos;
				createdLayer->rotation = layer->rotation;
			}
		} catch (...) {
			this->_unsetBusy();
			delete[] buffer;
			throw;
		}

		this->_unsetBusy();
		delete[] buffer;
	}

	void LayerManager::importImageFromMemory(const std::string &data)
	{
		this->_setBusy();
		this->_layers.clear();
		this->_unsetBusy();
		this->addImageFromMemory(data);
	}

	void LayerManager::importImageFromFile(const std::string &path)
	{
		this->_setBusy();
		this->_layers.clear();
		this->_unsetBusy();
		this->addImageFromFile(path);
		this->_selectedLayer = 0;
	}

	void LayerManager::addImageFromFile(const std::string &path)
	{
		sf::Image image;

		if (!image.loadFromFile(path))
			throw InvalidImageException("Failed to load file " + path);

		this->_setBusy();

		Vector2<unsigned> size{
			image.getSize().x,
			image.getSize().y
		};
		auto pixelBuffer = new Color[size.x * size.y];

		this->_size = size;

		for (unsigned x = 0; x < size.x; x++)
			for (unsigned y = 0; y < size.y; y++)
				pixelBuffer[x + y * size.x] = Color{
					image.getPixel(x, y).r,
					image.getPixel(x, y).g,
					image.getPixel(x, y).b,
					image.getPixel(x, y).a
				};
		this->_unsetBusy();

		auto &layer = this->addLayer(Layer{size, pixelBuffer});

		delete[] pixelBuffer;
#ifdef _WIN32
		sprintf(layer.name, "Layer %llu", this->_layers.size() - 1);
#else
		sprintf(layer.name, "Layer %lu", this->_layers.size() - 1);
#endif
	}

	void LayerManager::addImageFromMemory(const std::string &data)
	{
		sf::Image image;

		if (!image.loadFromMemory(data.c_str(), data.size()))
			throw InvalidImageException("Failed to load image from memory");

		this->_setBusy();

		Vector2<unsigned> size{
			image.getSize().x,
			image.getSize().y
		};
		auto pixelBuffer = new Color[size.x * size.y];

		this->_size = size;

		for (unsigned x = 0; x < size.x; x++)
			for (unsigned y = 0; y < size.y; y++)
				pixelBuffer[x + y * size.x] = Color{
					image.getPixel(x, y).r,
					image.getPixel(x, y).g,
					image.getPixel(x, y).b,
					image.getPixel(x, y).a
				};
		this->_unsetBusy();

		auto &layer = this->addLayer(Layer{size, pixelBuffer});

		delete[] pixelBuffer;
#ifdef _WIN32
		sprintf(layer.name, "Layer %llu", this->_layers.size() - 1);
#else
		sprintf(layer.name, "Layer %lu", this->_layers.size() - 1);
#endif
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
		std::ofstream stream{path, std::ifstream::binary};

		if (stream.fail())
			throw;

		this->save(stream);
		stream.close();
	}

	void LayerManager::save(std::ostream &stream) const
	{
		this->_checkBusy();

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

			std::memcpy(layer->name, layerObject->name, sizeof(layer->name));
			layer->size = layerObject->getSize();
			layer->pos = layerObject->pos;
			layer->rotation = layerObject->rotation;
			layer->attributes.visible = layerObject->visible;
			layer->attributes.locked = layerObject->locked;

			std::memcpy(layer->pixels, layerObject->buffer->getBuffer(), layer->size.x * layer->size.y * sizeof(*layer->pixels));

			currentLayer = reinterpret_cast<char *>(&layer->pixels[layer->size.x * layer->size.y]);
		}

		stream.write(buffer, bufferSize);
		delete[] buffer;
	}

	void LayerManager::_setBusy() const
	{
		this->_checkBusy();
		this->_busy = true;
	}

	void LayerManager::_unsetBusy() const
	{
		this->_busy = false;
	}

	void LayerManager::_checkBusy() const
	{
		while (this->_busy)
			std::this_thread::sleep_for(std::chrono::milliseconds(1));
	}

	size_t LayerManager::size() const
	{
		return this->_layers.size();
	}

	std::vector<std::shared_ptr<Layer>>::const_iterator LayerManager::begin() const
	{
		return this->_layers.begin();
	}

	std::vector<std::shared_ptr<Layer>>::const_iterator LayerManager::end() const
	{
		return this->_layers.end();
	}

	unsigned LayerManager::getSelectedLayerIndex() noexcept
	{
		return this->_selectedLayer;
	}
}