#include "DrawGrid.hpp"

Mimp::DrawGrid::DrawGrid() :
		ImageOperation({"Grid", "Draw grid"}, {Keys::KEY_G, true, false, false})
{
}

void Mimp::DrawGrid::click(tgui::Gui &, Mimp::CanvasWidget::Ptr image, tgui::ChildWindow::Ptr , Mimp::Editor &) const
{
	image->updateGrid();
}
