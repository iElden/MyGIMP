/*
** EPITECH PROJECT, 2020
** MyGimp
** File description:
** OutlineMoreSelectionOperation.hpp
*/
#ifndef MYGIMP_OUTLINEMORESELECTIONOPERATION_HPP
#define MYGIMP_OUTLINEMORESELECTIONOPERATION_HPP

#include "../ImageOperation.hpp"

namespace Mimp {
	//! @brief Define the OutlineMoreSelectionOperation.
	class OutlineMoreSelectionOperation : public ImageOperation {
	public:
		//! @brief Constructor of the OutlineMore Selection Operation
		OutlineMoreSelectionOperation();

		//! @brief Handles the click of the Expansion.
		//! @details Invert the selection on the image.
		//! @param gui The global gui used to open a slider dialog.
		//! @param image The image to edit.
		void click(tgui::Gui &gui, CanvasWidget::Ptr image, tgui::ChildWindow::Ptr window, Mimp::Editor &) const override;
	};
}

#endif //MYGIMP_OUTLINEMORESELECTIONOPERATION_HPP
