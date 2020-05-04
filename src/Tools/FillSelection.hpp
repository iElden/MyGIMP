/*
** EPITECH PROJECT, 2020
** MyGimp
** File description:
** FillSelection.hpp
*/
#ifndef MYGIMP_FILLSELECTION_HPP
#define MYGIMP_FILLSELECTION_HPP

#include "Tool.hpp"
#include "../ToolBox.hpp"

namespace Mimp {
	class FillSelection : public Tool {
	private:
		ToolBox &_toolBox;
	public:
		FillSelection(ToolBox &);
		void onMouseDrag(Vector2<int>, Vector2<int>, MouseClick, Image &) override {};
		void onClick(Vector2<int> pos, MouseClick click, Image &image) override;
		tgui::ScrollablePanel::Ptr getParametersPanel() override;
	};
}


#endif //MYGIMP_FILLSELECTION_HPP
