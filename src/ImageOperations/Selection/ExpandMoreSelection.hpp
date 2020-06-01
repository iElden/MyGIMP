/*
** EPITECH PROJECT, 2020
** MyGimp
** File description:
** ExpandMoreSelection.hpp
*/
#ifndef MYGIMP_EXPANDMORESELECTION_HPP
#define MYGIMP_EXPANDMORESELECTION_HPP

#include "ExpandSelection.hpp"

namespace Mimp {
    //! @brief Define the ExpandMoreSelection.
	class ExpandMoreSelection : public ImageOperation {
	public:
        //! @brief Constructor of the ExpansionMore Selection Operation
        ExpandMoreSelection();

        //! @brief Handles the click of the Expansion.
        //! @details Display a slider and expand the selection on the image.
        //! @param gui The global gui used to open a slider dialog.
        //! @param image The image to edit.
        //! @param window The focused window (unused).
        //! @param editor The global editor (unused).
	void click(tgui::Gui &gui, CanvasWidget::Ptr image, tgui::ChildWindow::Ptr window, Editor &editor) const override;
	};
}


#endif //MYGIMP_EXPANDMORESELECTION_HPP
