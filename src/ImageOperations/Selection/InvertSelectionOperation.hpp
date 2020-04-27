/*
** EPITECH PROJECT, 2020
** MyGimp
** File description:
** InvertSelectionOperation.hpp
*/
#ifndef MYGIMP_INVERTSELECTIONOPERATION_HPP
#define MYGIMP_INVERTSELECTIONOPERATION_HPP


#include "../ImageOperation.hpp"

namespace Mimp
{
	class InvertSelectionOperation : public ImageOperation {
	public:
		InvertSelectionOperation();
		void click(tgui::Gui &gui, Image &image) const override;
	};
}


#endif //MYGIMP_INVERTSELECTIONOPERATION_HPP
