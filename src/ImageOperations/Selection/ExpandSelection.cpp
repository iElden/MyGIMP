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

void Mimp::ExpandSelection::_addPointIfPointNearby(unsigned i, unsigned j, Mimp::Image &image, const SelectedArea &area) const noexcept
{
	for (int a = -1; a <= 1; a++)
		for (int b = -1; b <= 1; b++)
			if (area.pointInMap(i + a, j + b))
				return image.selectedArea.add(i, j);
}

void Mimp::ExpandSelection::click(tgui::Gui &, Mimp::Image &image) const
{
	auto size = image.getImageSize();
	SelectedArea selectedArea = image.selectedArea;

	for (unsigned j = 0; j < size.y; j++) {
		for (unsigned i = 0; i < size.x; i++) {
			this->_addPointIfPointNearby(i, j, image, selectedArea);
		}
	}
}