/*
** EPITECH PROJECT, 2020
** MyGimp
** File description:
** ColorPick.hpp
*/
#ifndef MYGIMP_COLORPICK_HPP
#define MYGIMP_COLORPICK_HPP

#include "Tool.hpp"
#include "../ToolBox.hpp"

namespace Mimp {
    //! @brief Class ColorPick
    //! @inherit Tool
	class ColorPick : public Tool {
	private:
	    //! @brief ToolBox
		ToolBox &_toolBox;
	public:
	    //! @brief Constructor of ColorPick class
	    //! @param toolBox Toolbox
		ColorPick(ToolBox &toolBox);
		void onClick(Vector2<int> pos, MouseClick click, Image &layer) override;
		void onMouseDrag(Vector2<int>, Vector2<int>, MouseClick, Image &) override;
		tgui::ScrollablePanel::Ptr getParametersPanel() const override;
	};
}


#endif //MYGIMP_COLORPICK_HPP
