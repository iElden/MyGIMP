/*
** EPITECH PROJECT, 2020
** MyGimp
** File description:
** UnselectOperation.hpp
*/
#ifndef MYGIMP_UNSELECTOPERATION_HPP
#define MYGIMP_UNSELECTOPERATION_HPP


#include "../ImageOperation.hpp"

namespace Mimp
{
	//! @brief Define the UnselectOperation.
	class UnselectOperation : public ImageOperation {
	public:
		//! @brief Constructor of the Unselect Operation
		UnselectOperation();

		//! @brief Handles the click of the Selection.
		//! @details Unselect the whole image.
		//! @param gui The global gui (unused).
		//! @param image The image to edit.
		//! @param window The focused window (unused).
		//! @param editor The global editor (unused).
		void click(tgui::Gui &gui, CanvasWidget::Ptr image, tgui::ChildWindow::Ptr window, Editor &editor) const override;
	};
}


#endif //MYGIMP_UNSELECTOPERATION_HPP
