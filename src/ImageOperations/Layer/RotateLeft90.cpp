//
// Created by Gegel85 on 25/05/2020.
//

#include <cmath>
#include "RotateLeft90.hpp"

namespace Mimp
{
	RotateLeft90::RotateLeft90() :
		ImageOperation({"Layer", "Rotate 90° Left"})
	{
	}

	void RotateLeft90::click(tgui::Gui &, CanvasWidget::Ptr image, tgui::ChildWindow::Ptr, Editor &) const
	{
		image->takeLayerSnapshot();
		image->getSelectedLayer().rotation = std::fmod(image->getSelectedLayer().rotation - 90 + 360, 360);
	}
}