//
// Created by Gegel85 on 25/04/2020.
//

#include <TGUI/TGUI.hpp>
#include "FillSelectionOperation.hpp"
#include "../../Utils.hpp"

namespace Mimp
{
	FillSelectionOperation::FillSelectionOperation() :
		ImageOperation({"Selection", "Fill area"})
	{
	}

	void FillSelectionOperation::click(tgui::Gui &gui, CanvasWidget::Ptr image, tgui::ChildWindow::Ptr, Editor &) const
	{
		Utils::makeColorPickWindow(gui, [image](Color color){
			image->takeFrameBufferSnapshot();
			image->selectedArea->fill(image->getSelectedLayer(), color);
		}, Color::Black);
	}
}