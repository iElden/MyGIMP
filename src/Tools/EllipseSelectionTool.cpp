/*
** EPITECH PROJECT, 2020
** MyGimp
** File description:
** EllipseSelectionTool.cpp
*/
#include <cmath>
#include "EllipseSelectionTool.hpp"

Mimp::EllipseSelectionTool::EllipseSelectionTool(Mimp::ToolBox &toolBox):
	SelectionTool("Elipse Selection", toolBox)
{
	this->clear();
}

void Mimp::EllipseSelectionTool::clear()
{
	this->_pt1 = {-1, -1};
	this->_pt2 = {-1, -1};
	this->_state = 0;
}

void Mimp::EllipseSelectionTool::onClick(Mimp::Vector2<int> pos, Mimp::MouseClick, Mimp::Image &image)
{
	this->_pt1 = pos;
	this->_pt2 = pos;
	this->_state = 1;
	this->_updateSelectedArea(image); // TODO: Add onMouseRelease event for optimisation
}

void Mimp::EllipseSelectionTool::onMouseDrag(Mimp::Vector2<int>, Mimp::Vector2<int> newPos, Mimp::MouseClick,
                                             Mimp::Image &image)
{
	this->_pt2 = newPos;
	this->_state = 2;
	this->_updateSelectedArea(image); // TODO: Add onMouseRelease event for optimisation
}

tgui::ScrollablePanel::Ptr Mimp::EllipseSelectionTool::getParametersPanel()
{
	return tgui::ScrollablePanel::create({0, 0});
}

void Mimp::EllipseSelectionTool::_updateSelectedArea(Mimp::Image &image)
{
	image.selectedArea.clear();

	Vector2<int> center = {(this->_pt1.x + this->_pt2.x) / 2, (this->_pt1.y + this->_pt2.y) / 2};
	int min_x = std::min(this->_pt1.x, this->_pt2.x);
	int min_y = std::min(this->_pt1.y, this->_pt2.y);
	int max_x = std::max(this->_pt1.x, this->_pt2.x);
	int max_y = std::max(this->_pt1.y, this->_pt2.y);
	int rx = center.x - min_x;
	int ry = center.y - min_y;
	for (int j = min_y; j < max_y; j++)
		for (int i = min_x; i < max_x; i++)
			if (this->point_in_ellipse(i - center.x, j - center.y, rx, ry))
				image.selectedArea.add(i, j);
}

bool Mimp::EllipseSelectionTool::point_in_ellipse(int x, int y, int rx, int ry)
{
	return std::pow(x, 2) / std::pow(rx, 2) + std::pow(y, 2) / std::pow(ry, 2) <= 1;
}
