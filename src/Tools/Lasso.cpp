#include "Lasso.hpp"

#include <iostream>

namespace Mimp {

	Lasso::Lasso(ToolBox &box) : SelectionTool("Lasso", box)
	{
		this->setKeyCombination({Keys::KEY_L, false, false, false});
	}

	void Lasso::onMouseDrag(Vector2<int>, Vector2<int> newPos, MouseClick click, Image &)
	{
		if (click == MouseClick::MIMP_LEFT_CLICK)
			this->_polygon.add(newPos);
	}

	void Lasso::onClick(Vector2<int>, MouseClick click, Image &image)
	{
		if (click == MouseClick::MIMP_LEFT_CLICK) {
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

	void Lasso::onMouseRelease(Vector2<int>, MouseClick click, Image &image)
	{
		if (click == MouseClick::MIMP_LEFT_CLICK) {
			image.takeSelectionSnapshot();
			image.selectedArea->clear();
			this->_polygon.update([&image](Vector2<int> pt) { image.selectedArea->add(pt); });
		}
	}
}