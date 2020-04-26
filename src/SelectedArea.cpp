/*
** EPITECH PROJECT, 2020
** MyGimp
** File description:
** SelectedArea.cpp
*/
#include "SelectedArea.hpp"

namespace Mimp
{
	void SelectedArea::clear() noexcept
	{
		this->_selectedPoints.clear();
	}

	bool SelectedArea::isAnAreaSelected() const noexcept
	{
		return !this->_selectedPoints.empty();
	}

	void SelectedArea::add(Vector2<int> point)
	{
		this->_selectedPoints.push_back(point);
	}

	void SelectedArea::add(int x, int y)
	{
		this->_selectedPoints.emplace_back(x, y);
	}

	std::vector<Vector2<int>>::iterator SelectedArea::begin()
	{
		return this->_selectedPoints.begin();
	}

	std::vector<Vector2<int>>::iterator SelectedArea::end()
	{
		return this->_selectedPoints.end();
	}

	std::vector<Vector2<int>>::const_iterator SelectedArea::begin() const
	{
		return this->_selectedPoints.begin();
	}

	std::vector<Vector2<int>>::const_iterator SelectedArea::end() const
	{
		return this->_selectedPoints.end();
	}

	std::vector<Vector2<int>> SelectedArea::copy() const noexcept
	{
		return this->_selectedPoints;
	}
}
