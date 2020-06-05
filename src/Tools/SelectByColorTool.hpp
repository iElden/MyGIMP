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
    //! @brief Define a SelectByColorTool
	class SelectByColorTool : public SelectionTool {
	private:
		void _updateSelectedArea(Image &image, const Color &target_color);

		unsigned _tolerance = 0; //!< The tolerance of the Selection
		bool _alpha_in_tolerance = false; //!< Include or not the alpha when selecting

	public:
        //! @brief Construct a SelectByColorTool
        //! @param toolBox ToolBox containing the SelectByColorTool Tool
		SelectByColorTool(ToolBox &toolBox);

        //! @brief Handle the mouse dragging of the Tool.
        //! @param oldPos Old position of the mouse
        //! @param newPos New position of the mouse
        //! @param click Mouse click state
        //! @param image The Image to edit
		void onMouseDrag([[maybe_unused]] Vector2<int> oldPos, [[maybe_unused]] Vector2<int> newPos, [[maybe_unused]] MouseClick click, [[maybe_unused]] Image &image) override {};

        //! @brief Handle the mouse click of the Tool.
        //! @param pos Position of the tool
        //! @param click Mouse click state
        //! @param image The Image to edit
		void onClick(Vector2<int> pos, MouseClick click, Image &layer) override;

        //! @brief Get the parameters panel for the Tool.
        //! @return tgui::ScrollablePanel::Ptr Pointer containing the parameters panel
		tgui::ScrollablePanel::Ptr getParametersPanel() override;
	};
}


#endif //MYGIMP_SELECTBYCOLORTOOL_HPP
