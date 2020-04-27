/*
** EPITECH PROJECT, 2020
** MyGimp
** File description:
** InvertSelection.cpp
*/
#include <iostream>
#include "InvertSelection.hpp"

Mimp::InvertSelection::InvertSelection(Mimp::ToolBox &toolBox):
		SelectionTool("InvertSelection", toolBox)
{}

void Mimp::InvertSelection::onClick(Mimp::Vector2<int>, Mimp::MouseClick, Mimp::Image &image)
{
	this->_updateSelectedArea(image);
}

void Mimp::InvertSelection::_updateSelectedArea(Mimp::Image &image)
{
	image.selectedArea.invert();
}

tgui::ScrollablePanel::Ptr Mimp::InvertSelection::getParametersPanel() const
{
	return tgui::ScrollablePanel::create({0, 0});
}
