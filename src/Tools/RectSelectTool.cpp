/*
** EPITECH PROJECT, 2020
** MyGimp
** File description:
** RectSelectTool.cpp
*/

#include <cmath>
#include <TGUI/TGUI.hpp>
#include "RectSelectTool.hpp"
#include "../Utils.hpp"

Mimp::RectSelectTool::RectSelectTool(ToolBox &toolBox) :
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
	image.takeSelectionSnapshot();
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

	image.selectedArea->clear();
	for (int j = min_y; j < max_y; j++) {
		for (int i = min_x; i < max_x; i++) {
			image.selectedArea->add(i, j);
		}
	}

	int radius = std::min(max_x - min_x, max_y - min_y) / 2 * (this->_percentage / 100);

	if (!radius)
		return;

	for (int j = 0; j <= radius; j++) {
		for (int i = 0; i <= radius; i++) {
			if (!Mimp::Utils::point_in_ellipse(i, j, radius, radius)) {
				image.selectedArea->remove(min_x - i + radius, min_y - j + radius); // Upper-left corner
				image.selectedArea->remove(max_x + i - radius, min_y - j + radius); // Upper-right corner
				image.selectedArea->remove(min_x - i + radius, max_y + j - radius); // Lower-left corner
				image.selectedArea->remove(max_x + i - radius, max_y + j - radius); // Lower-right corner
			}
		}
	}

}

tgui::ScrollablePanel::Ptr Mimp::RectSelectTool::getParametersPanel()
{
	auto panel = tgui::ScrollablePanel::create();

	panel->loadWidgetsFromFile("widgets/tools_cfg/rect_cfg.gui");

	auto borderRadiusSlider = panel->get<tgui::Slider>("BorderRadiusSlider");
	auto borderRadiusPreview = panel->get<tgui::TextBox>("BorderRadiusPreview");

	borderRadiusPreview->setText(std::to_string(static_cast<int>(this->_percentage)));
	borderRadiusSlider->setValue(this->_percentage);

	borderRadiusSlider->connect("ValueChanged", [borderRadiusPreview, this, borderRadiusSlider] {
		this->_percentage = borderRadiusSlider->getValue();
		borderRadiusPreview->setText(std::to_string(static_cast<int>(this->_percentage)));
	});
	return panel;
}