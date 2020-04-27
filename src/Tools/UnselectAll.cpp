/*
** EPITECH PROJECT, 2020
** MyGimp
** File description:
** UnselectAll.cpp
*/
#include "UnselectAll.hpp"

Mimp::UnselectAll::UnselectAll(Mimp::ToolBox &toolBox):
		SelectionTool("UnselectAll", toolBox)
{}

void Mimp::UnselectAll::onClick(Mimp::Vector2<int>, Mimp::MouseClick, Mimp::Image &image)
{
	this->_updateSelectedArea(image);
}

void Mimp::UnselectAll::_updateSelectedArea(Mimp::Image &image)
{
	image.selectedArea.clear();
}

tgui::ScrollablePanel::Ptr Mimp::UnselectAll::getParametersPanel() const
{
	return tgui::ScrollablePanel::create({0, 0});
}
