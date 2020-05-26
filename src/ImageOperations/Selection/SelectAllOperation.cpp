/*
** EPITECH PROJECT, 2020
** MyGimp
** File description:
** SelectAllOperation.cpp
*/
#include "SelectAllOperation.hpp"

Mimp::SelectAllOperation::SelectAllOperation():
	ImageOperation({"Selection", "Select all"}, "Select all",{Keys::KEY_A, true, false, false})
{

}

void Mimp::SelectAllOperation::click(tgui::Gui &, CanvasWidget::Ptr image, tgui::ChildWindow::Ptr, Editor &) const
{
	image->selectedArea.selectAll();
}