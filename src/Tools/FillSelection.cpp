/*
** EPITECH PROJECT, 2020
** MyGimp
** File description:
** FillSelection.cpp
*/
#include "FillSelection.hpp"

Mimp::FillSelection::FillSelection(Mimp::ToolBox &toolBox):
	Tool("FillSelection"),
	_toolBox(toolBox)
{
	this->setKeyCombination({Keys::KEY_F, false, false, true});
}

void Mimp::FillSelection::onClick(Mimp::Vector2<int>, Mimp::MouseClick click, Mimp::Image &image)
{
	if (image.getSelectedLayer().isLocked())
		return;

	auto &layer = image.getSelectedLayer();

	if (image.selectedArea.isAnAreaSelected())
		for (Vector2<int> pt : image.selectedArea.getPoints())
			layer.buffer.drawPixel(pt, this->_toolBox.getSelectedColor(click));
}

tgui::ScrollablePanel::Ptr Mimp::FillSelection::getParametersPanel()
{
	return tgui::ScrollablePanel::create({0, 0});
}
