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
	class SelectedArea {
	public:
		std::vector<Vector2<int>> _selectedPoints = {};
		Layer *selectedLayer = nullptr; // TODO: Gérer le fait que la layer puisse être supprimé !

		SelectedArea() = default;
		void clear();
	};
}


#endif //MYGIMP_SELECTEDAREA_HPP
