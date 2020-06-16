//
// Created by Gegel85 on 25/05/2020.
//

#include "MoveRight.hpp"

namespace Mimp
{
	MoveRight::MoveRight() :
		ImageOperation({"Layer", "Move Right"}, {Keys::KEY_RIGHT, false, false, false})
	{

	}

	void MoveRight::click(tgui::Gui &, CanvasWidget::Ptr image, tgui::ChildWindow::Ptr, Editor &) const
	{
		image->takeLayerSnapshot();
		image->getSelectedLayer().pos.x++;
	}
}