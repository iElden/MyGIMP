//
// Created by Gegel85 on 25/04/2020.
//

#ifndef MYGIMP_FILLSELECTIONOPERATION_HPP
#define MYGIMP_FILLSELECTIONOPERATION_HPP


#include "../ImageOperation.hpp"

namespace Mimp
{
	class FillSelectionOperation : public ImageOperation {
	private:
		static void _fill(Layer &layer, const SelectedArea &area, const Color &color);

	public:
		FillSelectionOperation();
		void click(tgui::Gui &gui, Image &image) const override;
	};
}


#endif //MYGIMP_FILLSELECTIONOPERATION_HPP
