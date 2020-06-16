//
// Created by Gegel85 on 25/05/2020.
//

#ifndef MYGIMP_ROTATELEFT90_HPP
#define MYGIMP_ROTATELEFT90_HPP


#include "../ImageOperation.hpp"
#include "../../Widgets/CanvasWidget.hpp"

namespace Mimp
{
	class RotateLeft90 : public ImageOperation {
	public:
		RotateLeft90();
		void click(tgui::Gui &gui, CanvasWidget::Ptr image, tgui::ChildWindow::Ptr window, Editor &editor) const override;
	};
}


#endif //MYGIMP_ROTATELEFT90_HPP
