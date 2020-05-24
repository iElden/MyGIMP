//
// Created by Gegel85 on 24/05/2020.
//

#ifndef MYGIMP_CUTOPERATION_HPP
#define MYGIMP_CUTOPERATION_HPP


#include "../ImageOperation.hpp"
#include "../../CanvasWidget.hpp"

namespace Mimp
{
	class CutOperation : public ImageOperation {
	public:
		CutOperation();
		void click(tgui::Gui &gui, CanvasWidget::Ptr image, tgui::ChildWindow::Ptr window, Editor &editor) const override;
	};
}


#endif //MYGIMP_CUTOPERATION_HPP
