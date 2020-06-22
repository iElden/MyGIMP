#include "Lasso.hpp"

#include <iostream>

namespace Mimp {

	Lasso::Lasso(ToolBox &box) : SelectionTool("Lasso", box)
	{
		this->setKeyCombination({Keys::KEY_L, false, false, false});
	}

	void Lasso::onMouseDrag(Mimp::Vector2<float> oldPos, Mimp::Vector2<float> newPos, Mimp::MouseClick click,
				Mimp::Image &image)
	{
		if (click == MouseClick::MIMP_LEFT_CLICK) {
			image.selectedArea->addLine(oldPos.to<int>(), newPos.to<int>());
			this->_polygon.add(newPos.to<int>());
		}
	}

	void Lasso::onClick(Mimp::Vector2<float> pos, Mimp::MouseClick click, Mimp::Image &image)
	{
		if (click == MouseClick::MIMP_LEFT_CLICK) {
			image.takeSelectionSnapshot();
			image.selectedArea->add(pos.to<int>());
			image.selectedArea->clear();
			this->_polygon.clear();
		}
	}

	tgui::ScrollablePanel::Ptr Lasso::getParametersPanel()
	{
		return tgui::ScrollablePanel::create();
	}

	void Lasso::clear()
	{
		this->_polygon.reset();
	}

	void Lasso::onMouseRelease(Vector2<float>, MouseClick click, Image &image)
	{
		if (click == MouseClick::MIMP_LEFT_CLICK) {
			image.selectedArea->clear();
			this->_polygon.update([&image](Vector2<int> pt) { image.selectedArea->add(pt); });
		}
	}
}