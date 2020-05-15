/*
** EPITECH PROJECT, 2020
** MyGimp
** File description:
** ShrinkMoreSelection.cpp
*/
#include "ShrinkMoreSelection.hpp"
#include "ExpandMoreSelection.hpp"
#include "ShrinkSelection.hpp"

Mimp::ShrinkMoreSelection::ShrinkMoreSelection():
		ImageOperation({"Selection", "Shrink Selection ..."}, {KEY_K, true, true, true})
{}

void Mimp::ShrinkMoreSelection::click(tgui::Gui &, Mimp::Image &image) const
{
	ShrinkSelection::_run(image, 3);
}
