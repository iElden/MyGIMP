/*
** EPITECH PROJECT, 2020
** MyGimp
** File description:
** ExpandMoreSelection.cpp
*/
#include "ExpandMoreSelection.hpp"

Mimp::ExpandMoreSelection::ExpandMoreSelection():
		ImageOperation({"Selection", "Expand Selection ..."}, {KEY_I, true, true, true})
{}

void Mimp::ExpandMoreSelection::click(tgui::Gui &gui, Mimp::Image &image) const
{
	ExpandSelection::_run(image, 3);
}
