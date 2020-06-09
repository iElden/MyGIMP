//
// Created by Gegel85 on 06/04/2020.
//

#include <cstring>
#include <SFML/Graphics/Color.hpp>
#include <cmath>
#include "FrameBuffer.hpp"
#include "../Exceptions.hpp"

#include <iostream>

namespace Mimp
{

	FrameBuffer::FrameBuffer(Vector2<unsigned int> size, const Color *buffer) :
		_size(size)
	{
		this->_drawBuffer = new sf::Color[size.x * size.y];
		this->_pixelBuffer = new Color[size.x * size.y];
		std::memcpy(this->_pixelBuffer, buffer, size.x * size.y * sizeof(*this->_pixelBuffer));
		for (unsigned i = 0; i < size.x * size.y; i++)
			this->_drawBuffer[i] = this->_pixelBuffer[i];
	}

	FrameBuffer::FrameBuffer(Vector2<unsigned int> size, const std::vector<Color> &buffer) :
		_size(size)
	{
		this->_drawBuffer = new sf::Color[size.x * size.y];
		this->_pixelBuffer = new Color[size.x * size.y];
		for (unsigned i = 0; i < size.x * size.y; i++) {
			this->_pixelBuffer[i] = buffer[i];
			this->_drawBuffer[i] = this->_pixelBuffer[i];
		}
	}

	FrameBuffer::FrameBuffer(const FrameBuffer &other) :
		FrameBuffer(other.getSize(), other.getBuffer())
	{
	}

	FrameBuffer &FrameBuffer::operator=(const FrameBuffer &other)
	{
		auto size = other.getSize();
		auto buffer = other.getBuffer();

		auto drawBuffer = new sf::Color[size.x * size.y];
		auto pixelBuffer = new Color[size.x * size.y];

		std::memcpy(pixelBuffer, buffer, size.x * size.y * sizeof(*pixelBuffer));
		for (unsigned i = 0; i < size.x * size.y; i++)
			drawBuffer[i] = pixelBuffer[i];

		delete[] this->_drawBuffer;
		delete[] this->_pixelBuffer;

		this->_size = size;
		this->_drawBuffer = drawBuffer;
		this->_pixelBuffer = pixelBuffer;
		return *this;
	}

	FrameBuffer::FrameBuffer(Vector2<unsigned int> size, const Color &defaultColor) :
		_size(size)
	{
		this->_drawBuffer = new sf::Color[size.x * size.y];
		this->_pixelBuffer = new Color[size.x * size.y];
		for (unsigned i = 0; i < size.x * size.y; i++) {
			this->_pixelBuffer[i] = defaultColor;
			this->_drawBuffer[i] = this->_pixelBuffer[i];
		}
	}

	FrameBuffer::~FrameBuffer()
	{
		delete[] this->_pixelBuffer;
		delete[] this->_drawBuffer;
	}

	const Color *FrameBuffer::getBuffer() const
	{
		return this->_pixelBuffer;
	}

