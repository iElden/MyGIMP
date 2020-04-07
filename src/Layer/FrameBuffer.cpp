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
		std::memcpy(this->_pixelBuffer, buffer, size.x * size.y);
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
		if (pos.x < 0)
			return fill;
		if (pos.y < 0)
			return fill;
		if (static_cast<unsigned>(pos.x) >= this->_size.x)
			return fill;
		if (static_cast<unsigned>(pos.y) >= this->_size.y)
			return fill;
		return this->operator[](pos.x + pos.y * this->_size.x);
	}

	Vector2<unsigned int> FrameBuffer::getSize() const noexcept
	{
		return this->_size;
	}

	void FrameBuffer::drawPixel(Vector2<int> pos, const Color &color) noexcept
	{
		if (pos.x < 0)
			return;
		if (pos.y < 0)
			return;
		if (static_cast<unsigned>(pos.x) >= this->_size.x)
			return;
		if (static_cast<unsigned>(pos.y) >= this->_size.y)
			return;
		this->_pixelBuffer[pos.x + pos.y * this->_size.x] = this->getPixel(pos) + color;
	}

	void FrameBuffer::drawLine(Vector2<int> pt1, Vector2<int> pt2, const Color &color) noexcept
	{
		/*procédure tracerSegment(entier x1, entier y1, entier x2, entier y2) est
		déclarer entier dx, dy;

		si (dx ← x2 - x1) ≠ 0 alors
			si dx > 0 alors
				si (dy ← y2 - y1) ≠ 0 alors
					si dy > 0 alors
						// vecteur oblique dans le 1er quadran

						si dx ≥ dy alors
							// vecteur diagonal ou oblique proche de l’horizontale, dans le 1er octant
							déclarer entier e ;
							dx ← (e ← dx) × 2 ; dy ← dy × 2 ;  // e est positif
							boucle sans fin  // déplacements horizontaux
								tracePixel(x1, y1) ;
								interrompre boucle si (x1 ← x1 + 1) = x2 ;
								si (e ← e - dy) < 0 alors
									y1 ← y1 + 1 ;  // déplacement diagonal
									e ← e + dx ;
								fin si ;
							fin boucle ;
						sinon
							// vecteur oblique proche de la verticale, dans le 2d octant
							déclarer entier e ;
							dy ← (e ← dy) × 2 ; dx ← dx × 2 ;  // e est positif
							boucle sans fin  // déplacements verticaux
								tracePixel(x1, y1) ;
									interrompre boucle si (y1 ← y1 + 1) = y2 ;
									si (e ← e - dx) < 0 alors
									x1 ← x1 + 1 ;  // déplacement diagonal
									e ← e + dy ;
								fin si ;
							fin boucle ;
						fin si ;

					sinon  // dy < 0 (et dx > 0)
						// vecteur oblique dans le 4e cadran

						si dx ≥ -dy alors
							// vecteur diagonal ou oblique proche de l’horizontale, dans le 8e octant
							déclarer entier e ;
							dx ← (e ← dx) × 2 ; dy ← dy × 2 ;  // e est positif
							boucle sans fin  // déplacements horizontaux
								tracePixel(x1, y1) ;
								interrompre boucle si (x1 ← x1 + 1) = x2 ;
								si (e ← e + dy) < 0 alors
									y1 ← y1 - 1 ;  // déplacement diagonal
									e ← e + dx ;
								fin si ;
							fin boucle ;
						sinon  // vecteur oblique proche de la verticale, dans le 7e octant
							déclarer entier e ;
							dy ← (e ← dy) × 2 ; dx ← dx × 2 ;  // e est négatif
							boucle sans fin  // déplacements verticaux
								tracePixel(x1, y1) ;
								interrompre boucle si (y1 ← y1 - 1) = y2 ;
								si (e ← e + dx) > 0 alors
									x1 ← x1 + 1 ;  // déplacement diagonal
									e ← e + dy ;
								fin si ;
							fin boucle ;
						fin si ;

					fin si ;
				sinon  // dy = 0 (et dx > 0)

					// vecteur horizontal vers la droite
					répéter
						tracePixel(x1, y1) ;
					jusqu’à ce que (x1 ← x1 + 1) = x2 ;

				fin si ;
			sinon  // dx < 0
				si (dy ← y2 - y1) ≠ 0 alors
					si dy > 0 alors
						// vecteur oblique dans le 2d quadran

						si -dx ≥ dy alors
							// vecteur diagonal ou oblique proche de l’horizontale, dans le 4e octant
							déclarer entier e ;
							dx ← (e ← dx) × 2 ; dy ← dy × 2 ;  // e est négatif
							boucle sans fin  // déplacements horizontaux
								tracePixel(x1, y1) ;
								interrompre boucle si (x1 ← x1 - 1) = x2 ;
								si (e ← e + dy) ≥ 0 alors
									y1 ← y1 + 1 ;  // déplacement diagonal
									e ← e + dx ;
								fin si ;
							fin boucle ;
						sinon
							// vecteur oblique proche de la verticale, dans le 3e octant
							déclarer entier e ;
							dy ← (e ← dy) × 2 ; dx ← dx × 2 ;  // e est positif
							boucle sans fin  // déplacements verticaux
								tracePixel(x1, y1) ;
								interrompre boucle si (y1 ← y1 + 1) = y2 ;
								si (e ← e + dx) ≤ 0 alors
									x1 ← x1 - 1 ;  // déplacement diagonal
									e ← e + dy ;
								fin si ;
							fin boucle ;
						fin si ;

					sinon  // dy < 0 (et dx < 0)
						// vecteur oblique dans le 3e cadran

						si dx ≤ dy alors
							// vecteur diagonal ou oblique proche de l’horizontale, dans le 5e octant
							déclarer entier e ;
							dx ← (e ← dx) × 2 ; dy ← dy × 2 ;  // e est négatif
							boucle sans fin  // déplacements horizontaux
								tracePixel(x1, y1) ;
								interrompre boucle si (x1 ← x1 - 1) = x2 ;
								si (e ← e - dy) ≥ 0 alors
									y1 ← y1 - 1 ;  // déplacement diagonal
									e ← e + dx ;
								fin si ;
							fin boucle ;
						sinon  // vecteur oblique proche de la verticale, dans le 6e octant
							déclarer entier e ;
							dy ← (e ← dy) × 2 ; dx ← dx × 2 ;  // e est négatif
							boucle sans fin  // déplacements verticaux
								tracePixel(x1, y1) ;
								interrompre boucle si (y1 ← y1 - 1) = y2 ;
								si (e ← e - dx) ≥ 0 alors
									x1 ← x1 - 1 ;  // déplacement diagonal
									e ← e + dy ;
								fin si ;
							fin boucle ;
						fin si ;

					fin si ;
				sinon  // dy = 0 (et dx < 0)

					// vecteur horizontal vers la gauche
					répéter
						tracePixel(x1, y1) ;
					jusqu’à ce que (x1 ← x1 - 1) = x2 ;

				fin si ;
			fin si ;
		sinon  // dx = 0
			si (dy ← y2 - y1) ≠ 0 alors
				si dy > 0 alors

					// vecteur vertical croissant
					répéter
						tracePixel(x1, y1) ;
					jusqu’à ce que (y1 ← y1 + 1) = y2 ;

				sinon  // dy < 0 (et dx = 0)

					// vecteur vertical décroissant
					répéter
						tracePixel(x1, y1) ;
					jusqu’à ce que (y1 ← y1 - 1) = y2 ;

				fin si ;
			fin si ;
		fin si ;*/
		//TODO: Implement the above algorithm
	}

	void FrameBuffer::drawRect(Vector2<int> pos, Vector2<unsigned> size, const Color &color) noexcept
	{
		for (unsigned x = 0; x < size.x; x++)
			this->drawPixel({static_cast<int>(x + pos.x), pos.y}, color);
		for (unsigned x = 0; x < size.x; x++)
			this->drawPixel({static_cast<int>(x + pos.x), static_cast<int>(pos.y + size.y - 1)}, color);
		for (unsigned y = 0; y < size.x; y++)
			this->drawPixel({pos.x, static_cast<int>(pos.y + y)}, color);
		for (unsigned y = 0; y < size.x; y++)
			this->drawPixel({static_cast<int>(pos.x + size.x - 1), static_cast<int>(pos.y + y)}, color);
	}

	void FrameBuffer::drawEllipsoid(Vector2<int> pos, Vector2<unsigned> size, const Color &color) noexcept
	{
		static_cast<void>(pos);
		static_cast<void>(size);
		static_cast<void>(color);
		//TODO: Draw ellipsoid
	}

	void FrameBuffer::drawFrameBuffer(Vector2<int> pos, const FrameBuffer &buffer) noexcept
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
					})
				);
	}

	FrameBuffer FrameBuffer::getRectFromBuffer(Vector2<int> pos, Vector2<unsigned> size, const Color &fill)
	{
		FrameBuffer result(size);

		for (unsigned x = 0; x < size.x; x++)
			for (unsigned y = 0; y < size.x; y++) {
				result.drawPixel({
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
}