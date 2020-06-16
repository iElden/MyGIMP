/*
** EPITECH PROJECT, 2020
** MyGimp
** File description:
** DelSelectionOperation.hpp
*/
#ifndef MYGIMP_DELSELECTIONOPERATION_HPP
#define MYGIMP_DELSELECTIONOPERATION_HPP


#include "FillSelectionOperation.hpp"
#include "../ImageOperation.hpp"

namespace Mimp
{
	//! @brief Define the DelSelectionOperation.
	class DelSelectionOperation : public ImageOperation {
	public:

		//! @brief Constructor of the Deletion Selection Operation
		DelSelectionOperation();

		//! @brief Handles the click of the Deletion.
		//! @details Delete the selection on the image.
		//! @param gui The global gui (unused).
		//! @param image The image to edit.
		//! @param window The focused window (unused).
		//! @param editor The global editor (unused).
		void click(tgui::Gui &gui, CanvasWidget::Ptr image, tgui::ChildWindow::Ptr window, Editor &editor) const override;
	};
}

#endif //MYGIMP_DELSELECTIONOPERATION_HPP
