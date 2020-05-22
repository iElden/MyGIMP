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
	//! @brief Define a Fill Tool.
	class Fill : public Tool {
	private:
		ToolBox &_box; //!< Reference to the ToolBox containing the Fill

		unsigned _tolerance = 0; //!< The tolerance of the Fill
		bool _alpha_in_tolerance = false; //!< Include or not the alpha when filling

		//! @brief Apply the Fill Tool
		//! @param pos Position of the Fill application
		//! @param layer Layer where the Fill tool is used
		//! @param click The Mouse click state
		void apply(Vector2<int> pos, Layer &layer, MouseClick &click);

		//! @brief Spread the Color on the SelectedArea
		//! @param pos Position of the spreading
		//! @param layer Layer where the spreading is applied
		//! @param target_color Color of the current area
		//! @param fill_color Color to apply
		void _spread_color(Vector2<int> pos, Layer &layer, Color target_color, Color fill_color);

	public:
		//! @brief Construct a Fill
		//! @param toolBox ToolBox containing the Fill Tool
		Fill(Mimp::ToolBox &toolBox);

        //! @brief Handle the mouse dragging of the Tool.
        //! @param oldPos Old position of the mouse
        //! @param newPos New position of the mouse
        //! @param click Mouse click state
        //! @param image The Image to edit
		void onMouseDrag(Vector2<int> oldPos, Vector2<int> newPos, MouseClick click, Image &image) override;

        //! @brief Handle the mouse click of the Tool.
        //! @param pos Position of the tool
        //! @param click Mouse click state
        //! @param image The Image to edit
		void onClick(Vector2<int> pos, MouseClick click, Image &image) override;

        //! @brief Get the parameters panel for the Tool.
        //! @return tgui::ScrollablePanel::Ptr Pointer containing the parameters panel
		tgui::ScrollablePanel::Ptr getParametersPanel() override;
	};
}


#endif //MYGIMP_FILL_HPP
