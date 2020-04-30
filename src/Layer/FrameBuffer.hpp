//
// Created by Gegel85 on 06/04/2020.
//

#ifndef MYGIMP_FRAMEBUFFER_HPP
#define MYGIMP_FRAMEBUFFER_HPP


#include <vector>
#include "../Data/Vector2.hpp"
#include "../Data/Color.hpp"

namespace Mimp
{
	//! @brief FrameBuffer in Mimp
	class FrameBuffer {
	private:
		//! @brief Size of the framebuffer
		//! @details Vector2 with a width in x and a height in y
		Vector2<unsigned int> _size;
		//! @brief Buffer in an int array.
		unsigned int *_pixelBuffer;

	public:

		enum DrawStrategy {
			ADD,
			SET
		};

		//! @brief Copy Constructor of the framebuffer.
		//! @param other FrameBuffer to use
		FrameBuffer(const FrameBuffer &other);
		//! @brief Constructor of the framebuffer.
		//! @param size Size of the buffer
		//! @param buffer Buffer allocated (array)
		FrameBuffer(Vector2<unsigned int> size, const unsigned int *buffer);
		//! @brief Constructor of the framebuffer.
		//! @param size Size of the buffer
		//! @param buffer Buffer as std::vector
		FrameBuffer(Vector2<unsigned int> size, const std::vector<Color> &buffer);
		//! @brief Constructor of the framebuffer.
		//! @param size Size of the buffer
		//! @param defaultColor Color that will fill the buffer when created
		FrameBuffer(Vector2<unsigned int> size, const Color &defaultColor = Color::Transparent);
		//! @brief Destructor
		~FrameBuffer();

		//! @brief Get the buffer
		//! @return const unsigned int * Contains the buffer in readonly
		const unsigned int *getBuffer() const;
		//! @brief Get the value from the framebuffer at the given index.
		//! @param index Contains the index of the seeked value
		//! @return unsigned int & The value at the given index.
		unsigned int &operator[](unsigned int index) const;
		//! @brief Get the color value at the given index in the framebuffer.
		//! @param pos Position of the pixel
		//! @oaram fill Fill color if the position wasn't found
		//! @return Color The color at the given position.
		Color getPixel(Vector2<int> pos, const Color &fill = Color::Transparent) const noexcept;
		//! @brief Get the color value at the given index in the framebuffer.
		//! @param pos Position of the pixel
		//! @oaram fill Fill color if the position wasn't found
		//! @return Color The color at the given position or the color given in fill parameter.
		Vector2<unsigned int> getSize() const noexcept;
		//! @brief Is the position given out of bounds ?
		//! @param pos Position
		//! @return bool
		bool posIsOutOfBound(Vector2<int> pos) const noexcept;
		//! @brief Draw a pixel on the framebuffer
		//! @param pos Position
		//! @param color Color of the pixel
		void drawPixel(Vector2<int> pos, const Color &color, DrawStrategy drawStrategy=ADD) noexcept;
		//! @brief Set a pixel on the framebuffer
		//! @param pos Position
		//! @param color Color of the pixel
		void setPixel(Vector2<int> pos, const Color &color) noexcept;
		//! @brief Draw a line of pixels on the framebuffer
		//! @param pt1 First Position
		//! @param pt2 Second Position
		//! @param color Color of the line
		void drawLine(Vector2<int> pt1, Vector2<int> pt2, const Color &color, DrawStrategy drawStrategy=ADD) noexcept;
		//! @brief Draw the framebuffer given in parameter
		//! @param pos Position of the Framebuffer on the screen
		//! @param buffer The framebuffer to draw
		void drawFrameBuffer(Vector2<int> pos, const FrameBuffer &buffer, DrawStrategy drawStrategy=ADD) noexcept;
		//! @brief Get a Framebuffer from the screen
		//! @param pos Origin of the Framebuffer to get
		//! @param size Size of the Framebuffer to get
		//! @param color Color of the framebuffer if it failed to be obtained
		FrameBuffer getRectFromBuffer(Vector2<int> pos, Vector2<unsigned> size, const Color &fill = Color::Transparent);
		//! @brief Clear the screen with a color
		//! @param color Color used to clear
		void clear(const Color &color) noexcept;
	};
}


#endif //MYGIMP_FRAMEBUFFER_HPP
