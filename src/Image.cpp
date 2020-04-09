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
		return this->layers.getSelectedLayer();
	}

	const Layer &Image::getSelectedLayer() const noexcept
	{
		return this->layers.getSelectedLayer();
	}
}