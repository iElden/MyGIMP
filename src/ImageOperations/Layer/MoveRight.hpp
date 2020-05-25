//
// Created by Gegel85 on 25/05/2020.
//

#ifndef MYGIMP_MOVERIGHT_HPP
#define MYGIMP_MOVERIGHT_HPP


#include "../ImageOperation.hpp"
#include "../../CanvasWidget.hpp"

namespace Mimp
{
	class MoveRight : public ImageOperation {
	public:
		MoveRight();
		void click(tgui::Gui &gui, CanvasWidget::Ptr image, tgui::ChildWindow::Ptr window, Editor &editor) const override;
	};
}


#endif //MYGIMP_MOVERIGHT_HPP
