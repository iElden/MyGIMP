/*
** EPITECH PROJECT, 2020
** MyGimp
** File description:
** SelectAll.cpp
*/
#include "SelectAll.hpp"

Mimp::SelectAll::SelectAll(Mimp::ToolBox &toolBox):
	SelectionTool("SelectAll", toolBox)
{}

void Mimp::SelectAll::onClick(Mimp::Vector2<int>, Mimp::MouseClick, Mimp::Image &image)
{
	this->_updateSelectedArea(image);
}

void Mimp::SelectAll::_updateSelectedArea(Mimp::Image &image)
{
	image.selectedArea.fill();
}

tgui::ScrollablePanel::Ptr Mimp::SelectAll::getParametersPanel() const
{
	return tgui::ScrollablePanel::create({0, 0});
}
