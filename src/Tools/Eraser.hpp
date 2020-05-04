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
	class Eraser : public Tool {
	private:
		ToolBox &_box;
		unsigned short _radius = 5;
		DrawShape _shape = CIRCLE;

	public:
		//! @brief Constructor of the Pencil Class
		//! @param toolBox ToolBox to create the Pencil Tool
		Eraser(ToolBox &);
		void onMouseDrag(Vector2<int> oldPos, Vector2<int> newPos, MouseClick click, Image &image) override;
		void onClick(Vector2<int> pos, MouseClick click, Image &image) override;
		tgui::ScrollablePanel::Ptr getParametersPanel() override;
	};
}


#endif //MYGIMP_ERASER_HPP
