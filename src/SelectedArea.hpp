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
		Vector2<unsigned> _size;

	private:
		bool *_map;
		unsigned _nbPoints = 0;

	public:
		SelectedArea(const SelectedArea &);
		SelectedArea(unsigned width, unsigned height);
		SelectedArea(Vector2<unsigned> size, const bool *buffer = nullptr);
		~SelectedArea();

		void setSize(Vector2<unsigned> size);
		Vector2<unsigned int> getSize() const;
		//! @brief Clears the selected points
		void clear() noexcept;
		void selectAll() noexcept;
		void fill(Layer &layer, const Color &color);

		//! @brief Is _selectedPoints not empty ?
		//! @return bool The result of the verification
		bool isAnAreaSelected() const noexcept;
		std::vector<Vector2<int>> getPoints() const noexcept;

		void add(Vector2<int> point);
		void add(int x, int y);

		void invert() noexcept;

		bool pointInMap(Vector2<int> point) const;
		bool pointInMap(int x, int y) const;
	};
}


#endif //MYGIMP_SELECTEDAREA_HPP
