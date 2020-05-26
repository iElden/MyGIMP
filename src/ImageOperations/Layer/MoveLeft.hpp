//
// Created by Gegel85 on 25/05/2020.
//

#ifndef MYGIMP_MOVELEFT_HPP
#define MYGIMP_MOVELEFT_HPP


#include "../ImageOperation.hpp"
#include "../../CanvasWidget.hpp"

namespace Mimp
{
	//! @brief Define a MoveLeft
	class MoveLeft : public ImageOperation {
	public:
		MoveLeft();

		//! @brief Handles the click of the MoveLeft.
		//! @details Move the Layer to the left.
		//! @param gui The global gui (unused).
		//! @param image The image to edit.
		//! @param window The focused window (unused).
		//! @param editor The global editor (unused).
		void click(tgui::Gui &gui, CanvasWidget::Ptr image, tgui::ChildWindow::Ptr window, Editor &editor) const override;
	};
}


#endif //MYGIMP_MOVELEFT_HPP
