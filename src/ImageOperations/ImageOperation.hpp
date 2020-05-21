//
// Created by Gegel85 on 25/04/2020.
//

#ifndef MYGIMP_IMAGEOPERATION_HPP
#define MYGIMP_IMAGEOPERATION_HPP


#include <TGUI/Gui.hpp>
#include "../Image.hpp"

namespace Mimp
{
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

		//! @brief Return the string representation of the combination.
		//! @return std::string
		std::string toString() const;
	};

    //! @brief Define the ImageOperation base class.
    class ImageOperation {
	private:
		std::vector<std::string> _hierarchy;
		std::optional<KeyCombination> _keys;

	protected:
	    //! @brief Constructor of ImageOperation
        //! @param hierarchy A vector of the hierarchy (ie : Menu title -> operation name)
		ImageOperation(const std::vector<std::string> &&hierarchy);

        //! @brief Constructor of ImageOperation
        //! @param hierarchy A vector of the hierarchy (ie : Menu title -> operation name)
        //! @param keys The key combination to invoke the operation.
		ImageOperation(const std::vector<std::string> &&hierarchy, const KeyCombination &keys);

	public:
	    //! @brief Handles the click. Must be override.
		virtual void click(tgui::Gui &, Image &) const = 0;

		//! @brief Get the hierarchy of a menu item.
		//! @return A vector of all the menu hierarchy.
		const std::vector<std::string> &getMenuHierarchy() const;

		//! @brief Get the possible key combination of the operation.
		//! @return The combination of the operation if it exists.
		std::optional<KeyCombination> getKeyStroke() const;
	};
}


#endif //MYGIMP_IMAGEOPERATION_HPP
