/*
** EPITECH PROJECT, 2020
** MyGimp
** File description:
** ShrinkSelection.hpp
*/
#ifndef MYGIMP_SHRINKSELECTION_HPP
#define MYGIMP_SHRINKSELECTION_HPP


#include "../ImageOperation.hpp"

namespace Mimp {
	class ShrinkSelection : public ImageOperation {
	public:
		static void _removePointIfNoPointNearby(unsigned i, unsigned j, Mimp::Image &image, const SelectedArea &area, int range) noexcept;
		static void _run(Image &image, int range=1) noexcept;
		ShrinkSelection();
		void click(tgui::Gui &gui, Image &image) const override;
	};
}


#endif //MYGIMP_SHRINKSELECTION_HPP
