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
	class FrameBuffer {
	private:
		Vector2<unsigned int> _size;
		unsigned int *_pixelBuffer;

	public:
		FrameBuffer(const FrameBuffer &other);
		FrameBuffer(Vector2<unsigned int> size, const unsigned int *buffer);
		FrameBuffer(Vector2<unsigned int> size, const std::vector<Color> &buffer);
		FrameBuffer(Vector2<unsigned int> size, const Color &defaultColor = Color::Transparent);
		~FrameBuffer();

		const unsigned int *getBuffer() const;
		unsigned int &operator[](unsigned int index) const;
		Color getPixel(Vector2<int> pos, const Color &fill = Color::Transparent) const noexcept;
		Vector2<unsigned int> getSize() const noexcept;
		bool posIsOutOfBound(Vector2<int> pos) const noexcept;
		void drawPixel(Vector2<int> pos, const Color &color) noexcept;
		void drawLine(Vector2<int> pt1, Vector2<int> pt2, const Color &color) noexcept;
		void drawRect(Vector2<int> pos, Vector2<unsigned> size, const Color &color) noexcept;
		void drawEllipsoid(Vector2<int> pos, Vector2<unsigned> size, const Color &color) noexcept;
		void drawFrameBuffer(Vector2<int> pos, const FrameBuffer &buffer) noexcept;
		FrameBuffer getRectFromBuffer(Vector2<int> pos, Vector2<unsigned> size, const Color &fill = Color::Transparent);
		void clear(const Color &color) noexcept;
	};
}


#endif //MYGIMP_FRAMEBUFFER_HPP
