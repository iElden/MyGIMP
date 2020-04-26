/*
** EPITECH PROJECT, 2020
** MyGimp
** File description:
** SelectAllOperation.cpp
*/
#include "SelectAllOperation.hpp"

Mimp::SelectAllOperation::SelectAllOperation():
	ImageOperation({"Selection", "Select all"})
{

}

void Mimp::SelectAllOperation::click(tgui::Gui &, Image &image) const
{
	image.selectedArea.clear();
	for (unsigned j = 0; j <= image.getImageSize().y; j++)
		for (unsigned i = 0; i <= image.getImageSize().x; i++)
			image.selectedArea.add(i, j);
}