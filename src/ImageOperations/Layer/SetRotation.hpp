//
// Created by Gegel85 on 02/06/2020.
//

#ifndef MYGIMP_SETROTATION_HPP
#define MYGIMP_SETROTATION_HPP


#include "../ImageOperation.hpp"
#include "../../Widgets/CanvasWidget.hpp"

namespace Mimp
{
	class SetRotation : public ImageOperation {
	public:
		SetRotation();
		void click(tgui::Gui &gui, CanvasWidget::Ptr image, tgui::ChildWindow::Ptr window, Editor &editor) const override;
	};
}


#endif //MYGIMP_SETROTATION_HPP
