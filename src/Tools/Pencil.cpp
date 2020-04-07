//
// Created by Gegel85 on 07/04/2020.
//

#include "Pencil.hpp"

namespace Mimp
{
	Pencil::Pencil(ToolBox &box) :
		_box(box)
	{
	}

	void Pencil::onMouseDrag(Vector2<int> oldPos, Vector2<int> newPos, MouseClick click, Layer &layer) const
	{
		if (layer.isLocked())
			return;
		layer.buffer.drawLine(oldPos, newPos, this->_box.getSelectedColor(click));
	}

	void Pencil::onClick(Vector2<int> pos, MouseClick click, Layer &layer) const
	{
		this->onMouseDrag(pos, click, layer);
	}

	tgui::ScrollablePanel::Ptr Pencil::getParametersPanel() const
	{
		return tgui::ScrollablePanel::create({0, 0});
	}
}