//
// Created by Gegel85 on 06/04/2020.
//

#include <cstring>
#include "Layer.hpp"

namespace Mimp
{
	Layer::Layer(Vector2<unsigned int> size, unsigned *buffer) :
		buffer(size, buffer)
	{
		std::memset(this->name, 0, sizeof(this->name));
	}

	Layer::Layer(Vector2<unsigned int> size, const Color &defaultColor) :
		buffer(size, defaultColor)
	{
		std::memset(this->name, 0, sizeof(this->name));
	}

	Vector2<unsigned int> Layer::getSize() const noexcept
	{
		return this->buffer.getSize();
	}

	bool Layer::isLocked() const noexcept
	{
		return this->locked || !this->visible;
	}
}