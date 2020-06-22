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
		void onClick(Mimp::Vector2<float> pos, Mimp::MouseClick click, Mimp::Image &image) override;
		void onMouseDrag(Mimp::Vector2<float> oldPos, Mimp::Vector2<float> newPos, Mimp::MouseClick click,
				 Mimp::Image &image) override;

		void onMouseRelease(Vector2<float> vector2, MouseClick click, Image &image) override;

		tgui::ScrollablePanel::Ptr getParametersPanel() override;
		void clear() override;

	private:
		Polygon _polygon;
	};
}


#endif //MYGIMP_LASSO_HPP
