/*
** EPITECH PROJECT, 2020
** MyGimp
** File description:
** Undo.cpp
*/
#include "Undo.hpp"

Mimp::Undo::Undo():
	ImageOperation({"Edit", "Undo"}, {Keys::KEY_Z, true, false, false})
{}

void Mimp::Undo::click(tgui::Gui &, Mimp::CanvasWidget::Ptr image, tgui::ChildWindow::Ptr, Mimp::Editor &editor) const
{
	image->undoLastAction(editor);
}
