/*
** EPITECH PROJECT, 2020
** MyGimp
** File description:
** Eraser.cpp
*/

#include "Eraser.hpp"

namespace Mimp
{
	Eraser::Eraser(ToolBox &box) :
			Tool("Eraser"),
			_box(box)
	{
	}

	void Eraser::onMouseDrag(Vector2<int> oldPos, Vector2<int> newPos, MouseClick, Image &image)
	{
		if (image.getSelectedLayer().isLocked())
			return;
		image.getSelectedLayer().buffer.drawLine(oldPos, newPos, Color::Transparent);
	}

	void Eraser::onClick(Vector2<int> pos, MouseClick, Image &image)
	{
		if (image.getSelectedLayer().isLocked())
			return;
		image.getSelectedLayer().buffer.drawPixel(pos, Color::Transparent);
	}

	tgui::ScrollablePanel::Ptr Eraser::getParametersPanel() const
	{
		return tgui::ScrollablePanel::create({0, 0});
	}
}