	Color FrameBuffer::operator[](unsigned int index) const
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
			this->setPixel(pos, this->getPixel(pos) + color);
			break;
		case SET:
			this->setPixel(pos, color);
		}
	}

	void FrameBuffer::drawLine(Vector2<int> pt1, Vector2<int> pt2, const Color &color, unsigned short thickness, DrawShape shape, DrawStrategy drawStrategy) noexcept
	{
		int dx = pt2.x - pt1.x;
		int dy = pt2.y - pt1.y;

		this->drawAt(pt2, color, thickness, shape, drawStrategy);
		if (dx > 0) {
			if (dy > 0) {
				// vecteur oblique dans le 1er quadran

				if (dx >= dy) {
					// vecteur diagonal ou oblique proche de l’horizontale, dans le 1er octant
					int e = dx;
					dx *= 2;
					dy *= 2 ;  // e est positif
					while (true) { // déplacements horizontaux
						this->drawAt(pt1, color, thickness, shape, drawStrategy);
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
						this->drawAt(pt1, color, thickness, shape, drawStrategy);
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
						this->drawAt(pt1, color, thickness, shape, drawStrategy);
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
						this->drawAt(pt1, color, thickness, shape, drawStrategy);
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
					this->drawAt(pt1, color, thickness, shape, drawStrategy);
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
						this->drawAt(pt1, color, thickness, shape, drawStrategy);
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
						this->drawAt(pt1, color, thickness, shape, drawStrategy);
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
						this->drawAt(pt1, color, thickness, shape, drawStrategy);
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
						this->drawAt(pt1, color, thickness, shape, drawStrategy);
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
					this->drawAt(pt1, color, thickness, shape, drawStrategy);
					pt1.x--;
				} while (pt2.x != pt1.x);

			}
		} else {  // dx = 0
			if (dy > 0) {
				do {
					this->drawAt(pt1, color, thickness, shape, drawStrategy);
					pt1.y++;
				} while (pt1.y != pt2.y);
			} else if (dy) {
				do {
					this->drawAt(pt1, color, thickness, shape, drawStrategy);
					pt1.y--;
				} while (pt1.y != pt2.y);
			}
		}
	}

	void FrameBuffer::drawFrameBuffer(Vector2<int> pos, const std::shared_ptr<FrameBuffer> &buffer, float rotation, DrawStrategy drawStrategy) noexcept
	{
		auto size = buffer->getSize();

		rotation = rotation * M_PI / 180;
		for (unsigned x = 0; x < size.x; x++)
			for (unsigned y = 0; y < size.x; y++) {
				auto col = buffer->getPixel({static_cast<int>(x), static_cast<int>(y)});
				auto c = cos(rotation);
				auto s = sin(rotation);

				if (rotation == 0)
					this->drawPixel({
						static_cast<int>(x + pos.x),
						static_cast<int>(y + pos.y)
					}, col, drawStrategy);
				else
					this->drawPoint({
						static_cast<float>(c * (x - size.x / 2.) - s * (y - size.y / 2.) + size.x / 2. + pos.x),
						static_cast<float>(s * (x - size.x / 2.) + c * (y - size.y / 2.) + size.y / 2. + pos.y)
					}, col, drawStrategy);
			}
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
		for (unsigned i = 0; i < this->_size.x * this->_size.y; i++) {
			this->_pixelBuffer[i] = color;
			this->_drawBuffer[i] = color;
		}
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
		this->_drawBuffer[pos.x + pos.y * this->_size.x] = sf::Color(static_cast<sf::Uint32>(color));
		this->_pixelBuffer[pos.x + pos.y * this->_size.x] = color;
	}

	void FrameBuffer::drawAt(Vector2<int> pos, const Color &color, unsigned short radius, DrawShape shape,
							 DrawStrategy drawStrategy) noexcept
	{
		switch (shape) {
		case DrawShape::CIRCLE:
			this->_drawCircleAt(pos, color, radius, drawStrategy);
			if (this->_symmetry.x) {
				int diff = this->_axis.y - pos.y;
				this->_drawCircleAt({pos.x, std::abs(diff) * (diff < 0 ? -1 : 1) + this->_axis.y}, color, radius, drawStrategy);
			}
			if (this->_symmetry.y) {
				int diff = this->_axis.x - pos.x;
				this->_drawCircleAt({std::abs(diff) * (diff < 0 ? -1 : 1) + this->_axis.x, pos.y}, color, radius, drawStrategy);
			}
			break;
		case DrawShape::SQUARE:
			this->_drawSquareAt(pos, color, radius, drawStrategy);
			if (this->_symmetry.x) {
				int diff = this->_axis.y - pos.y;
				this->_drawSquareAt({pos.x, std::abs(diff) * (diff < 0 ? -1 : 1) + this->_axis.y}, color, radius, drawStrategy);
			}
			if (this->_symmetry.y) {
				int diff = this->_axis.x - pos.x;
				this->_drawSquareAt({std::abs(diff) * (diff < 0 ? -1 : 1) + this->_axis.x, pos.y}, color, radius, drawStrategy);
			}
			break;
		case DrawShape::DIAMOND:
			this->_drawDiamondAt(pos, color, radius, drawStrategy);
			if (this->_symmetry.x) {
				int diff = this->_axis.y - pos.y;
				this->_drawDiamondAt({pos.x, std::abs(diff) * (diff < 0 ? -1 : 1) + this->_axis.y}, color, radius, drawStrategy);
			}
			if (this->_symmetry.y) {
				int diff = this->_axis.x - pos.x;
				this->_drawDiamondAt({std::abs(diff) * (diff < 0 ? -1 : 1) + this->_axis.x, pos.y}, color, radius, drawStrategy);
			}
			break;
		case DrawShape::NB_OF_SHAPES:
			return;
		}
	}

	void FrameBuffer::_drawCircleAt(Vector2<int> pos, const Color &color, unsigned short radius,
									DrawStrategy drawStrategy) noexcept
	{
		if (radius == 1)
			return this->drawPixel(pos, color, drawStrategy);

		float realRadius = radius / 2.f;
		float minX = pos.x - realRadius;
		float maxX = pos.x + realRadius;
		float minY = pos.y - realRadius;
		float maxY = pos.y + realRadius;

		for (float j = minY; j < maxY; j++)
			for (float i = minX; i < maxX; i++)
				if (std::pow(i - pos.x, 2) / std::pow(realRadius, 2) +
					std::pow(j - pos.y, 2) / std::pow(realRadius, 2) <= 1)
					this->drawPixel({
						static_cast<int>(std::ceil(i)),
						static_cast<int>(std::ceil(j))
					}, color, drawStrategy);
	}

	void FrameBuffer::_drawSquareAt(Vector2<int> pos, const Color &color, unsigned short radius, DrawStrategy drawStrategy) noexcept
	{
		int min_x = pos.x - radius / 2;
		int max_x = pos.x + (radius  - !(radius & 1U)) / 2;
		int min_y = pos.y - radius / 2;
		int max_y = pos.y + (radius  - !(radius & 1U)) / 2;
		for (int j = min_y; j <= max_y; j++)
			for (int i = min_x; i <= max_x; i++)
				this->drawPixel({i, j}, color, drawStrategy);
	}

	void FrameBuffer::_drawDiamondAt(Vector2<int> pos, const Color &color, unsigned short radius,
									 DrawStrategy drawStrategy) noexcept
	{
		int min_x = pos.x - radius / 2;
		int max_x = pos.x + radius / 2;
		int max_y = pos.y + radius / 2;
		for (int j = pos.y - radius / 2; j < max_y; j++)
			for (int i = min_x; i < max_x; i++)
				if (abs(pos.x - i) + abs(pos.y - j) < radius / 2)
					this->drawPixel({i, j}, color, drawStrategy);
	}

	const sf::Uint8 *FrameBuffer::getDrawBuffer() const
	{
		return reinterpret_cast<sf::Uint8 *>(this->_drawBuffer);
	}

	void FrameBuffer::drawPoint(Vector2<float> pos, const Color &color, DrawStrategy drawStrategy) noexcept
	{
		this->drawPixel({static_cast<int>(pos.x), static_cast<int>(pos.y)}, color, drawStrategy);
		if (std::floor(pos.x) != pos.x)
			this->drawPixel({static_cast<int>(pos.x + 1), static_cast<int>(pos.y)}, color, drawStrategy);
		if (std::floor(pos.y) != pos.y)
			this->drawPixel({static_cast<int>(pos.x), static_cast<int>(pos.y + 1)}, color, drawStrategy);
		if (std::floor(pos.x) != pos.x && std::floor(pos.y) != pos.y)
			this->drawPixel({static_cast<int>(pos.x + 1), static_cast<int>(pos.y + 1)}, color, drawStrategy);
	}
}