#include "Lasso.hpp"

#include <iostream>

namespace Mimp {

	Lasso::Lasso(ToolBox &box) : SelectionTool("Lasso", box)
	{
		this->setKeyCombination({Keys::KEY_L, false, false, false});
	}

	void Lasso::onMouseDrag(Vector2<int>, Vector2<int> newPos, MouseClick click, Image &image)
	{
		if (click == MouseClick::MIMP_LEFT_CLICK) {
			image.selectedArea->add(newPos);
			this->_polygon.add(newPos);
		}
	}

	void Lasso::onClick(Vector2<int>, MouseClick click, Image &image)
	{
		image.takeSelectionSnapshot();

		if (click == MouseClick::MIMP_RIGHT_CLICK) {
			image.selectedArea->clear();
			this->_polygon.update([&image](Vector2<int> pt) { image.selectedArea->add(pt); });
		}
	}

	tgui::ScrollablePanel::Ptr Lasso::getParametersPanel()
	{
		auto panel = tgui::ScrollablePanel::create();
		panel->loadWidgetsFromFile("widgets/tools_cfg/lasso_cfg.gui");

		auto button = panel->get<tgui::Button>("Clear");

		button->connect("Pressed", [this] { this->clear(); });
		panel->add(button);

		return panel;
	}

	void Lasso::clear()
	{
		this->_polygon.reset();
	}
}