/*
** EPITECH PROJECT, 2020
** MyGimp
** File description:
** RectSelectTool.hpp
*/
#ifndef MYGIMP_RECTSELECTTOOL_HPP
#define MYGIMP_RECTSELECTTOOL_HPP

#include "SelectionTool.hpp"

namespace Mimp {
	class RectSelectTool : SelectionTool {
	private:
		int _state = 0;
		Vector2<int> _pt1 = {-1, -1};
		Vector2<int> _pt2 = {-1, -1};

		void _updateSelectedArea();

	public:
		RectSelectTool(Image &image);
		void clear() override;
		void onMouseDrag(Vector2<int> oldPos, Vector2<int> newPos, MouseClick click, Layer &layer) override;
		void onClick(Vector2<int> pos, MouseClick click, Layer &layer) override;
		tgui::ScrollablePanel::Ptr getParametersPanel() const override;
	};
}


#endif //MYGIMP_RECTSELECTTOOL_HPP
