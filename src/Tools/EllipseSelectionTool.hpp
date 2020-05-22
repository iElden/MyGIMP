/*
** EPITECH PROJECT, 2020
** MyGimp
** File description:
** EllipseSelectionTool.hpp
*/
#ifndef MYGIMP_ELLIPSESELECTIONTOOL_HPP
#define MYGIMP_ELLIPSESELECTIONTOOL_HPP


#include "SelectionTool.hpp"

namespace Mimp {
    //! @brief Define a EllipseSelectionTool
	class EllipseSelectionTool : public SelectionTool {
	private:
		int _state;
		Vector2<int> _pt1;
		Vector2<int> _pt2;

		void _updateSelectedArea(Image &image);

	public:
        //! @brief Construct a EllipseSelectionTool
        //! @param toolBox ToolBox containing the EllipseSelectionTool Tool
		EllipseSelectionTool(ToolBox &toolBox);
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

		//! @brief Test if the point is inside the ellipse selection.
		//! @param x X position of the point
        //! @param y Y position of the point
        //! @param rx X radius of the ellipse
        //! @param ry Y radius of the ellipse
		bool point_in_ellipse(int x, int y, int rx, int ry);
	};
}


#endif //MYGIMP_ELLIPSESELECTIONTOOL_HPP
