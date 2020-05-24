//
// Created by Gegel85 on 24/05/2020.
//

#ifndef MYGIMP_MOVE_HPP
#define MYGIMP_MOVE_HPP


#include "Tool.hpp"
#include "../ToolBox.hpp"

namespace Mimp
{
	class Move : public Tool {
	public:
		//! @brief Constructor of the Pencil Class
		//! @param toolBox ToolBox to create the Pencil Tool
		Move();

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


#endif //MYGIMP_MOVE_HPP
