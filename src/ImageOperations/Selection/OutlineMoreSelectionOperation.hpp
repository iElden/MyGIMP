/*
** EPITECH PROJECT, 2020
** MyGimp
** File description:
** OutlineMoreSelectionOperation.hpp
*/
#ifndef MYGIMP_OUTLINEMORESELECTIONOPERATION_HPP
#define MYGIMP_OUTLINEMORESELECTIONOPERATION_HPP

#include "../ImageOperation.hpp"

namespace Mimp {
	class OutlineMoreSelectionOperation : public ImageOperation {
	public:
		OutlineMoreSelectionOperation();
		void click(tgui::Gui &gui, Image &image) const override;
	};
}

#endif //MYGIMP_OUTLINEMORESELECTIONOPERATION_HPP
