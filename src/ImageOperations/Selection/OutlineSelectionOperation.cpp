/*
** EPITECH PROJECT, 2020
** MyGimp
** File description:
** OutlineSelectionOperation.cpp
*/

#include "OutlineSelectionOperation.hpp"
#include "ExpandSelection.hpp"

Mimp::OutlineSelectionOperation::OutlineSelectionOperation():
		ImageOperation({"Selection", "Outline Selection"}, {KEY_O, true, true, false})
{}

void Mimp::OutlineSelectionOperation::click(tgui::Gui &, Mimp::Image &image) const
{
	Mimp::OutlineSelectionOperation::_run(image);
}

void Mimp::OutlineSelectionOperation::_run(Mimp::Image &image, int range) noexcept
{
	auto selectedArea = image.selectedArea;
	for (auto pt : image.selectedArea.getPoints())
		OutlineSelectionOperation::_keepPointIfNoPointNearby(pt.x, pt.y, image, selectedArea);
	if (range > 1)
		ExpandSelection::_run(image, range);
}

void Mimp::OutlineSelectionOperation::_keepPointIfNoPointNearby(unsigned i, unsigned j, Mimp::Image &image, const Mimp::SelectedArea &area) noexcept
{
	for (int a = -1; a <= 1; a++)
		for (int b = -1; b <= 1; b++)
			if (!area.pointInMap(i + a, j + b))
				return;
	image.selectedArea.remove(i, j);
}

