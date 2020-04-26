/*
** EPITECH PROJECT, 2020
** MyGimp
** File description:
** UnselectOperation.hpp
*/
#ifndef MYGIMP_UNSELECTOPERATION_HPP
#define MYGIMP_UNSELECTOPERATION_HPP


#include "../ImageOperation.hpp"

namespace Mimp
{
	class UnselectOperation : public ImageOperation {
	public:
		UnselectOperation();
		void click(tgui::Gui &gui, Image &image) const override;
	};
}


#endif //MYGIMP_UNSELECTOPERATION_HPP
