#ifndef MYGIMP_SHORTCUTCOMPARATOR_HPP
#define MYGIMP_SHORTCUTCOMPARATOR_HPP

#include <memory>
#include "Keys.hpp"
#include "Action.hpp"

namespace Mimp {
	struct Compare {
		Keys::KeyCombination _kc;

		explicit Compare(Keys::KeyCombination kc) : _kc(kc) {}
	};
	bool operator==(const std::pair<std::string, std::shared_ptr<Action>> &other, const Compare& c) {
		return c._kc == other.second->getKeyCombination();
	}
	bool operator==(const Compare& c, const std::pair<std::string, std::shared_ptr<Action>> &other) {
		return c._kc == other.second->getKeyCombination();
	}

	bool operator==(const std::pair<std::string, Keys::KeyCombination> &other, const Compare& c) {
		return c._kc == other.second;
	}
	bool operator==(const Compare& c, const std::pair<std::string, Keys::KeyCombination> &other) {
		return c._kc == other.second;
	}
}

#endif //MYGIMP_SHORTCUTCOMPARATOR_HPP
