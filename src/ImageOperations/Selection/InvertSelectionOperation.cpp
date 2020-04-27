/*
** EPITECH PROJECT, 2020
** MyGimp
** File description:
** InvertSelectionOperation.cpp
*/
#include "InvertSelectionOperation.hpp"

Mimp::InvertSelectionOperation::InvertSelectionOperation():
	ImageOperation({"Selection", "Invert Selection"}, {KEY_I, true, false, false})
{}

void Mimp::InvertSelectionOperation::click(tgui::Gui &, Mimp::Image &image) const
{
	image.selectedArea.invert();
}