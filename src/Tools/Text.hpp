#ifndef MYGIMP_TEXT_HPP
#define MYGIMP_TEXT_HPP

#include "Tool.hpp"
#include "../ToolBox.hpp"

#include <iostream>

namespace Mimp {
	class Text : public Tool {
	public:
		Text(ToolBox &toolBox);

		void onClick(Vector2<int> pos, MouseClick click, Image &image) override;

		void onMouseDrag(Vector2<int>, Vector2<int>, MouseClick, Image &) override {};

		tgui::ScrollablePanel::Ptr getParametersPanel() override;

		bool isEditing() override { return this->_edition; }

		void onUnselect() override;

	private:
		void getFonts();

	private:
		ToolBox &_toolBox;

		bool _edition = false;

		int _fontSize = 13;
		std::wstring _text;
		std::string _fontPath = "";
		sf::Font _font;
		Color _color = Color::Black;
		std::string _selected = "";

		std::map<std::string, std::string> _fonts;
	};
}


#endif //MYGIMP_TEXT_HPP
