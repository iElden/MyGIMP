/*
** EPITECH PROJECT, 2020
** MyGimp
** File description:
** SelectionTools.cpp
*/
#include "SelectionTool.hpp"

Mimp::SelectionTool::SelectionTool(const std::string &name, Mimp::Image &image):
	Tool(name),
	_image(image)
{}

void Mimp::SelectionTool::onSelect()
{
	this->_image.selectedArea.clear();
	this->clear();
}
