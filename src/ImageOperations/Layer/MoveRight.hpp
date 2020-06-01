//
// Created by Gegel85 on 25/05/2020.
//

#ifndef MYGIMP_MOVERIGHT_HPP
#define MYGIMP_MOVERIGHT_HPP


#include "../ImageOperation.hpp"
#include "../../CanvasWidget.hpp"

namespace Mimp
{
	//! @brief Define a MoveRight
	class MoveRight : public ImageOperation {
	public:
		MoveRight();

		//! @brief Handles the click of the MoveRight.
		//! @details Move the Layer to the right.
		//! @param gui The global gui (unused).
		//! @param image The image to edit.
		//! @param window The focused window (unused).
		//! @param editor The global editor (unused).
		void click(tgui::Gui &gui, CanvasWidget::Ptr image, tgui::ChildWindow::Ptr window, Editor &editor) const override;
	};
}


#endif //MYGIMP_MOVERIGHT_HPP
