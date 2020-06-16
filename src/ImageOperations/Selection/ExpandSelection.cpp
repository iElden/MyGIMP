/*
** EPITECH PROJECT, 2020
** MyGimp
** File description:
** ExpandSelection.cpp
*/
#include "ExpandSelection.hpp"
#include "../../Utils.hpp"
#include "../../Widgets/CanvasWidget.hpp"


Mimp::ExpandSelection::ExpandSelection():
	ImageOperation({"Selection", "Expand Selection"}, {Keys::KEY_I, true, true, false})
{}

void Mimp::ExpandSelection::_addPointIfPointNearby(unsigned i, unsigned j, Mimp::Image &image, const SelectedArea &area, int range) noexcept
{
	for (int a = -range; a <= range; a++)
		for (int b = -range; b <= range; b++)
			if (area.pointInMap(i + a, j + b))
				return image.selectedArea->add(i, j);
}

void Mimp::ExpandSelection::_run(Mimp::Image &image, int range) noexcept
{
	image.takeSelectionSnapshot();
	auto size = image.getImageSize();
	SelectedArea selectedArea = *image.selectedArea;

	for (unsigned j = 0; j < size.y; j++) {
		for (unsigned i = 0; i < size.x; i++) {
			ExpandSelection::_addPointIfPointNearby(i, j, image, selectedArea, range);
		}
	}
}

void Mimp::ExpandSelection::click(tgui::Gui &, CanvasWidget::Ptr image, tgui::ChildWindow::Ptr, Editor &) const
{
	ExpandSelection::_run(*image);
}
