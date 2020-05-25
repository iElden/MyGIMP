//
// Created by Gegel85 on 25/05/2020.
//

#ifndef MYGIMP_ROTATERIGHT90_HPP
#define MYGIMP_ROTATERIGHT90_HPP


#include "../ImageOperation.hpp"
#include "../../CanvasWidget.hpp"

namespace Mimp
{
	class RotateRight90 : public ImageOperation {
	public:
		RotateRight90();
		void click(tgui::Gui &gui, CanvasWidget::Ptr image, tgui::ChildWindow::Ptr window, Editor &editor) const override;
	};
}


#endif //MYGIMP_ROTATERIGHT90_HPP
