/*
** EPITECH PROJECT, 2020
** MyGimp
** File description:
** Fill.hpp
*/
#ifndef MYGIMP_FILL_HPP
#define MYGIMP_FILL_HPP

#include "../ToolBox.hpp"

namespace Mimp
{
	class Fill : public Tool {
	private:
		ToolBox &_box;

		void apply(Vector2<int> pos, Layer &layer, MouseClick &click);
		void _spread_color(Vector2<int> pos, Layer &layer, Color target_color, Color fill_color);

	public:
		Fill(Mimp::ToolBox &toolBox);
		void onMouseDrag(Vector2<int> oldPos, Vector2<int> newPos, MouseClick click, Layer &layer) override;
		void onClick(Vector2<int> pos, MouseClick click, Layer &layer) override;
		tgui::ScrollablePanel::Ptr getParametersPanel() const override;
	};
}


#endif //MYGIMP_FILL_HPP
