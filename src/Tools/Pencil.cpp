//
// Created by Gegel85 on 07/04/2020.
//

#include "Pencil.hpp"

namespace Mimp
{
	Pencil::Pencil(ToolBox &box) :
		Tool("Pencil"),
		_box(box)
	{
	}

	void Pencil::onMouseDrag(Vector2<int> oldPos, Vector2<int> newPos, MouseClick click, Image &image)
	{
		if (image.getSelectedLayer().isLocked())
			return;
		image.getSelectedLayer().buffer.drawLine(oldPos, newPos, this->_box.getSelectedColor(click), this->_radius, this->_shape);
	}

	void Pencil::onClick(Vector2<int> pos, MouseClick click, Image &image)
	{
		if (image.getSelectedLayer().isLocked())
			return;
		image.getSelectedLayer().buffer.drawAt(pos, this->_box.getSelectedColor(click), this->_radius, this->_shape);
	}

	tgui::ScrollablePanel::Ptr Pencil::getParametersPanel() const
	{
		return tgui::ScrollablePanel::create({0, 0});
	}
}