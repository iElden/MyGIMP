/*
** EPITECH PROJECT, 2020
** MyGimp
** File description:
** ShrinkMoreSelection.hpp
*/
#ifndef MYGIMP_SHRINKMORESELECTION_HPP
#define MYGIMP_SHRINKMORESELECTION_HPP


#include "../ImageOperation.hpp"

namespace Mimp {
    //! @brief Define the ShrinkMoreSelection.
    class ShrinkMoreSelection : public ImageOperation {
	public:
        //! @brief Constructor of the ShrinkMore Selection Operation
		ShrinkMoreSelection();

        //! @brief Handles the click of the ShrinkMore Selection Operation.
        //! @details Shrink the selection on the image.
        //! @param gui The global gui used to open a slider dialog.
        //! @param image The image to edit.
	void click(tgui::Gui &gui, CanvasWidget::Ptr image, tgui::ChildWindow::Ptr window, Editor &editor) const override;
	};
}


#endif //MYGIMP_SHRINKMORESELECTION_HPP
