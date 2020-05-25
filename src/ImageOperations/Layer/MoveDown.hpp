//
// Created by Gegel85 on 25/05/2020.
//

#ifndef MYGIMP_MOVEDOWN_HPP
#define MYGIMP_MOVEDOWN_HPP


#include "../ImageOperation.hpp"
#include "../../CanvasWidget.hpp"

namespace Mimp
{
	class MoveDown : public ImageOperation {
	public:
		MoveDown();
		void click(tgui::Gui &gui, CanvasWidget::Ptr image, tgui::ChildWindow::Ptr window, Editor &editor) const override;
	};
}


#endif //MYGIMP_MOVEDOWN_HPP
