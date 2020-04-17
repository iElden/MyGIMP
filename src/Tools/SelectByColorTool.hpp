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
		void _updateSelectedArea(const Color &target_color);

	public:
		SelectByColorTool(Image &image);
		void onMouseDrag(Vector2<int>, Vector2<int>, MouseClick, Layer &) override {};
		void onClick(Vector2<int> pos, MouseClick click, Layer &layer) override;
		tgui::ScrollablePanel::Ptr getParametersPanel() const override;
	};
}


#endif //MYGIMP_SELECTBYCOLORTOOL_HPP
