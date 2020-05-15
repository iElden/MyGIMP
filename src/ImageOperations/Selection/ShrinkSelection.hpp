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
	protected:
		void _removePointIfNoPointNearby(unsigned i, unsigned j, Mimp::Image &image, const SelectedArea &area, int range) const noexcept;
		void _run(Image &image, int range=1) const noexcept;
	public:
		ShrinkSelection();
		void click(tgui::Gui &gui, Image &image) const override;
	};
}


#endif //MYGIMP_SHRINKSELECTION_HPP
