/*
** EPITECH PROJECT, 2020
** MyGimp
** File description:
** ShrinkSelection.hpp
*/
#ifndef MYGIMP_SHRINKSELECTION_HPP
#define MYGIMP_SHRINKSELECTION_HPP


#include "../ImageOperation.hpp"

namespace Mimp {
    //! @brief Define the ShrinkSelection.
    class ShrinkSelection : public ImageOperation {
	public:
        //! @brief Do not call it directly. Use ShrinkSelection::click.
        static void _removePointIfNoPointNearby(unsigned i, unsigned j, Mimp::Image &image, const SelectedArea &area, int range) noexcept;

        //! @brief Do not call it directly. Use ShrinkSelection::click.
        static void _run(Image &image, int range=1) noexcept;

        //! @brief Constructor of the Shrink Selection Operation
		ShrinkSelection();

        //! @brief Handles the click of the ShrinkMore Selection Operation.
        //! @details Shrink the selection on the image.
        //! @param gui The global gui (unused).
        //! @param image The image to edit.
		void click(tgui::Gui &gui, Image &image) const override;
	};
}


#endif //MYGIMP_SHRINKSELECTION_HPP
