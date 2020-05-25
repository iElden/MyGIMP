//
// Created by Gegel85 on 25/05/2020.
//

#ifndef MYGIMP_MOVELEFT_HPP
#define MYGIMP_MOVELEFT_HPP


#include "../ImageOperation.hpp"
#include "../../CanvasWidget.hpp"

namespace Mimp
{
	class MoveLeft : public ImageOperation {
	public:
		MoveLeft();
		void click(tgui::Gui &gui, CanvasWidget::Ptr image, tgui::ChildWindow::Ptr window, Editor &editor) const override;
	};
}


#endif //MYGIMP_MOVELEFT_HPP
