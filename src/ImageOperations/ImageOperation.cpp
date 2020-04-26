//
// Created by Gegel85 on 25/04/2020.
//

#include "ImageOperation.hpp"

namespace Mimp
{
	ImageOperation::ImageOperation(const std::vector<std::string> &&hierarchy) :
		_hierarchy(hierarchy)
	{
	}

	const std::vector<std::string> &ImageOperation::getMenuHierarchy() const
	{
		return this->_hierarchy;
	}
}