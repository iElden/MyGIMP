#include "PolygonSelection.hpp"

#include <iostream>

namespace Mimp {

	PolygonSelection::PolygonSelection(ToolBox &toolBox) : SelectionTool("Polygon Selection", toolBox)
	{
		this->setKeyCombination({Keys::KEY_P, true, false, false});
	}

	void PolygonSelection::onClick(Mimp::Vector2<float> pos, Mimp::MouseClick click, Mimp::Image &image)
	{
		if (click == MouseClick::MIMP_LEFT_CLICK) {
			auto v = this->_map.find(&image);
			if (v == this->_map.end()) {
				image.selectedArea->clear();
				this->_map.insert(std::pair<Image *, Polygon>(&image, Polygon()));
				this->_map.at(&image).add(pos.to<int>());
				this->_map.at(&image).update([&image](Vector2<int> pt) { image.selectedArea->add(pt); });
			} else {
				image.selectedArea->clear();
				v->second.add(pos.to<int>());
				v->second.update([&image](Vector2<int> pt) { image.selectedArea->add(pt); });
			}
		}
		if (click == MouseClick::MIMP_RIGHT_CLICK) {
			auto v = this->_map.find(&image);
			if (v != this->_map.end()) {
				image.selectedArea->clear();
				v->second.removeLast();
				v->second.update([&image](Vector2<int> pt) { image.selectedArea->add(pt); });
			}
		}
	}

	tgui::ScrollablePanel::Ptr PolygonSelection::getParametersPanel()
	{
		auto panel = tgui::ScrollablePanel::create();

		std::string content;
		content += "Left click : Add a point to the selection.\n";
		content += "Right click : Remove the last point.\n";
		content += "Note : Undo/Redo don't work with this tool.\nUse mouse clicks instead.";
		auto hint = tgui::Label::create(content);

		panel->add(hint);
		return panel;
	}

	void PolygonSelection::clear()
	{
		for (auto &m : this->_map) {
			m.second.clear();
		}
		this->_map.clear();
	}

}
