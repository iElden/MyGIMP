//
// Created by Gegel85 on 06/04/2020.
//

#include <cstring>
#include <SFML/Graphics/Color.hpp>
#include "FrameBuffer.hpp"
#include "../Exceptions.hpp"

namespace Mimp
{

	FrameBuffer::FrameBuffer(Vector2<unsigned int> size, const unsigned int *buffer) :
		_size(size)
	{
		this->_pixelBuffer = new unsigned int[size.x * size.y];
		std::memcpy(this->_pixelBuffer, buffer, size.x * size.y * sizeof(*this->_pixelBuffer));
	}

	FrameBuffer::FrameBuffer(Vector2<unsigned int> size, const std::vector<Color> &buffer) :
		_size(size)
	{
		this->_pixelBuffer = new unsigned int[size.x * size.y];
		for (unsigned i = 0; i < size.x * size.y; i++)
			this->_pixelBuffer[i] = buffer[i];
	}

	FrameBuffer::FrameBuffer(const FrameBuffer &other) :
		FrameBuffer(other.getSize(), other.getBuffer())
	{
	}

	FrameBuffer::FrameBuffer(Vector2<unsigned int> size, const Color &defaultColor) :
		_size(size)
	{
		this->_pixelBuffer = new unsigned int[size.x * size.y];
		for (unsigned i = 0; i < size.x * size.y; i++)
			this->_pixelBuffer[i] = defaultColor;
	}

	FrameBuffer::~FrameBuffer()
	{
		delete[] this->_pixelBuffer;
	}

	const unsigned int *FrameBuffer::getBuffer() const
	{
		return this->_pixelBuffer;
	}

	unsigned int &FrameBuffer::operator[](unsigned int index) const
	{
		if (index >= this->_size.x * this->_size.y)
			throw OutOfBoundException(std::to_string(index) + " >= " + std::to_string(this->_size.x) + " * " + std::to_string(this->_size.y));
		return this->_pixelBuffer[index];
	}

	Color FrameBuffer::getPixel(Vector2<int> pos, const Color &fill) const noexcept
	{
		if (this->posIsOutOfBound(pos))
			return fill;
		return this->operator[](pos.x + pos.y * this->_size.x);
	}

	Vector2<unsigned int> FrameBuffer::getSize() const noexcept
	{
		return this->_size;
	}

	void FrameBuffer::drawPixel(Vector2<int> pos, const Color &color, DrawStrategy drawStrategy) noexcept
	{
		if (this->posIsOutOfBound(pos))
			return;
		switch (drawStrategy) {
		case ADD:
			this->_pixelBuffer[pos.x + pos.y * this->_size.x] = this->getPixel(pos) + color;
			break;
		case SET:
			this->_pixelBuffer[pos.x + pos.y * this->_size.x] = color;
		}
	}

