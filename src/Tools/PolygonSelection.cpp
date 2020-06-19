#include "PolygonSelection.hpp"

#include <iostream>

namespace Mimp {

	PolygonSelection::PolygonSelection(ToolBox &toolBox) : SelectionTool("Polygon Selection", toolBox)
	{
		this->setKeyCombination({Keys::KEY_P, true, false, false});
	}

	void PolygonSelection::onClick(Vector2<int> pos, MouseClick click, Image &image)
	{
		if (click == MouseClick::MIMP_LEFT_CLICK) {
			image.selectedArea->clear();
			this->_polygon.reset();
			this->_polygon.add(pos);
			this->_polygon.update([&image](Vector2<int> pt) { image.selectedArea->add(pt); });
		}
		if (click == MouseClick::MIMP_RIGHT_CLICK) {
			image.selectedArea->clear();
			this->_polygon.add(pos);
			this->_polygon.update([&image](Vector2<int> pt) { image.selectedArea->add(pt); });
		}
	}

	tgui::ScrollablePanel::Ptr PolygonSelection::getParametersPanel()
	{
		auto panel = tgui::ScrollablePanel::create();

		std::string content;
		content += "Left click : Create a new selection and set start point.\n";
		content += "Right click : Add point to the selection.\n";
		content += "Note : Undo/Redo affect the Left click only,\nnot the Right click.";
		auto hint = tgui::Label::create(content);

		panel->add(hint);
		return panel;
	}

	void PolygonSelection::clear()
	{
		this->_polygon.reset();
	}
}
