//
// Created by Gegel85 on 06/04/2020.
//

#include <cstring>
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
		for (int i = 0; i < size.x * size.y; i++)
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
		for (int i = 0; i < size.x * size.y; i++)
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

	Color FrameBuffer::operator[](Vector2<int> pos) const noexcept
	{
		if (pos.x < 0)
			return Color::Transparent;
		if (pos.y < 0)
			return Color::Transparent;
		if (pos.x >= this->_size.x)
			return Color::Transparent;
		if (pos.y >= this->_size.y)
			return Color::Transparent;
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
		if (pos.x >= this->_size.x)
			return;
		if (pos.y >= this->_size.y)
			return;
		this->_pixelBuffer[pos.x + pos.y * this->_size.x] = this->operator[](pos) + color;
	}

	void FrameBuffer::drawLine(Vector2<int> pt1, Vector2<int> pt2) noexcept
	{
		//TODO: Draw line
	}

	void FrameBuffer::drawRect(Vector2<int> pos, Vector2<unsigned> size, const Color &color) noexcept
	{
		for (int x = 0; x < size.x; x++)
			this->drawPixel({x + pos.x, pos.y}, color);
		for (int x = 0; x < size.x; x++)
			this->drawPixel({x + pos.x, static_cast<int>(pos.y + size.y - 1)}, color);
		for (int y = 0; y < size.x; y++)
			this->drawPixel({pos.x, pos.y + y}, color);
		for (int y = 0; y < size.x; y++)
			this->drawPixel({static_cast<int>(pos.x + size.x - 1), pos.y + y}, color);
	}

	void FrameBuffer::drawEllipsoid(Vector2<int> pos, Vector2<unsigned> size, const Color &color) noexcept
	{
		//TODO: Draw ellipsoid
	}

	void FrameBuffer::drawFrameBuffer(Vector2<int> pos, const FrameBuffer &buffer) noexcept
	{
		auto size = buffer.getSize();

		for (int x = 0; x < size.x; x++)
			for (int y = 0; y < size.x; y++)
				this->drawPixel({x + pos.x, y + pos.y}, buffer[{x, y}]);
	}

	FrameBuffer FrameBuffer::getRectFromBuffer(Vector2<int> pos, Vector2<unsigned> size, const Color &fill)
	{
		FrameBuffer result(size);

		for (int x = 0; x < size.x; x++)
			for (int y = 0; y < size.x; y++)
				result[{x, y}] = this->operator[]({x, y});
		return result;
	}

	void FrameBuffer::clear(const Color &color) noexcept
	{
		for (int i = 0; i < this->_size.x * this->_size.y; i++)
			this->_pixelBuffer[i] = color;
	}
}