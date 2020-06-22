#ifndef MYGIMP_FINGER_HPP
#define MYGIMP_FINGER_HPP

#include "SelectionTool.hpp"

namespace Mimp {
	class Finger : public SelectionTool {
	public:
		Finger(ToolBox &box);
		void onMouseDrag(Mimp::Vector2<float> oldPos, Mimp::Vector2<float> newPos, Mimp::MouseClick click,
				 Mimp::Image &image) override;
		void onClick(Mimp::Vector2<float> pos, Mimp::MouseClick click, Mimp::Image &image) override;
		tgui::ScrollablePanel::Ptr getParametersPanel() override;

	private:
		int _radius = 5;

		void _apply(Vector2<int> pos, Image &image);
	};
}

#endif //MYGIMP_FINGER_HPP
