/*
** EPITECH PROJECT, 2020
** MyGimp
** File description:
** SelectAllOperation.cpp
*/
#include "SelectAllOperation.hpp"

Mimp::SelectAllOperation::SelectAllOperation():
	ImageOperation({"Selection", "Select all"}, {KEY_A, true, false, false})
{

}

void Mimp::SelectAllOperation::click(tgui::Gui &, Image &image) const
{
	image.selectedArea.fill();
}