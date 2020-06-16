/*
** EPITECH PROJECT, 2020
** MyGimp
** File description:
** OutlineMoreSelectionOperation.cpp
*/
#include "OutlineMoreSelectionOperation.hpp"
#include "OutlineSelectionOperation.hpp"
#include "../../Utils.hpp"

Mimp::OutlineMoreSelectionOperation::OutlineMoreSelectionOperation():
	ImageOperation({"Selection", "Outline with thickness of ..."}, {Keys::KEY_O, true, true, true})
{}

void Mimp::OutlineMoreSelectionOperation::click(tgui::Gui &gui, CanvasWidget::Ptr image, tgui::ChildWindow::Ptr, Mimp::Editor &) const
{
	Utils::makeSliderWindow(gui, [image](unsigned short value){
		OutlineSelectionOperation::_run(*image, value);
	});
}
