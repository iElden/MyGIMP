//
// Created by Gegel85 on 25/05/2020.
//

#ifndef MYGIMP_MOVEUP_HPP
#define MYGIMP_MOVEUP_HPP


#include "../ImageOperation.hpp"
#include "../../CanvasWidget.hpp"

namespace Mimp
{
	class MoveUp : public ImageOperation {
	public:
		MoveUp();
		void click(tgui::Gui &gui, CanvasWidget::Ptr image, tgui::ChildWindow::Ptr window, Editor &editor) const override;
	};
}


#endif //MYGIMP_MOVEUP_HPP
