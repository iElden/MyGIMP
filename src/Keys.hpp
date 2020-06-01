#ifndef MYGIMP_KEYS_HPP
#define MYGIMP_KEYS_HPP

#include <string>
#include <SFML/Window.hpp>

namespace Mimp::Keys {
	enum Key {
		KEY_UNKNOWN = -1,
		KEY_A,
		KEY_B,
		KEY_C,
		KEY_D,
		KEY_E,
		KEY_F,
		KEY_G,
		KEY_H,
		KEY_I,
		KEY_J,
		KEY_K,
		KEY_L,
		KEY_M,
		KEY_N,
		KEY_O,
		KEY_P,
		KEY_Q,
		KEY_R,
		KEY_S,
		KEY_T,
		KEY_U,
		KEY_V,
		KEY_W,
		KEY_X,
		KEY_Y,
		KEY_Z,
		KEY_DEL,
		KEY_ESC,
		KEY_UP,
		KEY_DOWN,
		KEY_LEFT,
		KEY_RIGHT,
		NB_OF_KEYS
	};

	//! @brief Convert a Key to a string
	//! @param key The key to convert.
	//! @return std::string
	std::string KeyToString(Key key);

	//! @brief Convert a string to a Key.
	//! @param s The string to convert.
	//! @return Key
	Key StringToKey(std::string s);

	//! @brief Struct defining a combination of keys.
	//! @details Holds the required key for a combination and some basic operations on keys.
	struct KeyCombination {
		Key key; //!< The key value
		bool control; //!< If the Control key has to be pressed or not.
		bool shift; //!< If the Shift key has to be pressed or not.
		bool alt; //!< If the Alt key has to be pressed or not.

		//! @brief Compare the combination with an other one.
		//! @return bool
		bool operator<(const KeyCombination &) const;

		bool operator==(const KeyCombination &other) const;

		//! @brief Return the string representation of the combination.
		//! @return std::string
		std::string toString() const;

		//! @brief Convert a string to a KeyCombination
		//! @param s The string to convert
		void fromString(std::string s);

		//! @brief Get the name of the Key.
		//! @return std::string
		std::string getKeyName() const
		{ return KeyToString(this->key); };
	};

	//! @brief Convert a sfml key to a mimp key
	//! @param key The key to convert
	//! @return The converted key
	Key SFMLKeyToKey(sf::Keyboard::Key key);
}


#endif //MYGIMP_KEYS_HPP
