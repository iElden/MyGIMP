//
// Created by Gegel85 on 25/05/2020.
//

#include "MoveUp.hpp"

namespace Mimp
{
	MoveUp::MoveUp() :
		ImageOperation({"Layer", "Move Up"}, {Keys::KEY_UP, false, false, false})
	{

	}

	void MoveUp::click(tgui::Gui &, CanvasWidget::Ptr image, tgui::ChildWindow::Ptr, Editor &) const
	{
		image->getSelectedLayer().pos.y--;
	}
}