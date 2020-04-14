/*
** EPITECH PROJECT, 2020
** MyGimp
** File description:
** SelectedArea.hpp
*/
#ifndef MYGIMP_SELECTEDAREA_HPP
#define MYGIMP_SELECTEDAREA_HPP


#include <vector>
#include "Data/Vector2.hpp"
#include "Layer/Layer.hpp"

namespace Mimp {
	//! @brief Class Selected Area
	class SelectedArea {
	public:
		//! @brief All the points selected, building the selected area
		std::vector<Vector2<int>> _selectedPoints = {};
		//! @brief The Selected Layer
		Layer *selectedLayer = nullptr; // TODO: Gérer le fait que la layer puisse être supprimé !

		SelectedArea() = default;
		//! @brief Clears the selected points
		void clear();
	};
}


#endif //MYGIMP_SELECTEDAREA_HPP
