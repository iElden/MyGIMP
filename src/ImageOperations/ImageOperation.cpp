//
// Created by Gegel85 on 25/04/2020.
//

#include "ImageOperation.hpp"

namespace Mimp
{
	ImageOperation::ImageOperation(const std::vector<std::string> &&hierarchy) :
		_hierarchy(hierarchy),
		_keys()
	{
	}

	ImageOperation::ImageOperation(const std::vector<std::string> &&hierarchy, const KeyCombination &keys) :
		_hierarchy(hierarchy),
		_keys(keys)
	{
	}

	const std::vector<std::string> &ImageOperation::getMenuHierarchy() const
	{
		return this->_hierarchy;
	}

	std::optional<KeyCombination> ImageOperation::getKeyStroke() const
	{
		return this->_keys;
	}

	bool KeyCombination::operator<(const KeyCombination &other) const
	{
		auto val1 = this->control | (this->shift << 1) | (this->alt << 2) | (this->key << 3);
		auto val2 = other.control | (other.shift << 1) | (other.alt << 2) | (other.key << 3);

		return val1 < val2;
	}
}