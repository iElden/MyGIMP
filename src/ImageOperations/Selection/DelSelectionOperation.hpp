/*
** EPITECH PROJECT, 2020
** MyGimp
** File description:
** DelSelectionOperation.hpp
*/
#ifndef MYGIMP_DELSELECTIONOPERATION_HPP
#define MYGIMP_DELSELECTIONOPERATION_HPP


#include "FillSelectionOperation.hpp"
#include "../ImageOperation.hpp"

namespace Mimp
{
	class DelSelectionOperation : public ImageOperation {
	private:
		void _fill(Layer &layer, const SelectedArea &area, const Color &color);
	public:
		DelSelectionOperation();
		void click(tgui::Gui &gui, Image &image) const override;
	};
}

#endif //MYGIMP_DELSELECTIONOPERATION_HPP
