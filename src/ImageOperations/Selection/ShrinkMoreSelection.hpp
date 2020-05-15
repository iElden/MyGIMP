/*
** EPITECH PROJECT, 2020
** MyGimp
** File description:
** ShrinkMoreSelection.hpp
*/
#ifndef MYGIMP_SHRINKMORESELECTION_HPP
#define MYGIMP_SHRINKMORESELECTION_HPP


#include "../ImageOperation.hpp"

namespace Mimp {
	class ShrinkMoreSelection : public ImageOperation {
	public:
		ShrinkMoreSelection();
		void click(tgui::Gui &gui, Image &image) const override;
	};
}


#endif //MYGIMP_SHRINKMORESELECTION_HPP
