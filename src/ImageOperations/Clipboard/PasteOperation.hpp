//
// Created by andgel on 23/05/2020
//

#ifndef MYGIMP_PASTEOPERATION_HPP
#define MYGIMP_PASTEOPERATION_HPP


#include "../ImageOperation.hpp"
#include "../../Widgets/CanvasWidget.hpp"

namespace Mimp
{
	//! @brief Define a PastOperation
	class PasteOperation : public ImageOperation {
	public:
		PasteOperation();

		//! @brief Handles the click of the PasteOperation.
		//! @details Paste the clipboard inside the CanvasWidget.
		//! @param gui The global gui (unused).
		//! @param image The image to edit.
		//! @param window The focused window.
		//! @param editor The global editor.
		void click(tgui::Gui &gui, CanvasWidget::Ptr image, tgui::ChildWindow::Ptr window, Editor &editor) const override;
	};
}


#endif //MYGIMP_PASTEOPERATION_HPP
