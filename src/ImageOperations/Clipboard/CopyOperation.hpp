//
// Created by Gegel85 on 24/05/2020.
//

#ifndef MYGIMP_COPYOPERATION_HPP
#define MYGIMP_COPYOPERATION_HPP


#include "../ImageOperation.hpp"
#include "../../CanvasWidget.hpp"

namespace Mimp
{
	class CopyOperation : public ImageOperation {
	public:
		CopyOperation();
		void click(tgui::Gui &gui, CanvasWidget::Ptr image, tgui::ChildWindow::Ptr window, Editor &editor) const override;
	};
}


#endif //MYGIMP_COPYOPERATION_HPP
