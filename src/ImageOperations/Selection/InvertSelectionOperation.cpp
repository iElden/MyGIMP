/*
** EPITECH PROJECT, 2020
** MyGimp
** File description:
** InvertSelectionOperation.cpp
*/
#include "InvertSelectionOperation.hpp"

Mimp::InvertSelectionOperation::InvertSelectionOperation():
	ImageOperation({"Selection", "Invert Selection"})
{}

void Mimp::InvertSelectionOperation::click(tgui::Gui &, Mimp::Image &image) const
{
	std::vector<Vector2<int>> oldSelected = image.selectedArea.copy();

	image.selectedArea.clear();
	for (int j = 0; j <= static_cast<int>(image.getImageSize().y); j++) {
		for (int i = 0; i <= static_cast<int>(image.getImageSize().x); i++) {
			Vector2<int> pt = {i, j};
			if (find(oldSelected.begin(), oldSelected.end(), pt) == oldSelected.end())
				image.selectedArea.add(pt);
		}
	}
}
