//
// Created by Gegel85 on 24/05/2020.
//

#ifndef MYGIMP_COPYOPERATION_HPP
#define MYGIMP_COPYOPERATION_HPP


#include "../ImageOperation.hpp"
#include "../../CanvasWidget.hpp"

namespace Mimp
{
	//! @brief Define a CopyOperation
	class CopyOperation : public ImageOperation {
	public:
		CopyOperation();

		//! @brief Handles the click of the CopyOperation.
		//! @details Copy the CanvasWidget.
		//! @param gui The global gui (unused).
		//! @param image The image to edit.
		//! @param window The focused window (unused).
		//! @param editor The global editor (unused).
		void click(tgui::Gui &gui, CanvasWidget::Ptr image, tgui::ChildWindow::Ptr window, Editor &editor) const override;
	};
}


#endif //MYGIMP_COPYOPERATION_HPP
