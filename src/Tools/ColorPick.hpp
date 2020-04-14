/*
** EPITECH PROJECT, 2020
** MyGimp
** File description:
** ColorPick.hpp
*/
#ifndef MYGIMP_COLORPICK_HPP
#define MYGIMP_COLORPICK_HPP

#include "Tool.hpp"
#include "../ToolBox.hpp"

namespace Mimp {
	class ColorPick : public Tool {
	private:
		ToolBox &_toolBox;
	public:
		ColorPick(ToolBox &toolBox);
		void onClick(Vector2<int> pos, MouseClick click, Layer &layer) override;
		void onMouseDrag(Vector2<int>, Vector2<int>, MouseClick, Layer &) override;
		tgui::ScrollablePanel::Ptr getParametersPanel() const override;
	};
}


#endif //MYGIMP_COLORPICK_HPP
