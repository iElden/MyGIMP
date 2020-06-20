#ifndef MYGIMP_POLYGONSELECTION_HPP
#define MYGIMP_POLYGONSELECTION_HPP

#include <TGUI/TGUI.hpp>
#include "SelectionTool.hpp"
#include "../ToolBox.hpp"
#include "Polygon.hpp"

namespace Mimp {
	class PolygonSelection : public SelectionTool {
	public:
		PolygonSelection(ToolBox &toolBox);
		void clear() override;
		void onMouseDrag(Vector2<int>, Vector2<int>, MouseClick, Image &) override {};
		void onClick(Vector2<int> pos, MouseClick click, Image &image) override;
		tgui::ScrollablePanel::Ptr getParametersPanel() override;

	private:
		tgui::EditBox::Ptr _box;
		Polygon _polygon;
	};
}


#endif //MYGIMP_POLYGONSELECTION_HPP
