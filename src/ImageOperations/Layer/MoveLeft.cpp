//
// Created by Gegel85 on 25/05/2020.
//

#include "MoveLeft.hpp"

namespace Mimp
{
	MoveLeft::MoveLeft() :
		ImageOperation({"Layer", "Move Left"}, {KEY_LEFT, false, false, false})
	{

	}

	void MoveLeft::click(tgui::Gui &, CanvasWidget::Ptr image, tgui::ChildWindow::Ptr, Editor &) const
	{
		image->getSelectedLayer().pos.x--;
	}
}