#include "PolygonSelection.hpp"

#include <iostream>

namespace Mimp {

	PolygonSelection::PolygonSelection(ToolBox &toolBox) : SelectionTool("Polygon Selection", toolBox)
	{
		this->setKeyCombination({Keys::KEY_P, true, false, false});
	}

	void PolygonSelection::_addVertex(Vector2<int> point)
	{
		this->_min.x = std::min(this->_min.x, point.x);
		this->_min.y = std::min(this->_min.y, point.y);
		this->_max.x = std::max(this->_max.x, point.x);
		this->_max.y = std::max(this->_max.y, point.y);
		this->_vertices.push_back(point);
	}

	void PolygonSelection::_removeLastVertex()
	{
		this->_vertices.pop_back();
		this->_min = {INT32_MAX, INT32_MAX};
		this->_max = {INT32_MIN, INT32_MIN};
		if (!this->_vertices.empty()) {
			for (auto &v : _vertices) {
				this->_min.x = std::min(this->_min.x, v.x);
				this->_min.y = std::min(this->_min.y, v.y);
				this->_max.x = std::max(this->_max.x, v.x);
				this->_max.y = std::max(this->_max.y, v.y);
			}
		}
	}

	void PolygonSelection::onClick(Vector2<int> pos, MouseClick click, Image &image)
	{
		if (click == MouseClick::MIMP_LEFT_CLICK) {
			this->_addVertex(pos);
		}
		if (click == MouseClick::MIMP_RIGHT_CLICK && !this->_vertices.empty()) {
			this->_removeLastVertex();
		}
		this->_box->setText(std::to_string(this->_vertices.size()));

		image.selectedArea.clear();

		if (this->_vertices.empty())
			return;
		for (int x = this->_min.x; x < this->_max.x; x += 1) {
			for (int y = this->_min.y; y < this->_max.y; y += 1) {
				if (this->_isInside({x, y}))
					image.selectedArea.add(x, y);
			}
		}

	}

	// http://www.eecs.umich.edu/courses/eecs380/HANDOUTS/PROJ2/InsidePoly.html
	bool PolygonSelection::_isInside(Vector2<int> pt)
	{
		bool isInside = false;
		auto v = this->_vertices;

		for (unsigned int i = 0, j = v.size() - 1; i < v.size(); j = i, i++) {
			if ((((pt.y > v.at(i).y) && (pt.y < v.at(j).y)) || ((pt.y > v.at(j).y) && (pt.y < v.at(i).y))) &&
			    (pt.x < ((v.at(j).x - v.at(i).x) * (pt.y - v.at(i).y) / (v.at(j).y - v.at(i).y) + v.at(i).x)))
				isInside = !isInside;
		}

		return isInside;
	}

	tgui::ScrollablePanel::Ptr PolygonSelection::getParametersPanel()
	{
		auto panel = tgui::ScrollablePanel::create();

		panel->loadWidgetsFromFile("widgets/tools_cfg/polyselect_cfg.gui");
		this->_box = panel->get<tgui::EditBox>("Nb");
		auto button = panel->get<tgui::Button>("Clear");

		button->connect("Pressed", [this] {
			this->clear();
		});

		panel->add(button);
		return panel;
	}

	void PolygonSelection::clear()
	{
		this->_vertices.clear();
		this->_box->setText("0");
		this->_min = {INT32_MAX, INT32_MAX};
		this->_max = {INT32_MIN, INT32_MIN};
	}
}
