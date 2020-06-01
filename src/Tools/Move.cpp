//
// Created by Gegel85 on 24/05/2020.
//

#include "Move.hpp"

namespace Mimp
{
	Move::Move() :
		Tool("Move Layer")
	{
        this->setKeyCombination({Keys::KEY_M, false, false, false});
    }

	void Move::onMouseDrag(Vector2<int> oldPos, Vector2<int> newPos, MouseClick, Image &image)
	{
		image.getSelectedLayer().pos -= oldPos - newPos;
	}

	void Move::onClick(Vector2<int>, MouseClick, Image &)
	{

	}

	tgui::ScrollablePanel::Ptr Move::getParametersPanel()
	{
		return tgui::ScrollablePanel::create({0, 0});
	}
}
