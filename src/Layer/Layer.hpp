//
// Created by Gegel85 on 06/04/2020.
//

#ifndef MYGIMP_LAYER_HPP
#define MYGIMP_LAYER_HPP

#include <string>
#include <memory>
#include "../Data/Vector2.hpp"
#include "../Data/Color.hpp"
#include "FrameBuffer.hpp"

namespace Mimp
{
	//! @brief Layer
	//! @details FrameBuffer that you can put above the main Framebuffer.
	struct Layer {
		//! @brief FrameBuffer of the layer
		std::shared_ptr<FrameBuffer> buffer;
		//! @brief Is the layer locked on the screen ?
		bool locked = false;
		//! @brief Is the layer visible on the screen ?
		bool visible = true;
		//! @brief Name of the layer
		char name[32];
		//! @brief Position of the layer
		Vector2<int> pos = {0, 0};

		FrameBuffer getFrameBuffer() noexcept;
		//! @brief Constructor of the Layer
		//! @param size Size of the layer
		//! @param buffer Framebuffer of the layer
		Layer(Vector2<unsigned int> size, const Color *buffer);
		//! @brief Constructor of the Layer
		//! @param size Size of the layer
		//! @param color Color of the framebuffer
		Layer(Vector2<unsigned int> size, const Color &defaultColor = Color::Transparent);

		//! @brief Get the size of the layer
		//! @return Vector2<unsigned int> Contains the width and height of the layer
		Vector2<unsigned int> getSize() const noexcept;
		//! @brief Function that returns the "locked" state of the layer
		//! @return bool Locked State of the layer
		bool isLocked() const noexcept;
	};
}


#endif //MYGIMP_LAYER_HPP
