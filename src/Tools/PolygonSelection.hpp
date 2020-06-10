#ifndef MYGIMP_POLYGONSELECTION_HPP
#define MYGIMP_POLYGONSELECTION_HPP

#include <TGUI/TGUI.hpp>
#include "SelectionTool.hpp"
#include "../ToolBox.hpp"

namespace Mimp {
	class PolygonSelection : public SelectionTool {
	public:

		PolygonSelection(ToolBox &toolBox);

		void clear() override;

		void onMouseDrag(Vector2<int> oldPos, Vector2<int> newPos, MouseClick click, Image &image) override {};

		void onClick(Vector2<int> pos, MouseClick click, Image &image) override;

		tgui::ScrollablePanel::Ptr getParametersPanel() override;

	private:
		void _addVertex(Vector2<int> point);

		void _removeLastVertex();

		bool _isInside(Vector2<int> point);

	private:
		std::vector<Vector2<int>> _vertices;

		Vector2<int> _min = {INT32_MAX, INT32_MAX};
		Vector2<int> _max = {INT32_MIN, INT32_MIN};

		tgui::EditBox::Ptr _box;
	};
}


#endif //MYGIMP_POLYGONSELECTION_HPP
