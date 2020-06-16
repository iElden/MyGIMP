//
// Created by Gegel85 on 02/06/2020.
//

#include <cmath>
#include "Rotate.hpp"
#include "../../Utils.hpp"

namespace Mimp
{
	Rotate::Rotate() :
		ImageOperation({"Layer", "Rotate..."})
	{
	}

	void Rotate::click(tgui::Gui &gui, CanvasWidget::Ptr image, tgui::ChildWindow::Ptr, Editor &) const
	{
		image->takeLayerSnapshot();
		Utils::makeSliderWindow(gui, [image](float value){
			auto &layer = image->getSelectedLayer();

			layer.rotation = std::fmod(layer.rotation + value, 360);
		}, 0, -180, 180);
	}
}