#ifndef MYGIMP_LASSO_HPP
#define MYGIMP_LASSO_HPP

#include <TGUI/TGUI.hpp>
#include "SelectionTool.hpp"
#include "../ToolBox.hpp"
#include "Polygon.hpp"

namespace Mimp {
	class Lasso : public SelectionTool {
	public:

		Lasso(ToolBox &box);

		void onClick(Vector2<int> pos, MouseClick click, Image &image) override;

		void onMouseDrag(Vector2<int> oldPos, Vector2<int> newPos, MouseClick click, Image &image) override;

		tgui::ScrollablePanel::Ptr getParametersPanel() override;

		void clear() override;

	private:
		Polygon _polygon;
	};
}


#endif //MYGIMP_LASSO_HPP
