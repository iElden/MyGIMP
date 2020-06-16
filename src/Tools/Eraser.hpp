/*
** EPITECH PROJECT, 2020
** MyGimp
** File description:
** Eraser.hpp
*/
#ifndef MYGIMP_ERASER_HPP
#define MYGIMP_ERASER_HPP


#include "Tool.hpp"
#include "../ToolBox.hpp"

namespace Mimp
{
	//! @brief Define a Eraser
	class Eraser : public Tool {
	private:
		ToolBox &_box;
		unsigned short _radius = 5;
		DrawShape _shape = CIRCLE;

	public:
		//! @brief Constructor of the Pencil Class
		//! @param toolBox ToolBox to create the Eraser Tool
		Eraser(ToolBox &toolBox);

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


#endif //MYGIMP_ERASER_HPP
