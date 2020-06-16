/*
** EPITECH PROJECT, 2020
** MyGimp
** File description:
** InvertSelectionOperation.hpp
*/
#ifndef MYGIMP_INVERTSELECTIONOPERATION_HPP
#define MYGIMP_INVERTSELECTIONOPERATION_HPP


#include "../ImageOperation.hpp"
#include "../../Editor.hpp"

namespace Mimp
{
	//! @brief Define the InvertSelectionOperation.
	class InvertSelectionOperation : public ImageOperation {
	public:
		//! @brief Constructor of the Invert Selection Operation
		InvertSelectionOperation();

		//! @brief Handles the click of the Inversion.
		//! @details Invert the selection on the image.
		//! @param gui The global gui (unused).
		//! @param image The image to edit.
		//! @param window The focused window (unused).
		//! @param editor The global editor (unused).
		void click(tgui::Gui &gui, CanvasWidget::Ptr image, tgui::ChildWindow::Ptr window, Mimp::Editor &editor) const override;
	};
}


#endif //MYGIMP_INVERTSELECTIONOPERATION_HPP
