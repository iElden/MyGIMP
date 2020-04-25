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
		//! @brief All the points selected, building the selected area
		std::vector<Vector2<int>> _selectedPoints = {};
	public:
		SelectedArea() = default;
		//! @brief Clears the selected points
		void clear() noexcept;

		//! @brief Is _selectedPoints not empty ?
		//! @return bool The result of the verification
		bool isAnAreaSelected() const noexcept;

		void add(Vector2<int> point);
		void add(int x, int y);

		//! @brief Iterator begin for vectors of layers
		std::vector<Vector2<int>>::iterator begin();
		//! @brief Iterator end for vectors of layers
		std::vector<Vector2<int>>::iterator end();

		//! @brief Iterator begin for vectors of layers
		std::vector<Vector2<int>>::const_iterator begin() const;
		//! @brief Iterator end for vectors of layers
		std::vector<Vector2<int>>::const_iterator end() const;
	};
}


#endif //MYGIMP_SELECTEDAREA_HPP
