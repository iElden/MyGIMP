//
// Created by Gegel85 on 02/06/2020.
//

#include <cmath>
#include "SetRotation.hpp"
#include "../../Utils.hpp"

namespace Mimp
{
	SetRotation::SetRotation() :
		ImageOperation({"Layer", "Set rotation..."})
	{
	}

	void SetRotation::click(tgui::Gui &gui, CanvasWidget::Ptr image, tgui::ChildWindow::Ptr, Editor &) const
	{
		image->takeLayerSnapshot();
		Utils::makeSliderWindow(gui, [image](float value){
			image->getSelectedLayer().rotation = value;
		}, image->getSelectedLayer().rotation, -180, 180);
	}
}