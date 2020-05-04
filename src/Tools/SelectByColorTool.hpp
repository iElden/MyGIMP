/*
** EPITECH PROJECT, 2020
** MyGimp
** File description:
** SelectByColorTool.hpp
*/
#ifndef MYGIMP_SELECTBYCOLORTOOL_HPP
#define MYGIMP_SELECTBYCOLORTOOL_HPP

#include "SelectionTool.hpp"

namespace Mimp {
	class SelectByColorTool : public SelectionTool {
	private:
		void _updateSelectedArea(Image &image, const Color &target_color);

	public:
		SelectByColorTool(ToolBox &toolBox);
		void onMouseDrag(Vector2<int>, Vector2<int>, MouseClick, Image &) override {};
		void onClick(Vector2<int> pos, MouseClick click, Image &layer) override;
		tgui::ScrollablePanel::Ptr getParametersPanel() override;
	};
}


#endif //MYGIMP_SELECTBYCOLORTOOL_HPP
