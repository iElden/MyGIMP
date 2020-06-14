#include "PolygonSelection.hpp"

#include <iostream>

namespace Mimp {

	PolygonSelection::PolygonSelection(ToolBox &toolBox) : SelectionTool("Polygon Selection", toolBox)
	{
		this->setKeyCombination({Keys::KEY_P, true, false, false});
	}

	void PolygonSelection::onClick(Vector2<int> pos, MouseClick click, Image &image)
	{
		image.takeSelectionSnapshot();

		if (click == MouseClick::MIMP_LEFT_CLICK) this->_polygon.add(pos);
		if (click == MouseClick::MIMP_RIGHT_CLICK && !this->_polygon.empty()) this->_polygon.removeLast();

		this->_box->setText(std::to_string(this->_polygon.size()));
		image.selectedArea->clear();
		this->_polygon.update([&image](Vector2<int> pt) { image.selectedArea->add(pt); });
	}

	tgui::ScrollablePanel::Ptr PolygonSelection::getParametersPanel()
	{
		auto panel = tgui::ScrollablePanel::create();
		panel->loadWidgetsFromFile("widgets/tools_cfg/polyselect_cfg.gui");

		auto button = panel->get<tgui::Button>("Clear");
		this->_box = panel->get<tgui::EditBox>("Nb");

		button->connect("Pressed", [this] { this->clear(); });
		panel->add(button);

		return panel;
	}

	void PolygonSelection::clear()
	{
		this->_box->setText("0");
		this->_polygon.reset();
	}

	void PolygonSelection::onMouseDrag(Vector2<int>, Vector2<int>, MouseClick, Image &)
	{
	}
}
