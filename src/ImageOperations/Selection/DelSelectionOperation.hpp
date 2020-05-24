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
	private:
		void _fill(Layer &layer, const SelectedArea &area, const Color &color);
	public:

	    //! @brief Constructor of the Deletion Selection Operation
		DelSelectionOperation();

	    //! @brief Handles the click of the Deletion.
	    //! @details Delete the selection on the image.
	    //! @param gui The global gui (unused).
	    //! @param image The image to edit.
	    void click(tgui::Gui &gui, CanvasWidget::Ptr image, tgui::ChildWindow::Ptr window, Editor &editor) const override;
	};
}

#endif //MYGIMP_DELSELECTIONOPERATION_HPP
