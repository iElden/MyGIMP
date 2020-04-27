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

	std::string KeyToString(Key key);

	struct KeyCombination {
		Key key;
		bool control;
		bool shift;
		bool alt;

		bool operator<(const KeyCombination &) const;
		std::string toString() const;
	};

	class ImageOperation {
	private:
		std::vector<std::string> _hierarchy;
		std::optional<KeyCombination> _keys;

	protected:
		ImageOperation(const std::vector<std::string> &&hierarchy);
		ImageOperation(const std::vector<std::string> &&hierarchy, const KeyCombination &keys);

	public:
		virtual void click(tgui::Gui &, Image &) const = 0;
		const std::vector<std::string> &getMenuHierarchy() const;
		std::optional<KeyCombination> getKeyStroke() const;
	};
}


#endif //MYGIMP_IMAGEOPERATION_HPP
