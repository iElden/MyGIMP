//
// Created by Gegel85 on 02/06/2020.
//

#ifndef MYGIMP_ROTATE_HPP
#define MYGIMP_ROTATE_HPP


#include "../ImageOperation.hpp"
#include "../../CanvasWidget.hpp"

namespace Mimp
{
	class Rotate : public ImageOperation {
	public:
		Rotate();
		void click(tgui::Gui &gui, CanvasWidget::Ptr image, tgui::ChildWindow::Ptr window, Editor &editor) const override;
	};
}


#endif //MYGIMP_ROTATE_HPP
