/*
** EPITECH PROJECT, 2020
** MyGimp
** File description:
** ExpandMoreSelection.cpp
*/
#include "ExpandMoreSelection.hpp"
#include "../../Utils.hpp"

Mimp::ExpandMoreSelection::ExpandMoreSelection():
		ImageOperation({"Selection", "Expand Selection ..."}, {KEY_I, true, true, true})
{}

void Mimp::ExpandMoreSelection::click(tgui::Gui &gui, Mimp::Image &image) const
{
	Utils::makeSliderWindow(gui, [&image](unsigned short value){
		ExpandSelection::_run(image, value);
	});
}