	void FrameBuffer::drawLine(Vector2<int> pt1, Vector2<int> pt2, const Color &color, DrawStrategy drawStrategy) noexcept
	{
		int dx = pt2.x - pt1.x;
		int dy = pt2.y - pt1.y;

		if (dx > 0) {
			if (dy > 0) {
				// vecteur oblique dans le 1er quadran

				if (dx >= dy) {
					// vecteur diagonal ou oblique proche de l’horizontale, dans le 1er octant
					int e = dx;
					dx *= 2;
					dy *= 2 ;  // e est positif
					while (true) { // déplacements horizontaux
						this->drawPixel(pt1, color, drawStrategy);
						pt1.x++;
						if (pt1.x == pt2.x)
							break;
						e -= dy;
						if (e < 0) {
							pt1.y++;  // déplacement diagonal
							e += dx ;
						}
					}
				} else {
					// vecteur oblique proche de la verticale, dans le 2d octant
					int e = dy;
					dy *= 2;
					dx *= 2;  // e est positif
					while (true) {  // déplacements verticaux
						this->drawPixel(pt1, color, drawStrategy);
						pt1.y++;
						if (pt1.y == pt2.y)
							break;
						e -= dx;
						if (e < 0) {
							pt1.x++;  // déplacement diagonal
							e += dy;
						}
					}
				}

			} else if (dy) {  // dy < 0 (et dx > 0)
				// vecteur oblique dans le 4e cadran

				if (dx >= -dy) {
					// vecteur diagonal ou oblique proche de l’horizontale, dans le 8e octant
					int e = dx;
					dx *= 2;
					dy *= 2 ;  // e est positif
					while (true) {  // déplacements horizontaux
						this->drawPixel(pt1, color, drawStrategy);
						pt1.x++;
						if (pt1.x == pt2.x)
							break;
						e += dy;
						if (e < 0) {
							pt1.y--;  // déplacement diagonal
							e += dx;
						}
					}
				} else {  // vecteur oblique proche de la verticale, dans le 7e octant
					int e = dy;
					dy *= 2;
					dx *= 2;  // e est négatif
					while (true) {  // déplacements verticaux
						this->drawPixel(pt1, color, drawStrategy);
						pt1.y--;
						if (pt1.y == pt2.y)
							break;
						e += dx;
						if (e > 0) {
							pt1.x++;  // déplacement diagonal
							e += dy;
						}
					}
				}
			} else { // dy = 0 (et dx > 0)
				do {
					this->drawPixel(pt1, color, drawStrategy);
					pt1.x++;
				} while (pt2.x != pt1.x);
			}
		} else if (dx) {  // dx < 0
			if (dy > 0) {
				// vecteur oblique dans le 2d quadran

				if (-dx >= dy) {
					// vecteur diagonal ou oblique proche de l’horizontale, dans le 4e octant
					int e = dx;
					dx *= 2;
					dy *= 2;  // e est négatif
					while (true) {  // déplacements horizontaux
						this->drawPixel(pt1, color, drawStrategy);
						pt1.x--;
						if (pt1.x == pt2.x)
							break;
						e += dy;
						if (e >= 0) {
							pt1.y++;  // déplacement diagonal
							e += dx;
						}
					}
				} else {
					// vecteur oblique proche de la verticale, dans le 3e octant
					int e = dy;
					dy *= 2;
					dx *= 2;  // e est positif
					while (true) {  // déplacements verticaux
						this->drawPixel(pt1, color, drawStrategy);
						pt1.y++;
						if (pt1.y == pt2.y)
							break;
						e += dx;
						if (e <= 0) {
							pt1.x--;  // déplacement diagonal
							e += dy;
						}
					}
				}

			} else if (dy) { // dy < 0 (et dx < 0)
				// vecteur oblique dans le 3e cadran

				if (dx <= dy) {
					// vecteur diagonal ou oblique proche de l’horizontale, dans le 5e octant
					int e = dx;
					dx *= 2;
					dy *= 2;  // e est négatif
					while (true) {  // déplacements horizontaux
						this->drawPixel(pt1, color, drawStrategy);
						pt1.x--;
						if (pt1.x == pt2.x)
							break;
						e -= dy;
						if (e >= 0) {
							pt1.y--;  // déplacement diagonal
							e += dx;
						}
					}
				} else {  // vecteur oblique proche de la verticale, dans le 6e octant
					int e = dy;

					dy *= 2;
					dx *= 2;  // e est négatif
					while (true) {  // déplacements verticaux
						this->drawPixel(pt1, color, drawStrategy);
						pt1.y--;
						if (pt1.y == pt2.y)
							break;
						e -= dx;
						if (e >= 0) {
							pt1.x--;  // déplacement diagonal
							e += dy;
						}
					}
				}
			} else {  // dy = 0 (et dx < 0)

				// vecteur horizontal vers la gauche
				do {
					this->drawPixel(pt1, color, drawStrategy);
					pt1.x--;
				} while (pt2.x != pt1.x);

			}
		} else {  // dx = 0
			if (dy > 0) {
				do {
					this->drawPixel(pt1, color, drawStrategy);
					pt1.y++;
				} while (pt1.y != pt2.y);
			} else if (dy) {
				do {
					this->drawPixel(pt1, color, drawStrategy);
					pt1.y--;
				} while (pt1.y != pt2.y);
			}
		}
		//TODO: Implement the above algorithm
	}

	void FrameBuffer::drawFrameBuffer(Vector2<int> pos, const FrameBuffer &buffer, DrawStrategy drawStrategy) noexcept
	{
		auto size = buffer.getSize();

		for (unsigned x = 0; x < size.x; x++)
			for (unsigned y = 0; y < size.x; y++)
				this->drawPixel(
					{
						static_cast<int>(x + pos.x),
						static_cast<int>(y + pos.y)
					}, buffer.getPixel({
						static_cast<int>(x),
						static_cast<int>(y)
					}, drawStrategy)
				);
	}

	FrameBuffer FrameBuffer::getRectFromBuffer(Vector2<int> pos, Vector2<unsigned> size, const Color &fill)
	{
		FrameBuffer result(size);

		for (unsigned x = 0; x < size.x; x++)
			for (unsigned y = 0; y < size.x; y++) {
				result.setPixel({
					static_cast<int>(x),
					static_cast<int>(y)
				}, this->getPixel({
					static_cast<int>(x + pos.x),
					static_cast<int>(y + pos.y)
				}, fill));
			}
		return result;
	}

	void FrameBuffer::clear(const Color &color) noexcept
	{
		for (unsigned i = 0; i < this->_size.x * this->_size.y; i++)
			this->_pixelBuffer[i] = color;
	}

	bool FrameBuffer::posIsOutOfBound(Vector2<int> pos) const noexcept
	{
		if (pos.x < 0)
			return true;
		if (pos.y < 0)
			return true;
		if (static_cast<unsigned>(pos.x) >= this->_size.x)
			return true;
		return static_cast<unsigned>(pos.y) >= this->_size.y;
	}

	void FrameBuffer::setPixel(Vector2<int> pos, const Color &color) noexcept
	{
		if (this->posIsOutOfBound(pos))
			return;
		this->_pixelBuffer[pos.x + pos.y * this->_size.x] = color;
	}
}