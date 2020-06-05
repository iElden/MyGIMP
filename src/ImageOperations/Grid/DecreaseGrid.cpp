#include "DecreaseGrid.hpp"

Mimp::DecreaseGrid::DecreaseGrid() :
		ImageOperation({"Grid", "Decrease grid size"}, {Keys::KEY_G, false, false, true})
{
}

void Mimp::DecreaseGrid::click(tgui::Gui &, Mimp::CanvasWidget::Ptr image, tgui::ChildWindow::Ptr , Mimp::Editor &) const
{
	image->decreaseGrid();
}
