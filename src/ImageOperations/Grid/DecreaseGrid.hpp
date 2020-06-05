#ifndef MYGIMP_DECREASEGRID_HPP
#define MYGIMP_DECREASEGRID_HPP

#include "../ImageOperation.hpp"

namespace Mimp {
	class DecreaseGrid : public ImageOperation {
	public:
		DecreaseGrid();
		void click(tgui::Gui &gui, CanvasWidget::Ptr ptr, tgui::ChildWindow::Ptr window, Editor &editor) const override;
	};
}


#endif //MYGIMP_DECREASEGRID_HPP
