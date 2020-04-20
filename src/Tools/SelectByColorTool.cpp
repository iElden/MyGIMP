/*
** EPITECH PROJECT, 2020
** MyGimp
** File description:
** SelectByColorTool.cpp
*/
#include "SelectByColorTool.hpp"

Mimp::SelectByColorTool::SelectByColorTool(ToolBox &toolBox):
	SelectionTool("SelectByColor", toolBox)
{}

void Mimp::SelectByColorTool::onClick(Mimp::Vector2<int> pos, Mimp::MouseClick click, Mimp::Image &image)
{
	if (click == MouseClick::MIMP_LEFT_CLICK) {
		image.selectedArea.clear();
		this->_updateSelectedArea(image, image.getSelectedLayer().buffer.getPixel(pos));
	}
}

void Mimp::SelectByColorTool::_updateSelectedArea(Image &image, const Color &target_color)
{
	unsigned max_x = image.getSelectedLayer().getSize().x;
	unsigned max_y = image.getSelectedLayer().getSize().y;

	for (unsigned j = 0; j < max_y; j++)
		for (unsigned i = 0; i < max_x; i++)
			if (image.getSelectedLayer().buffer[j * max_x + i] == target_color)
				image.selectedArea.add(i, j);
}

tgui::ScrollablePanel::Ptr Mimp::SelectByColorTool::getParametersPanel() const
{
	return tgui::ScrollablePanel::create({0, 0});
}
