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
