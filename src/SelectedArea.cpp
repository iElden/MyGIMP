/*
** EPITECH PROJECT, 2020
** MyGimp
** File description:
** SelectedArea.cpp
*/
#include "SelectedArea.hpp"

void Mimp::SelectedArea::clear() noexcept
{
	this->_selectedPoints.clear();
	this->selectedLayer = nullptr;
}

bool Mimp::SelectedArea::isAnAreaSelected() const noexcept
{
	return !this->_selectedPoints.empty();
}

void Mimp::SelectedArea::add(Mimp::Vector2<int> point)
{
	this->_selectedPoints.push_back(point);
}

void Mimp::SelectedArea::add(int x, int y)
{
	this->_selectedPoints.emplace_back(x, y);
}

std::vector<Mimp::Vector2<int>, std::allocator<Mimp::Vector2<int>>>::iterator Mimp::SelectedArea::begin()
{
	return this->_selectedPoints.begin();
}

std::vector<Mimp::Vector2<int>, std::allocator<Mimp::Vector2<int>>>::iterator Mimp::SelectedArea::end()
{
	return this->_selectedPoints.end();
}

std::vector<Mimp::Vector2<int>> Mimp::SelectedArea::copy() const noexcept
{
	return this->_selectedPoints;
}
