/*
** EPITECH PROJECT, 2020
** MyGimp
** File description:
** Fill.cpp
*/
#include "Fill.hpp"

Mimp::Fill::Fill(Mimp::ToolBox &toolBox):
		Tool("Fill color"),
		_box(toolBox)
{}

void Mimp::Fill::onClick(Mimp::Vector2<int> pos, Mimp::MouseClick click, Mimp::Image &image)
{
	this->apply(pos, image.getSelectedLayer(), click);
}

void Mimp::Fill::onMouseDrag(Mimp::Vector2<int>, Mimp::Vector2<int> newPos, Mimp::MouseClick click,
							 Mimp::Image &image)
{
	this->apply(newPos, image.getSelectedLayer(), click);
}

void Mimp::Fill::apply(Mimp::Vector2<int> pos, Mimp::Layer &layer, MouseClick &click)
{
	if (layer.buffer.posIsOutOfBound(pos))
		return;
	auto target_color = layer.buffer.getPixel(pos);
	auto fill_color = this->_box.getSelectedColor(click);
	if (fill_color == target_color)
		return;
	this->_spread_color(pos, layer, target_color, fill_color);
}

void Mimp::Fill::_spread_color(Vector2<int> pos, Layer &layer, Color target_color, Color fill_color)
{
	std::vector<Vector2<int>> spread_pos = {{-1,0}, {0,-1}, {1,0}, {0,1}};
	std::vector<Vector2<int>> points = {pos};
	std::vector<Vector2<int>> new_points;

	layer.buffer.drawPixel(pos, fill_color);
	while (!points.empty()) {
		new_points.clear();
		for (auto pt : points)
			for (auto sp : spread_pos) {
				auto new_pos = pt + sp;
				if (!layer.buffer.posIsOutOfBound(new_pos) && layer.buffer.getPixel(new_pos) == target_color) {
					layer.buffer.drawPixel(new_pos, fill_color);
					new_points.push_back(new_pos);
				}
			}
		points = new_points;
	}
}

tgui::ScrollablePanel::Ptr Mimp::Fill::getParametersPanel() const
{
	return tgui::ScrollablePanel::create({0, 0});
}

