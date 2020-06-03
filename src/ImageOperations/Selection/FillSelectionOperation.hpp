//
// Created by Gegel85 on 25/04/2020.
//

#ifndef MYGIMP_FILLSELECTIONOPERATION_HPP
#define MYGIMP_FILLSELECTIONOPERATION_HPP


#include "../ImageOperation.hpp"
#include "../../Widgets/CanvasWidget.hpp"
#include "../../Editor.hpp"

namespace Mimp
{
    //! @brief Define the FillSelectionOperation.
    class FillSelectionOperation : public ImageOperation {
    protected:
        //! @brief Fill the SelectedArea of the Layer with a Color.
        //! @param layer The Layer to fill
        //! @param area The SelectedArea of the Layer to fill
        //! @param color The Color used to fill
		static void _fill(Layer &layer, const SelectedArea &area, const Color &color);

	public:
        //! @brief Constructor of the Fill Selection Operation
        FillSelectionOperation();

        //! @brief Handles the click of the Filler.
        //! @details Expand the selection on the image.
        //! @param gui The global gui (unused).
        //! @param image The image to edit.
        //! @param window The focused window (unused).
        //! @param editor The global editor (unused).
	void click(tgui::Gui &gui, CanvasWidget::Ptr image, tgui::ChildWindow::Ptr window, Editor &editor) const override;
	};
}


#endif //MYGIMP_FILLSELECTIONOPERATION_HPP
