//
// Created by Gegel85 on 24/05/2020.
//

#ifndef MYGIMP_CUTOPERATION_HPP
#define MYGIMP_CUTOPERATION_HPP


#include "../ImageOperation.hpp"
#include "../../CanvasWidget.hpp"

namespace Mimp
{
	//! @brief Define a CutOperation
	class CutOperation : public ImageOperation {
	public:
		CutOperation();

		//! @brief Handles the click of the CutOperation.
		//! @details Cut the CanvasWidget.
		//! @param gui The global gui (unused).
		//! @param image The image to edit.
		//! @param window The focused window (unused).
		//! @param editor The global editor (unused).
		void click(tgui::Gui &gui, CanvasWidget::Ptr image, tgui::ChildWindow::Ptr window, Editor &editor) const override;
	};
}


#endif //MYGIMP_CUTOPERATION_HPP
