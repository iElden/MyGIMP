//
// Created by Gegel85 on 25/05/2020.
//

#ifndef MYGIMP_ROTATERIGHT90_HPP
#define MYGIMP_ROTATERIGHT90_HPP


#include "../ImageOperation.hpp"
#include "../../Widgets/CanvasWidget.hpp"

namespace Mimp
{
	//! @brief Define a Rotation of 90°
	class RotateRight90 : public ImageOperation {
	public:
		//! @brief Construct the rotator.
		RotateRight90();

		//! @brief Handles the click of the RotateRight90.
		//! @details Rotate the selection on the image.
		//! @param gui The global gui (unused).
		//! @param image The image to edit.
		//! @param window The focused window (unused).
		//! @param editor The global editor (unused).
		void click(tgui::Gui &gui, CanvasWidget::Ptr image, tgui::ChildWindow::Ptr window, Editor &editor) const override;
	};
}


#endif //MYGIMP_ROTATERIGHT90_HPP
