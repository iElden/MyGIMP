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
		image->takeFrameBufferSnapshot();
		Utils::makeColorPickWindow(gui, [image](Color color){
			FillSelectionOperation::_fill(image->getSelectedLayer(), *image->selectedArea, color);
		}, Color::Black);
	}

	void FillSelectionOperation::_fill(Layer &layer, const SelectedArea &area, const Color &color)
	{
		if (area.isAnAreaSelected())
			for (const auto &pt : area.getPoints())
				layer.buffer->setPixel(pt, color);
	}
}