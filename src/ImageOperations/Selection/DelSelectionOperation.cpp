/*
** EPITECH PROJECT, 2020
** MyGimp
** File description:
** DelSelectionOperation.cpp
*/

#include "DelSelectionOperation.hpp"

Mimp::DelSelectionOperation::DelSelectionOperation():
	ImageOperation({"Selection", "Delete Selection"}, {KEY_DEL, false, false, false})
{}

void Mimp::DelSelectionOperation::click(tgui::Gui &, Mimp::Image &image) const
{
	image.selectedArea.fill(image.getSelectedLayer(), Color::Transparent);
}

