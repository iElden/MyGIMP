//
// Created by Gegel85 on 25/04/2020.
//

#include "ImageOperation.hpp"
#include "../ShortcutManager.hpp"

namespace Mimp {
	ImageOperation::ImageOperation(const std::vector<std::string> &&hierarchy, const std::string &&name) :
			_hierarchy(hierarchy),
			_keys(),
			name(name){
	}

	ImageOperation::ImageOperation(const std::vector<std::string> &&hierarchy, const std::string &&name, const Keys::KeyCombination &keys) :
			_hierarchy(hierarchy),
			_keys(keys),
			name(name){
	}

	const std::vector<std::string> &ImageOperation::getMenuHierarchy() const {
		return this->_hierarchy;
	}

	std::optional<Keys::KeyCombination> ImageOperation::getKeyStroke() const {
		return this->_keys;
	}

	void ImageOperation::setKeyStroke(Keys::KeyCombination k) {
		this->_keys = k;
	}
}