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

	std::string KeyCombination::toString() const
	{
		std::string result;

		if (this->control)
			result += "Ctrl + ";
		if (this->shift)
			result += "Shift + ";
		if (this->alt)
			result += "Alt + ";
		result += KeyToString(this->key);
		return result;
	}

	std::string KeyToString(Key key)
	{
		switch (key) {
		case KEY_A:
			return "A";
		case KEY_B:
			return "B";
		case KEY_C:
			return "C";
		case KEY_D:
			return "D";
		case KEY_E:
			return "E";
		case KEY_F:
			return "F";
		case KEY_G:
			return "G";
		case KEY_H:
			return "H";
		case KEY_I:
			return "I";
		case KEY_J:
			return "J";
		case KEY_K:
			return "K";
		case KEY_L:
			return "L";
		case KEY_M:
			return "M";
		case KEY_N:
			return "N";
		case KEY_O:
			return "O";
		case KEY_P:
			return "P";
		case KEY_Q:
			return "Q";
		case KEY_R:
			return "R";
		case KEY_S:
			return "S";
		case KEY_T:
			return "T";
		case KEY_U:
			return "U";
		case KEY_V:
			return "V";
		case KEY_W:
			return "W";
		case KEY_X:
			return "X";
		case KEY_Y:
			return "Y";
		case KEY_Z:
			return "Z";
		case KEY_DEL:
			return "Del";
		case KEY_ESC:
			return "Esc";
		case KEY_UP:
			return "Up";
		case KEY_DOWN:
			return "Down";
		case KEY_LEFT:
			return "Left";
		case KEY_RIGHT:
			return "Right";
		default:
			return "Unknown";
		}
	}
}