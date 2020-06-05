#include "IncreaseGrid.hpp"

Mimp::IncreaseGrid::IncreaseGrid() :
		ImageOperation({"Grid", "Increase grid size"}, {Keys::KEY_G, false, true, false})
{
}

void Mimp::IncreaseGrid::click(tgui::Gui &, Mimp::CanvasWidget::Ptr image, tgui::ChildWindow::Ptr , Mimp::Editor &) const
{
	image->increaseGrid();
}
