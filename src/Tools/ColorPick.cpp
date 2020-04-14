/*
** EPITECH PROJECT, 2020
** MyGimp
** File description:
** ColorPick.cpp
*/
#include "ColorPick.hpp"

Mimp::ColorPick::ColorPick(Mimp::ToolBox &toolBox):
	Tool("ColorPick"),
	_toolBox(toolBox)
{}

void Mimp::ColorPick::onClick(Mimp::Vector2<int> pos, Mimp::MouseClick click, Mimp::Layer &layer)
{
	Color color = layer.buffer.getPixel(pos);
	_toolBox.setSelectedColor(click, color);
}


void Mimp::ColorPick::onMouseDrag(Mimp::Vector2<int>, Mimp::Vector2<int>, Mimp::MouseClick, Mimp::Layer &)
{}

tgui::ScrollablePanel::Ptr Mimp::ColorPick::getParametersPanel() const
{
	return tgui::ScrollablePanel::Ptr();
}
