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
	protected:
		Vector2<unsigned> _size;
		LayerManager _layers;
	public:
		SelectedArea selectedArea;

		Image(Vector2<unsigned> size);
		Image(Vector2<unsigned> size, const LayerManager &layers);
		Layer &getSelectedLayer() noexcept;
		const Layer &getSelectedLayer() const noexcept;
		LayerManager &getLayers();
		void exportImage(const std::string &path) const;
		const LayerManager &getLayers() const noexcept;
		Vector2<unsigned> getImageSize() const noexcept;
	};
}


#endif //MYGIMP_IMAGE_HPP
