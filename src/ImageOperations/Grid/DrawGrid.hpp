#ifndef MYGIMP_DRAWGRID_HPP
#define MYGIMP_DRAWGRID_HPP

#include "../ImageOperation.hpp"

namespace Mimp {
	class DrawGrid : public ImageOperation {
	public:
		DrawGrid();
		void click(tgui::Gui &gui, CanvasWidget::Ptr ptr, tgui::ChildWindow::Ptr window, Editor &editor) const override;
	};
}


#endif //MYGIMP_DRAWGRID_HPP
