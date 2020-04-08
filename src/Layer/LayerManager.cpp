//
// Created by Gegel85 on 06/04/2020.
//

#include <stdexcept>
#include "LayerManager.hpp"
#include "../Exceptions.hpp"

namespace Mimp
{
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
}