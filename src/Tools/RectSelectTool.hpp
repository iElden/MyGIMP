/*
** EPITECH PROJECT, 2020
** MyGimp
** File description:
** RectSelectTool.hpp
*/
#ifndef MYGIMP_RECTSELECTTOOL_HPP
#define MYGIMP_RECTSELECTTOOL_HPP

#include "SelectionTool.hpp"
#include "../ToolBox.hpp"

namespace Mimp {
	class RectSelectTool : public SelectionTool {
	private:
		int _state = 0;
		Vector2<int> _pt1 = {-1, -1};
		Vector2<int> _pt2 = {-1, -1};

		void _updateSelectedArea(Image &image);

	public:
		RectSelectTool(ToolBox &toolBox);
		void clear() override;
		void onMouseDrag(Vector2<int> oldPos, Vector2<int> newPos, MouseClick click, Image &image) override;
		void onClick(Vector2<int> pos, MouseClick click, Image &image) override;
		tgui::ScrollablePanel::Ptr getParametersPanel() override;
	};
}


#endif //MYGIMP_RECTSELECTTOOL_HPP
