/*
** EPITECH PROJECT, 2020
** MyGimp
** File description:
** SelectAllOperation.hpp
*/
#ifndef MYGIMP_SELECTALLOPERATION_HPP
#define MYGIMP_SELECTALLOPERATION_HPP


#include "../ImageOperation.hpp"

namespace Mimp
{
	class SelectAllOperation : public ImageOperation {
	public:
		SelectAllOperation();
		void click(tgui::Gui &gui, Image &image) const override;
	};
}


#endif //MYGIMP_SELECTALLOPERATION_HPP
