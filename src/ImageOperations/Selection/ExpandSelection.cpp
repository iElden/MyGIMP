/*
** EPITECH PROJECT, 2020
** MyGimp
** File description:
** ExpandSelection.cpp
*/
#include "ExpandSelection.hpp"
#include "../../Utils.hpp"


Mimp::ExpandSelection::ExpandSelection():
		ImageOperation({"Selection", "Expand Selection"}, {KEY_I, true, true, false})
{}

void Mimp::ExpandSelection::_add_point_if_point_neabrary(int i, int j, Mimp::Image &image, SelectedArea area) const noexcept
{
	for (int a = -1; a <= 1; a++)
		for (int b = -1; b <= 1; b++)
			if (!Utils::isOutOfBound({i + a, j + b}, image.getImageSize()) && area.pointInMap(i + a, j + b))
				return image.selectedArea.add(i, j);
}

void Mimp::ExpandSelection::click(tgui::Gui &, Mimp::Image &image) const
{
	int max_x = image.getImageSize().x;
	SelectedArea *selectedArea = image.selectedArea.copy();

	for (int j = 0; j < image.getImageSize().y; j++) {
		for (int i = 0; i < max_x; i++) {
			this->_add_point_if_point_neabrary(i, j, image, *selectedArea);
		}
	}
	delete selectedArea;
}
