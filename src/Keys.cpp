#include "Keys.hpp"

namespace Mimp::Keys {

	bool Keys::KeyCombination::operator<(const KeyCombination &other) const
	{
		auto val1 = this->control | (this->shift << 1) | (this->alt << 2) | (this->key << 3);
		auto val2 = other.control | (other.shift << 1) | (other.alt << 2) | (other.key << 3);

		return val1 < val2;
	}

	bool Keys::KeyCombination::operator==(const KeyCombination &other) const {
		return this->key == other.key && this->alt == other.alt && this->control == other.control && this->shift == other.shift;
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

	void KeyCombination::fromString(std::string s)
	{
		std::size_t position = 0;
		std::size_t ctrlPos = s.find("Ctrl + ");
		std::size_t shiftPos = s.find("Shift + ");
		std::size_t altPos = s.find("Alt + ");

		if (ctrlPos != std::string::npos) {
			this->control = true;
			position += 7;
		} else {
			this->control = false;
		}
		if (shiftPos != std::string::npos) {
			this->shift = true;
			position += 8;
		} else {
			this->shift = false;
		}
		if (altPos != std::string::npos) {
			this->alt = true;
			position += 6;
		} else {
			this->alt = false;
		}

		this->key = StringToKey(s.substr(position, s.length()));
	}

	Key StringToKey(std::string s)
	{
		if (s == "A")
			return KEY_A;
		if (s == "B")
			return KEY_B;
		if (s == "C")
			return KEY_C;
		if (s == "D")
			return KEY_D;
		if (s == "E")
			return KEY_E;
		if (s == "F")
			return KEY_F;
		if (s == "G")
			return KEY_G;
		if (s == "H")
			return KEY_H;
		if (s == "I")
			return KEY_I;
		if (s == "J")
			return KEY_J;
		if (s == "K")
			return KEY_K;
		if (s == "L")
			return KEY_L;
		if (s == "M")
			return KEY_M;
		if (s == "N")
			return KEY_N;
		if (s == "O")
			return KEY_O;
		if (s == "P")
			return KEY_P;
		if (s == "Q")
			return KEY_Q;
		if (s == "R")
			return KEY_R;
		if (s == "S")
			return KEY_S;
		if (s == "T")
			return KEY_T;
		if (s == "U")
			return KEY_U;
		if (s == "V")
			return KEY_V;
		if (s == "W")
			return KEY_W;
		if (s == "X")
			return KEY_X;
		if (s == "Y")
			return KEY_Y;
		if (s == "Z")
			return KEY_Z;
		if (s == "Del")
			return KEY_DEL;
		if (s == "Esc")
			return KEY_ESC;
		if (s == "Up")
			return KEY_UP;
		if (s == "Down")
			return KEY_DOWN;
		if (s == "Left")
			return KEY_LEFT;
		if (s == "Right")
			return KEY_RIGHT;
		return KEY_UNKNOWN;
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


	Key SFMLKeyToKey(sf::Keyboard::Key key)
	{
		switch (key) {
			case sf::Keyboard::Key::A:
				return KEY_A;
			case sf::Keyboard::Key::B:
				return KEY_B;
			case sf::Keyboard::Key::C:
				return KEY_C;
			case sf::Keyboard::Key::D:
				return KEY_D;
			case sf::Keyboard::Key::E:
				return KEY_E;
			case sf::Keyboard::Key::F:
				return KEY_F;
			case sf::Keyboard::Key::G:
				return KEY_G;
			case sf::Keyboard::Key::H:
				return KEY_H;
			case sf::Keyboard::Key::I:
				return KEY_I;
			case sf::Keyboard::Key::J:
				return KEY_J;
			case sf::Keyboard::Key::K:
				return KEY_K;
			case sf::Keyboard::Key::L:
				return KEY_L;
			case sf::Keyboard::Key::M:
				return KEY_M;
			case sf::Keyboard::Key::N:
				return KEY_N;
			case sf::Keyboard::Key::O:
				return KEY_O;
			case sf::Keyboard::Key::P:
				return KEY_P;
			case sf::Keyboard::Key::Q:
				return KEY_Q;
			case sf::Keyboard::Key::R:
				return KEY_R;
			case sf::Keyboard::Key::S:
				return KEY_S;
			case sf::Keyboard::Key::T:
				return KEY_T;
			case sf::Keyboard::Key::U:
				return KEY_U;
			case sf::Keyboard::Key::V:
				return KEY_V;
			case sf::Keyboard::Key::W:
				return KEY_W;
			case sf::Keyboard::Key::X:
				return KEY_X;
			case sf::Keyboard::Key::Y:
				return KEY_Y;
			case sf::Keyboard::Key::Z:
				return KEY_Z;
			case sf::Keyboard::Key::Delete:
				return KEY_DEL;
			case sf::Keyboard::Key::Escape:
				return KEY_ESC;
			case sf::Keyboard::Key::Up:
				return KEY_UP;
			case sf::Keyboard::Key::Down:
				return KEY_DOWN;
			case sf::Keyboard::Key::Left:
				return KEY_LEFT;
			case sf::Keyboard::Key::Right:
				return KEY_RIGHT;
			default:
				return KEY_UNKNOWN;
		}
	}
}
