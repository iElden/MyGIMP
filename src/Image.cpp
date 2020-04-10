/*
** EPITECH PROJECT, 2020
** MyGimp
** File description:
** Image.cpp
*/
#include "Image.hpp"

namespace Mimp {
	Layer &Image::getSelectedLayer() noexcept
	{
		return this->_layers.getSelectedLayer();
	}

	const Layer &Image::getSelectedLayer() const noexcept
	{
		return this->_layers.getSelectedLayer();
	}

	Image::Image(Vector2<unsigned> size):
		_size(size),
		_layers(size)
	{}

	Image::Image(Vector2<unsigned> size, const LayerManager &layers):
		_size(size),
		_layers(layers)
	{
	}

	LayerManager &Image::getLayers()
	{
		return this->_layers;
	}

	const LayerManager &Image::getLayers() const noexcept
	{
		return this->_layers;
	}

	Vector2<unsigned> Image::getImageSize() const noexcept
	{
		return this->_size;
	}
}