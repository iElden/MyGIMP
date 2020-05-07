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
	//! @brief Class For the Fill Tool
	//! @inherit Tool
	//! @details Fill tool fills the selected area
	class Fill : public Tool {
	private:
		//! @brief Reference of the Toolbox
		ToolBox &_box;

		unsigned _tolerance;

		//! @brief Apply the fill tool
		//! @param pos Position of the fill application
		//! @param layer Layer where the fill tool is used
		//! @param click The Mouse click state
		void apply(Vector2<int> pos, Layer &layer, MouseClick &click);
		//! @brief Spread the color on the selected area
		//! @param pos Position of the spreading
		//! @param layer Layer where the spreading is applied
		//! @param target_color Color of the current area
		//! @param fill_color Color to apply
		void _spread_color(Vector2<int> pos, Layer &layer, Color target_color, Color fill_color);

	public:
		//! @brief Constructor of the Fill Class
		//! @param toolBox ToolBox to create the Fill Tool
		Fill(Mimp::ToolBox &toolBox);
		void onMouseDrag(Vector2<int> oldPos, Vector2<int> newPos, MouseClick click, Image &image) override;
		void onClick(Vector2<int> pos, MouseClick click, Image &image) override;
		tgui::ScrollablePanel::Ptr getParametersPanel() override;
	};
}


#endif //MYGIMP_FILL_HPP
