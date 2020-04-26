/*
** EPITECH PROJECT, 2020
** MyGimp
** File description:
** Image.cpp
*/
#include <SFML/Graphics/Image.hpp>
#include "Image.hpp"
#include "Exceptions.hpp"

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
		_layers(size),
		selectedArea(size)
	{}

	Image::Image(Vector2<unsigned> size, const LayerManager &layers):
		_size(size),
		_layers(layers),
		selectedArea(size)
	{
	}

	LayerManager &Image::getLayers() noexcept
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

	void Image::exportImage(const std::string &path) const
	{
		FrameBuffer buffer({
			static_cast<unsigned>(this->getImageSize().x),
			static_cast<unsigned>(this->getImageSize().y)
		});
		auto size = buffer.getSize();
		sf::Image image;
		auto pixelArray = new sf::Color[size.x * size.y];

		this->_layers.render(buffer);
		for (unsigned x = 0; x < size.x; x++)
			for (unsigned y = 0; y < size.y; y++)
				pixelArray[x + y * size.x] = buffer.getPixel({static_cast<int>(x), static_cast<int>(y)});

		image.create(size.x, size.y, reinterpret_cast<const sf::Uint8 *>(pixelArray));
		delete[] pixelArray;
		if (!image.saveToFile(path))
			throw ExportErrorException("Cannot export to file " + path);
	}
}