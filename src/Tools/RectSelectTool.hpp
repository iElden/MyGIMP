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
#include "EllipseSelectionTool.hpp"

namespace Mimp {
	//! @brief Define a RectSelectTool
	class RectSelectTool : public SelectionTool {
	private:
		int _state = 0;
		Vector2<int> _pt1 = {-1, -1};
		Vector2<int> _pt2 = {-1, -1};

		void _updateSelectedArea(Image &image);

		EllipseSelectionTool _esp;
		float _percentage = 0;

	public:
		//! @brief Construct a RectSelectTool
		//! @param toolBox ToolBox containing the RectSelectTool Tool
		RectSelectTool(ToolBox &toolBox);
		void clear() override;

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


#endif //MYGIMP_RECTSELECTTOOL_HPP
