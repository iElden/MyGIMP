/*
** EPITECH PROJECT, 2020
** MyGimp
** File description:
** SelectAllOperation.hpp
*/
#ifndef MYGIMP_SELECTALLOPERATION_HPP
#define MYGIMP_SELECTALLOPERATION_HPP


#include "../ImageOperation.hpp"
#include "../../CanvasWidget.hpp"
#include "../../Editor.hpp"

namespace Mimp
{
    //! @brief Define the SelectAllOperation.
	class SelectAllOperation : public ImageOperation {
	public:
        //! @brief Constructor of the SelectAll Operation
        SelectAllOperation();

        //! @brief Handles the click of the Selection.
        //! @details Select the whole image.
        //! @param gui The global gui (unused).
        //! @param image The image to edit.
	void click(tgui::Gui &gui, CanvasWidget::Ptr image, tgui::ChildWindow::Ptr window, Editor &editor) const override;
	};
}


#endif //MYGIMP_SELECTALLOPERATION_HPP
