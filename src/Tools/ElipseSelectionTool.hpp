/*
** EPITECH PROJECT, 2020
** MyGimp
** File description:
** ElipseSelectionTool.hpp
*/
#ifndef MYGIMP_ELIPSESELECTIONTOOL_HPP
#define MYGIMP_ELIPSESELECTIONTOOL_HPP


#include "SelectionTool.hpp"

namespace Mimp {
	class ElipseSelectionTool : public SelectionTool {
	private:
		int _state;
		Vector2<int> _pt1;
		Vector2<int> _pt2;

		void _updateSelectedArea(Image &image);

	public:
		ElipseSelectionTool(ToolBox &toolBox);
		void clear() override;
		void onMouseDrag(Vector2<int> oldPos, Vector2<int> newPos, MouseClick click, Image &image) override;
		void onClick(Vector2<int> pos, MouseClick click, Image &image) override;
		tgui::ScrollablePanel::Ptr getParametersPanel() const override;
		bool point_in_elipse(int x, int y, int rx, int ry);
	};
}


#endif //MYGIMP_ELIPSESELECTIONTOOL_HPP
