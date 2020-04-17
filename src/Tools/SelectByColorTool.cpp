/*
** EPITECH PROJECT, 2020
** MyGimp
** File description:
** SelectByColorTool.cpp
*/
#include "SelectByColorTool.hpp"

Mimp::SelectByColorTool::SelectByColorTool(Mimp::Image &image):
	SelectionTool("SelectByColor", image)
{}

void Mimp::SelectByColorTool::onClick(Mimp::Vector2<int> pos, Mimp::MouseClick click, Mimp::Layer &layer)
{
	if (click == MouseClick::MIMP_LEFT_CLICK) {
		this->_image.selectedArea.clear();
		this->_updateSelectedArea(layer.buffer.getPixel(pos));
	}
}

void Mimp::SelectByColorTool::_updateSelectedArea(const Color &target_color)
{
	unsigned max_x = this->_image.getSelectedLayer().getSize().x;
	unsigned max_y = this->_image.getSelectedLayer().getSize().y;

	for (unsigned j = 0; j < max_y; j++)
		for (unsigned i = 0; i < max_x; i++)
			if (this->_image.getSelectedLayer().buffer[j * max_x + i] == target_color)
				this->_image.selectedArea.add(i, j);
}

tgui::ScrollablePanel::Ptr Mimp::SelectByColorTool::getParametersPanel() const
{
	return tgui::ScrollablePanel::create({0, 0});
}
