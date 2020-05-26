//
// Created by Gegel85 on 25/05/2020.
//

#include "MoveDown.hpp"

namespace Mimp
{
	MoveDown::MoveDown() :
		ImageOperation({"Layer", "Move Down"},"Move Down", {Keys::KEY_DOWN, false, false, false})
	{

	}

	void MoveDown::click(tgui::Gui &, CanvasWidget::Ptr image, tgui::ChildWindow::Ptr, Editor &) const
	{
		image->getSelectedLayer().pos.y++;
	}
}