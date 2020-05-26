/*
** EPITECH PROJECT, 2020
** MyGimp
** File description:
** DelSelectionOperation.cpp
*/

#include "DelSelectionOperation.hpp"

Mimp::DelSelectionOperation::DelSelectionOperation():
	ImageOperation({"Selection", "Delete Selection"},"Delete Selection", {Keys::KEY_DEL, false, false, false})
{}

void Mimp::DelSelectionOperation::click(tgui::Gui &, CanvasWidget::Ptr image, tgui::ChildWindow::Ptr, Editor &) const
{
	image->selectedArea.fill(image->getSelectedLayer(), Color::Transparent);
}

