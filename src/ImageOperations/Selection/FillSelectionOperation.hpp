//
// Created by Gegel85 on 25/04/2020.
//

#ifndef MYGIMP_FILLSELECTIONOPERATION_HPP
#define MYGIMP_FILLSELECTIONOPERATION_HPP


#include "../ImageOperation.hpp"

namespace Mimp
{
    //! @brief Define the FillSelectionOperation.
    class FillSelectionOperation : public ImageOperation {
	private:
		static void _fill(Layer &layer, const SelectedArea &area, const Color &color);

	public:
        //! @brief Constructor of the Fill Selection Operation
        FillSelectionOperation();

        //! @brief Handles the click of the Filler.
        //! @details Expand the selection on the image.
        //! @param gui The global gui (unused).
        //! @param image The image to edit.
		void click(tgui::Gui &gui, Image &image) const override;
	};
}


#endif //MYGIMP_FILLSELECTIONOPERATION_HPP
