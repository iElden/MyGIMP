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
{
	this->setKeyCombination({Keys::KEY_C, false, false, false});
}

void Mimp::ColorPick::onClick(Mimp::Vector2<float> pos, Mimp::MouseClick click, Mimp::Image &image)
{
	auto &layer = image.getSelectedLayer();
	Color color = layer.buffer->getPixel((pos - layer.pos).rotate(-layer.rotation, layer.getSize() / 2).to<int>());

	this->_toolBox.setSelectedColor(click, color);
}

void Mimp::ColorPick::onMouseDrag(Mimp::Vector2<float>, Mimp::Vector2<float> pos, Mimp::MouseClick click,
				  Mimp::Image &image)
{
	auto &layer = image.getSelectedLayer();
	Color color = layer.buffer->getPixel((pos - layer.pos).rotate(-layer.rotation, layer.getSize() / 2).to<int>());

	this->_toolBox.setSelectedColor(click, color);
}

tgui::ScrollablePanel::Ptr Mimp::ColorPick::getParametersPanel()
{
	return tgui::ScrollablePanel::create({0, 0});
}
