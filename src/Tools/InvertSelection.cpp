/*
** EPITECH PROJECT, 2020
** MyGimp
** File description:
** InvertSelection.cpp
*/
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
	std::vector<Vector2<int>> oldSelected = image.selectedArea.copy();

	image.selectedArea.clear();
	for (int j = 0; j <= static_cast<int>(image.getImageSize().y); j++) {
		for (int i = 0; i <= static_cast<int>(image.getImageSize().x); i++) {
			Vector2<int> pt = {i, j};
			if (find(oldSelected.begin(), oldSelected.end(), pt) != oldSelected.end())
				image.selectedArea.add(pt);
		}
	}
}

tgui::ScrollablePanel::Ptr Mimp::InvertSelection::getParametersPanel() const
{
	return tgui::ScrollablePanel::create({0, 0});
}
