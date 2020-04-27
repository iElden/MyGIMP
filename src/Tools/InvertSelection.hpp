/*
** EPITECH PROJECT, 2020
** MyGimp
** File description:
** InvertSelection.hpp
*/
#ifndef MYGIMP_INVERTSELECTION_HPP
#define MYGIMP_INVERTSELECTION_HPP


#include "SelectionTool.hpp"

namespace Mimp {
	class InvertSelection : public SelectionTool {
	private:
		void _updateSelectedArea(Image &image);

	public:
		InvertSelection(ToolBox &toolBox);
		void clear() override {};
		void onMouseDrag(Vector2<int>, Vector2<int>, MouseClick, Image &) override {};
		void onSelect() override {};
		void onClick(Vector2<int> pos, MouseClick click, Image &image) override;
		tgui::ScrollablePanel::Ptr getParametersPanel() const override;
	};
}


#endif //MYGIMP_INVERTSELECTION_HPP
