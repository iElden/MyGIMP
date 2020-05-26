/*
** EPITECH PROJECT, 2020
** MyGimp
** File description:
** UnselectOperation.cpp
*/
#include "UnselectOperation.hpp"
#include "../../CanvasWidget.hpp"

Mimp::UnselectOperation::UnselectOperation():
	ImageOperation({"Selection", "Unselect"}, "Unselect", {Keys::KEY_D, true, false, false})
{

}

void Mimp::UnselectOperation::click(tgui::Gui &, CanvasWidget::Ptr image, tgui::ChildWindow::Ptr, Editor &) const
{
	image->selectedArea.clear();
}
