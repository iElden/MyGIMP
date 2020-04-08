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

void Mimp::Fill::onClick(Mimp::Vector2<int> pos, Mimp::MouseClick click, Mimp::Layer &layer)
{
	this->apply(pos, layer, click);
}

void Mimp::Fill::onMouseDrag(Mimp::Vector2<int>, Mimp::Vector2<int> newPos, Mimp::MouseClick click,
							 Mimp::Layer &layer)
{
	this->apply(newPos, layer, click);
}

void Mimp::Fill::apply(Mimp::Vector2<int> pos, Mimp::Layer &layer, MouseClick &click)
{
	if (layer.buffer.posIsOutOfBound(pos))
		return;
	this->_target_color = layer.buffer.getPixel(pos);
	this->_fill_color = this->_box.getSelectedColor(click);
	this->_target_layer = &layer;
	if (this->_fill_color == this->_target_color)
		return;
	this->_spread_color(pos);
}

void Mimp::Fill::_spread_color(Mimp::Vector2<int> pos)
{
	if (this->_target_layer->buffer.posIsOutOfBound(pos))
		return;
	if (this->_target_layer->buffer.getPixel(pos) != this->_target_color)
		return;
	this->_target_layer->buffer.drawPixel(pos, this->_fill_color);
	this->_spread_color(pos - Vector2<int>{1,0});
	this->_spread_color(pos - Vector2<int>{0,1});
	this->_spread_color(pos + Vector2<int>{1,0});
	this->_spread_color(pos + Vector2<int>{0,1});
}

tgui::ScrollablePanel::Ptr Mimp::Fill::getParametersPanel() const
{
	return tgui::ScrollablePanel::create({0, 0});
}

