/*
** EPITECH PROJECT, 2020
** MyGimp
** File description:
** UnselectOperation.cpp
*/
#include "UnselectOperation.hpp"

Mimp::UnselectOperation::UnselectOperation():
	ImageOperation({"Selection", "Unselect"})
{

}

void Mimp::UnselectOperation::click(tgui::Gui &, Mimp::Image &image) const
{
	image.selectedArea.clear();
}
