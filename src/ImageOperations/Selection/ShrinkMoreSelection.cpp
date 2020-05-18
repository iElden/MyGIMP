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

Mimp::ShrinkMoreSelection::ShrinkMoreSelection():
		ImageOperation({"Selection", "Shrink Selection ..."}, {KEY_K, true, true, true})
{}

void Mimp::ShrinkMoreSelection::click(tgui::Gui &gui, Mimp::Image &image) const
{
	Utils::makeSliderWindow(gui, [&image](unsigned short value){
		ShrinkSelection::_run(image, value);
	});

}
