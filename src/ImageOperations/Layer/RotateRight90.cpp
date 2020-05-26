//
// Created by Gegel85 on 25/05/2020.
//

#include <cmath>
#include "RotateRight90.hpp"

namespace Mimp
{
	RotateRight90::RotateRight90() :
		ImageOperation({"Layer", "Rotate 90° Right"},"Rotate 90° Right", {Keys::KEY_RIGHT, true, false, false})
	{

	}

	void RotateRight90::click(tgui::Gui &, CanvasWidget::Ptr image, tgui::ChildWindow::Ptr, Editor &) const
	{
		image->getSelectedLayer().rotation = std::fmod(image->getSelectedLayer().rotation + 90, 360);
	}
}