/*
** EPITECH PROJECT, 2020
** MyGimp
** File description:
** ShrinkMoreSelection.cpp
*/
#include "ShrinkMoreSelection.hpp"
#include "ExpandMoreSelection.hpp"
#include "ShrinkSelection.hpp"
#include "../../Utils.hpp"
#include "../../Widgets/CanvasWidget.hpp"
#include "../../Editor.hpp"

Mimp::ShrinkMoreSelection::ShrinkMoreSelection():
	ImageOperation({"Selection", "Shrink Selection ..."}, {Keys::KEY_K, true, true, true})
{}

void Mimp::ShrinkMoreSelection::click(tgui::Gui &gui, CanvasWidget::Ptr image, tgui::ChildWindow::Ptr, Editor &) const
{
	Utils::makeSliderWindow(gui, [image](unsigned short value){
		ShrinkSelection::_run(*image, value);
	});
}
