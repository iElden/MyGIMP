/*
** EPITECH PROJECT, 2020
** MyGimp
** File description:
** ExpandSelection.hpp
*/
#ifndef MYGIMP_EXPANDSELECTION_HPP
#define MYGIMP_EXPANDSELECTION_HPP

#include "../ImageOperation.hpp"

namespace Mimp {
	class ExpandSelection : public ImageOperation {
	public:
		static void _addPointIfPointNearby(unsigned i, unsigned j, Mimp::Image &image, const SelectedArea &area, int range) noexcept;
		static void _run(Image &image, int range=1) noexcept;
		ExpandSelection();
		void click(tgui::Gui &gui, Image &image) const override;
	};
}


#endif //MYGIMP_EXPANDSELECTION_HPP
