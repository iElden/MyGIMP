//
// Created by andgel on 23/05/2020
//

#ifndef MYGIMP_PASTEOPERATION_HPP
#define MYGIMP_PASTEOPERATION_HPP


#include "../ImageOperation.hpp"
#include "../../CanvasWidget.hpp"

namespace Mimp
{
	class PasteOperation : public ImageOperation {
	public:
		PasteOperation();
		void click(tgui::Gui &gui, CanvasWidget::Ptr image, tgui::ChildWindow::Ptr window, Editor &editor) const override;
	};
}


#endif //MYGIMP_PASTEOPERATION_HPP
