/*
** EPITECH PROJECT, 2020
** MyGimp
** File description:
** OutlineSelectionOperation.hpp
*/
#ifndef MYGIMP_OUTLINESELECTIONOPERATION_HPP
#define MYGIMP_OUTLINESELECTIONOPERATION_HPP

#include "../ImageOperation.hpp"

namespace Mimp {
	class OutlineSelectionOperation : public ImageOperation {
	public:
		static void _keepPointIfNoPointNearby(unsigned i, unsigned j, Mimp::Image &image, const SelectedArea &area) noexcept;
		static void _run(Image &image, int range=1) noexcept;
		OutlineSelectionOperation();
		void click(tgui::Gui &gui, Image &image) const override;
	};
}


#endif //MYGIMP_OUTLINESELECTIONOPERATION_HPP
