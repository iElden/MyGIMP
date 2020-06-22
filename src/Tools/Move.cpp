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

	void Move::onMouseDrag(Mimp::Vector2<float> oldPos, Mimp::Vector2<float> newPos, Mimp::MouseClick, Mimp::Image &image)
	{
		image.getSelectedLayer().pos -= oldPos.to<int>() - newPos.to<int>();
	}

	void Move::onClick(Mimp::Vector2<float>, Mimp::MouseClick, Mimp::Image &image)
	{
		image.takeLayerSnapshot();
	}

	tgui::ScrollablePanel::Ptr Move::getParametersPanel()
	{
		return tgui::ScrollablePanel::create({0, 0});
	}
}
