/*
** EPITECH PROJECT, 2020
** MyGimp
** File description:
** ExpandSelection.hpp
*/
#ifndef MYGIMP_EXPANDSELECTION_HPP
#define MYGIMP_EXPANDSELECTION_HPP

#include "../ImageOperation.hpp"

namespace Mimp {
    //! @brief Define the ExpandSelection.
    class ExpandSelection : public ImageOperation {
    public:
	    //! @brief Do not call it directly. Use ExpandSelection::click.
		static void _addPointIfPointNearby(unsigned i, unsigned j, Mimp::Image &image, const SelectedArea &area, int range) noexcept;

        //! @brief Do not call it directly. Use ExpandSelection::click.
		static void _run(Image &image, int range=1) noexcept;

        //! @brief Constructor of the Expansion Selection Operation
        ExpandSelection();

        //! @brief Handles the click of the Expansion.
        //! @details Expand the selection on the image.
        //! @param gui The global gui (unused).
        //! @param image The image to edit.
        //! @param window The focused window (unused).
        //! @param editor The global editor (unused).
	void click(tgui::Gui &gui, CanvasWidget::Ptr image, tgui::ChildWindow::Ptr window, Editor &editor) const override;
	};
}


#endif //MYGIMP_EXPANDSELECTION_HPP
