#ifndef MYGIMP_FINGER_HPP
#define MYGIMP_FINGER_HPP

#include "SelectionTool.hpp"

namespace Mimp {
	class Finger : public SelectionTool {
	public:
		Finger(ToolBox &box);
		void onMouseDrag(Vector2<int> oldPos, Vector2<int> newPos, MouseClick click, Image &image) override;
		void onClick(Vector2<int> pos, MouseClick click, Image &image) override;
		tgui::ScrollablePanel::Ptr getParametersPanel() override;

	private:
		int _radius = 5;

		void _apply(Vector2<int> pos, Image &image);
	};
}

#endif //MYGIMP_FINGER_HPP
