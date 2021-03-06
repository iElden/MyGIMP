/*
** EPITECH PROJECT, 2020
** MyGimp
** File description:
** Redo.cpp
*/
#include "Redo.hpp"

Mimp::Redo::Redo():
	ImageOperation({"Edit", "Redo"}, {Keys::KEY_Y, true, false, false})
{}

void Mimp::Redo::click(tgui::Gui &, Mimp::CanvasWidget::Ptr image, tgui::ChildWindow::Ptr, Mimp::Editor &editor) const
{
	image->redoLastUndo(editor);
}