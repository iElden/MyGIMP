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
    //! @brief Define the InvertSelectionOperation.
	class InvertSelectionOperation : public ImageOperation {
	public:
	    //! @brief Constructor of the Invert Selection Operation
        InvertSelectionOperation();

        //! @brief Handles the click of the Inversion.
        //! @details Invert the selection on the image.
        //! @param gui The global gui (unused).
        //! @param image The image to edit.
		void click(tgui::Gui &gui, Image &image) const override;
	};
}


#endif //MYGIMP_INVERTSELECTIONOPERATION_HPP
