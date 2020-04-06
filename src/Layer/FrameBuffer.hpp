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
		FrameBuffer(Vector2<unsigned int> size, const unsigned int *buffer);
		FrameBuffer(Vector2<unsigned int> size, const std::vector<Color> &buffer);
		FrameBuffer(Vector2<unsigned int> size, const Color &defaultColor = Color::Transparent);
		~FrameBuffer();

		unsigned int *getBuffer();
		Color operator[](unsigned int index) const;
		Color operator[](Vector2<unsigned> pos) const;
		Vector2<unsigned int> getSize() const noexcept;
		void drawPixel(Vector2<unsigned> pos, const Color &color) noexcept;
		void drawLine(Vector2<unsigned> pt1, Vector2<unsigned> pt2) noexcept;
		void drawRect(Vector2<unsigned> pos, Vector2<unsigned> size, const Color &color) noexcept;
		void drawEllipsoid(Vector2<unsigned> pos, Vector2<unsigned> size, const Color &color) noexcept;
		void drawFrameBuffer(Vector2<unsigned> pos, const FrameBuffer &buffer) noexcept;
		FrameBuffer getRectFromBuffer(Vector2<int> pos, Vector2<unsigned> size, const Color &fill = Color::Transparent);
		void clear(const Color &color) noexcept;
	};
}


#endif //MYGIMP_FRAMEBUFFER_HPP
