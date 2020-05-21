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
    //! @brief Define the OutlineSelectionOperation.
    class OutlineSelectionOperation : public ImageOperation {
	public:
        //! @brief Do not call it directly. Use OutlineSelectionOperation::click.
        static void _keepPointIfNoPointNearby(unsigned i, unsigned j, Mimp::Image &image, const SelectedArea &area) noexcept;

        //! @brief Do not call it directly. Use OutlineSelectionOperation::click.
        static void _run(Image &image, int range=1) noexcept;

        //! @brief Constructor of the Outline Selection Operation
        OutlineSelectionOperation();

        //! @brief Handles the click of the Outline.
        //! @details Outline the selection on the image.
        //! @param gui The global gui (unused).
        //! @param image The image to edit.
		void click(tgui::Gui &gui, Image &image) const override;
	};
}


#endif //MYGIMP_OUTLINESELECTIONOPERATION_HPP
