#ifndef MYGIMP_INCREASEGRID_HPP
#define MYGIMP_INCREASEGRID_HPP

#include "../ImageOperation.hpp"

namespace Mimp {
	class IncreaseGrid : public ImageOperation {
	public:
		IncreaseGrid();
		void click(tgui::Gui &gui, CanvasWidget::Ptr ptr, tgui::ChildWindow::Ptr window, Editor &editor) const override;
	};
}


#endif //MYGIMP_INCREASEGRID_HPP
