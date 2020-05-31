//
// Created by Gegel85 on 06/04/2020.
//

#ifndef MYGIMP_FRAMEBUFFER_HPP
#define MYGIMP_FRAMEBUFFER_HPP

#include <memory>
#include <vector>
#include "../Data/Vector2.hpp"
#include "../Data/Color.hpp"
#include "../Enum.hpp"

namespace Mimp
{
    //! @brief Define a FrameBuffer.
	class FrameBuffer {
	private:
		Vector2<unsigned int> _size;
		Color *_pixelBuffer;
		sf::Color *_drawBuffer;

		void _drawCircleAt(Vector2<int> pos, const Color &color, unsigned short radius, DrawStrategy drawStrategy) noexcept;
		void _drawSquareAt(Vector2<int> pos, const Color &color, unsigned short radius, DrawStrategy drawStrategy) noexcept;
		void _drawDiamondAt(Vector2<int> pos, const Color &color, unsigned short radius, DrawStrategy drawStrategy) noexcept;

	public:
		//! @brief Copy Constructor of the framebuffer.
		//! @param other FrameBuffer to copy.
		FrameBuffer(const FrameBuffer &other);

		//! @brief Constructor of the FrameBuffer.
		//! @param size Size of the buffer
		//! @param buffer Allocated buffer as array
		FrameBuffer(Vector2<unsigned int> size, const Color *buffer);

		//! @brief Constructor of the framebuffer.
		//! @param size Size of the buffer
		//! @param buffer Buffer as std::vector
		FrameBuffer(Vector2<unsigned int> size, const std::vector<Color> &buffer);

		//! @brief Constructor of the framebuffer.
		//! @param size Size of the buffer
		//! @param defaultColor Color that will fill the buffer when created.
		FrameBuffer(Vector2<unsigned int> size, const Color &defaultColor = Color::Transparent);

		//! @brief FrameBuffer Destructor
		~FrameBuffer();

		//! @brief Create a FrameBuffer from other one by assignation.
		//! @param other The FrameBuffer to copy.
		FrameBuffer &operator=(const FrameBuffer &other);

		//! @brief Get the buffer
		//! @return const Color * Contains the buffer in readonly mode
		const Color *getBuffer() const;

		//! @brief Get the DrawBuffer
		//! @return const sf::Uint * Contains the DrawBuffer in readonly mode
		const sf::Uint8 *getDrawBuffer() const;

		//! @brief Get the color from the framebuffer at the given index.
		//! @param index Contains the index of the seeked value
		//! @return Color & The value at the given index.
		Color operator[](unsigned int index) const;

		//! @brief Get the pixel at the given position, or the given color if the position is incorrect.
		//! \param pos The position of the seeked pixel.
		//! \param fill The color to return if the seeked pixel does not exist. Transparent by default.
		//! \return Color
		Color getPixel(Vector2<int> pos, const Color &fill = Color::Transparent) const noexcept;

		//! @brief Get the size of the FrameBuffer.
		//! @return Vector2<unsigned int>
		Vector2<unsigned int> getSize() const noexcept;

		//! @brief Is the position given out of bounds ?
		//! @param pos Position to test.
		//! @return bool
		bool posIsOutOfBound(Vector2<int> pos) const noexcept;

		//! @brief Draw a pixel in the FrameBuffer
		//! @param pos Position
		//! @param color Color of the pixel
		//! \param drawStrategy How the shape has to be drawn. Default is ADD.
		void drawPixel(Vector2<int> pos, const Color &color, DrawStrategy drawStrategy=ADD) noexcept;

		//! @brief Draw a DrawShape in the FrameBuffer
		//! \param pos The position of the shape.
		//! \param color The color of the shape.
		//! \param radius The radius of the shape. Default is Circle.
		//! \param shape The shape to draw.
		//! \param drawStrategy How the shape has to be drawn. Default is ADD.
		void drawAt(Vector2<int> pos, const Color &color, unsigned short radius, DrawShape shape, DrawStrategy drawStrategy=ADD) noexcept;

		//! @brief Set a pixel in the FrameBuffer
		//! @param pos Position of the pixel.
		//! @param color Color of the pixel.
		void setPixel(Vector2<int> pos, const Color &color) noexcept;

		//! @brief Draw a line of pixels in the FrameBuffer
		//! @param pt1 First Position
		//! @param pt2 Second Position
		//! @param color Color of the line
		//! @param thickness The thickness of the line
		//! @param shape The shape to draw.
		//! @param drawStrategy How the shape has to be drawn. Default is ADD.
		void drawLine(Vector2<int> pt1, Vector2<int> pt2, const Color &color, unsigned short thickness, DrawShape shape=CIRCLE, DrawStrategy drawStrategy=ADD) noexcept;

		//! @brief Draw the FrameBuffer given in parameter
		//! @param pos Position of the FrameBuffer on the screen
		//! @param buffer The FrameBuffer to draw
		//! @param drawStrategy How the shape has to be drawn. Default is ADD.
		void drawFrameBuffer(Vector2<int> pos, std::shared_ptr<FrameBuffer> buffer, DrawStrategy drawStrategy=ADD) noexcept;

		//! @brief Get a FrameBuffer rectangle from the screen
		//! @param pos Origin of the Framebuffer to get
		//! @param size Size of the Framebuffer to get
		//! @param fill Color of the FrameBuffer if it failed to be obtained. Default is Transparent.
		FrameBuffer getRectFromBuffer(Vector2<int> pos, Vector2<unsigned> size, const Color &fill = Color::Transparent);

		//! @brief Clear the FrameBuffer with a color
		//! @param color Color used to clear
		void clear(const Color &color) noexcept;
	};
}


#endif //MYGIMP_FRAMEBUFFER_HPP
