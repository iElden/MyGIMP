//
// Created by Gegel85 on 25/05/2020.
//

#ifndef MYGIMP_MOVEUP_HPP
#define MYGIMP_MOVEUP_HPP


#include "../ImageOperation.hpp"
#include "../../Widgets/CanvasWidget.hpp"

namespace Mimp
{
	//! @brief Define a MoveUp
	class MoveUp : public ImageOperation {
	public:
		MoveUp();

		//! @brief Handles the click of the MoveUp.
		//! @details Move the Layer to the top.
		//! @param gui The global gui (unused).
		//! @param image The image to edit.
		//! @param window The focused window (unused).
		//! @param editor The global editor (unused).
		void click(tgui::Gui &gui, CanvasWidget::Ptr image, tgui::ChildWindow::Ptr window, Editor &editor) const override;
	};
}


#endif //MYGIMP_MOVEUP_HPP
