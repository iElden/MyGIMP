//
// Created by Gegel85 on 06/04/2020.
//

#ifndef MYGIMP_TOOL_HPP
#define MYGIMP_TOOL_HPP


#include <TGUI/Widgets/ScrollablePanel.hpp>
#include "../Layer/Layer.hpp"
#include "../Data/MouseClick.hpp"

namespace Mimp
{
	class Tool {
	public:
		virtual void onSelect(Layer &) {};
		virtual void onUnselect(Layer &) {};
		virtual void onMouseDrag(Vector2<int> oldPos, Vector2<int> newPos, MouseClick click, Layer &layer) = 0;
		virtual void onClick(Vector2<int> pos, MouseClick click, Layer &layer) = 0;
		virtual tgui::ScrollablePanel::Ptr getParametersPanel() const = 0;
	};
}


#endif //MYGIMP_TOOL_HPP
