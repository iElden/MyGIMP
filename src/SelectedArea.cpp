/*
** EPITECH PROJECT, 2020
** MyGimp
** File description:
** SelectedArea.cpp
*/
#include <cstring>
#include "SelectedArea.hpp"

namespace Mimp
{
	SelectedArea::SelectedArea(unsigned width, unsigned height) :
		SelectedArea(Vector2<unsigned>{width, height})
	{
	}

	SelectedArea::SelectedArea(Vector2<unsigned> size) :
		_size(size),
		_map(new bool[size.x * size.y])
	{
		this->clear();
	}

	SelectedArea::~SelectedArea()
	{
		delete[] this->_map;
	}

	void SelectedArea::clear() noexcept
	{
		std::memset(this->_map, 0, this->_size.x * this->_size.y);
	}

	bool SelectedArea::isAnAreaSelected() const noexcept
	{
		return this->_nbPoints;
	}

	void SelectedArea::add(Vector2<int> point)
	{
		this->add(point.x, point.y);
	}

	void SelectedArea::add(int x, int y)
	{
		if (x < 0)
			return;
		if (y < 0)
			return;
		if (static_cast<unsigned>(x) >= this->_size.x)
			return;
		if (static_cast<unsigned>(y) >= this->_size.y)
			return;

		auto &val = this->_map[x + y * this->_size.x];

		this->_nbPoints += !val;
		this->_modified |= !val;
		val = true;
	}

	std::vector<Vector2<int>>::iterator SelectedArea::begin()
	{
		this->_generatePointArray();
		return this->_selectedPoints.begin();
	}

	std::vector<Vector2<int>>::iterator SelectedArea::end()
	{
		this->_generatePointArray();
		return this->_selectedPoints.end();
	}

	std::vector<Vector2<int>>::const_iterator SelectedArea::begin() const
	{
		this->_generatePointArray();
		return this->_selectedPoints.begin();
	}

	std::vector<Vector2<int>>::const_iterator SelectedArea::end() const
	{
		this->_generatePointArray();
		return this->_selectedPoints.end();
	}

	std::vector<Vector2<int>> SelectedArea::copy() const noexcept
	{
		this->_generatePointArray();
		return this->_selectedPoints;
	}

	void SelectedArea::_generatePointArray() const noexcept
	{
		if (!this->_modified)
			return;

		int index = 0;

		this->_selectedPoints.clear();
		this->_selectedPoints.reserve(this->_nbPoints);
		for (unsigned y = 0; y < this->_size.y; y++)
			for (unsigned x = 0; x < this->_size.x; x++)
				if (this->_map[index++])
					this->_selectedPoints.emplace_back(x, y);
	}

	void SelectedArea::invert() noexcept
	{
		int index = 0;

		this->_modified = true;
		this->_nbPoints = this->_size.x * this->_size.y - this->_nbPoints;
		for (unsigned y = 0; y < this->_size.y; y++)
			for (unsigned x = 0; x < this->_size.x; x++) {
				this->_map[index] = !this->_map[index];
				index++;
			}
	}
}
