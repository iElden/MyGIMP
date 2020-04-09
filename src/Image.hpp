/*
** EPITECH PROJECT, 2020
** MyGimp
** File description:
** Image.hpp
*/
#ifndef MYGIMP_IMAGE_HPP
#define MYGIMP_IMAGE_HPP

#include "Layer/LayerManager.hpp"
#include "SelectedArea.hpp"

namespace Mimp {
	class Image {
	public:
		LayerManager layers;
		SelectedArea selectedArea;

		Layer &getSelectedLayer() noexcept;
		const Layer &getSelectedLayer() const noexcept;
	};
}


#endif //MYGIMP_IMAGE_HPP
