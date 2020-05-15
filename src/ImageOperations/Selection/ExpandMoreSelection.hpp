/*
** EPITECH PROJECT, 2020
** MyGimp
** File description:
** ExpandMoreSelection.hpp
*/
#ifndef MYGIMP_EXPANDMORESELECTION_HPP
#define MYGIMP_EXPANDMORESELECTION_HPP

#include "ExpandSelection.hpp"

namespace Mimp {
	class ExpandMoreSelection : public ImageOperation {
	public:
		ExpandMoreSelection();
		void click(tgui::Gui &gui, Image &image) const override;
	};
}


#endif //MYGIMP_EXPANDMORESELECTION_HPP
