/*
** EPITECH PROJECT, 2020
** MyGimp
** File description:
** ShrinkSelection.cpp
*/
#include "ShrinkSelection.hpp"
#include "../../CanvasWidget.hpp"

Mimp::ShrinkSelection::ShrinkSelection():
		ImageOperation({"Selection", "Shrink Selection"}, "Shrink Selection",{Keys::KEY_K, true, true, false})
{}

void Mimp::ShrinkSelection::_removePointIfNoPointNearby(unsigned i, unsigned j, Mimp::Image &image,
												   const Mimp::SelectedArea &area, int range) noexcept
{
	for (int a = -range; a <= range; a++)
		for (int b = -range; b <= range; b++)
			if (!area.pointInMap(i + a, j + b))
				return image.selectedArea.remove(i, j);
}

void Mimp::ShrinkSelection::_run(Mimp::Image &image, int range) noexcept
{
	auto selectedArea = image.selectedArea;
	for (auto pt : image.selectedArea.getPoints())
		ShrinkSelection::_removePointIfNoPointNearby(pt.x, pt.y, image, selectedArea, range);
}

void Mimp::ShrinkSelection::click(tgui::Gui &, CanvasWidget::Ptr image, tgui::ChildWindow::Ptr, Editor &) const
{
	ShrinkSelection::_run(*image);
}
