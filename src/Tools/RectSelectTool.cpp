/*
** EPITECH PROJECT, 2020
** MyGimp
** File description:
** RectSelectTool.cpp
*/

#include "RectSelectTool.hpp"

Mimp::RectSelectTool::RectSelectTool(ToolBox &toolBox):
	SelectionTool("RectSelect", toolBox)
{
	this->setKeyCombination({Keys::KEY_R, false, false, false});
}

void Mimp::RectSelectTool::clear()
{
	this->_state = 0;
}

void Mimp::RectSelectTool::onClick(Mimp::Vector2<int> pos, Mimp::MouseClick, Mimp::Image &image)
{
	this->_pt1 = pos;
	this->_pt2 = pos;
	this->_state = 1;
	this->_updateSelectedArea(image); // TODO: Add onMouseRelease event for optimisation
}

void Mimp::RectSelectTool::onMouseDrag(Mimp::Vector2<int>, Mimp::Vector2<int> newPos, Mimp::MouseClick, Mimp::Image &image)
{
	this->_pt2 = newPos;
	this->_state = 2;
	this->_updateSelectedArea(image); // TODO: Add onMouseRelease event for optimisation
}

void Mimp::RectSelectTool::_updateSelectedArea(Image &image)
{
	int min_x = std::min(this->_pt1.x, this->_pt2.x);
	int max_x = std::max(this->_pt1.x, this->_pt2.x);
	int min_y = std::min(this->_pt1.y, this->_pt2.y);
	int max_y = std::max(this->_pt1.y, this->_pt2.y);

	image.selectedArea.clear();
	for (int j = min_y; j <= max_y; j++)
		for (int i = min_x; i <= max_x; i++)
			image.selectedArea.add(i, j);
}

tgui::ScrollablePanel::Ptr Mimp::RectSelectTool::getParametersPanel()
{
	return tgui::ScrollablePanel::create({0, 0});
}
