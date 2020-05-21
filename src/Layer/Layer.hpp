//
// Created by Gegel85 on 06/04/2020.
//

#ifndef MYGIMP_LAYER_HPP
#define MYGIMP_LAYER_HPP

#include <string>
#include "../Data/Vector2.hpp"
#include "../Data/Color.hpp"
#include "FrameBuffer.hpp"

namespace Mimp
{
    //! @brief Define a Layer.
    struct Layer {
		FrameBuffer buffer; //!< FrameBuffer of the layer
		bool locked = false; //!< Is the layer locked on the screen ?
		bool visible = true; //!< Is the layer visible on the screen ?
		char name[32]; 		//!< Name of the layer
		Vector2<int> pos = {0, 0}; //!< Position of the layer

		//! @brief Constructor of the Layer
		//! @param size Size of the Layer
		//! @param buffer An array of colors to create the FrameBuffer of the Layer
		Layer(Vector2<unsigned int> size, const Color *buffer);

		//! @brief Constructor of the Layer
		//! @param size Size of the layer
		//! @param defaultColor Color of the FrameBuffer. Default is Transparent.
		Layer(Vector2<unsigned int> size, const Color &defaultColor = Color::Transparent);

		//! @brief Get the size of the layer
		//! @return Vector2<unsigned int> Contains the width and height of the layer
		Vector2<unsigned int> getSize() const noexcept;

		//! @brief Function that returns the state of the layer
		//! @return bool Locked State of the layer
		bool isLocked() const noexcept;
	};
}


#endif //MYGIMP_LAYER_HPP
