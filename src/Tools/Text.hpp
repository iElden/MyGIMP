#ifndef MYGIMP_TEXT_HPP
#define MYGIMP_TEXT_HPP

#include "Tool.hpp"
#include "../ToolBox.hpp"

namespace Mimp {
	//! @brief Define a Text Tool.
	class Text : public Tool {
	public:

		//! @brief Construct a Text Tool
		//! @param toolBox ToolBox containing the Text Tool
		Text(ToolBox &toolBox);

		//! @brief Handle the mouse click of the Tool.
		//! @details Draw the text in the image.
		//! @param pos Position of the mouse
		//! @param click Mouse click state (unused)
		//! @param image The Image to edit
		void onClick(Vector2<int> pos, MouseClick click, Image &image) override;

		//! @brief Handle the mouse dragging of the Tool (unused).
		//! @param oldPos Old position of the mouse
		//! @param newPos New position of the mouse
		//! @param click Mouse click state
		//! @param image The Image to edit
		void onMouseDrag(Vector2<int> oldPos, Vector2<int> newPos, MouseClick click, Image &image) override
		{};

		//! @brief Get the parameters panel for the Tool.
		//! @return tgui::ScrollablePanel::Ptr Pointer containing the parameters panel
		tgui::ScrollablePanel::Ptr getParametersPanel() override;

		//! @brief Return the state of the Tool.
		bool isEditing() override
		{ return this->_edition; }

		//! @brief Handle the unselection of the Tool.
		void onUnselect() override;

	private:
		void getFontsFromPath(std::string systemPath);

		void getSystemFonts();

		void getCustomFonts();

		void getFonts();

	private:
		ToolBox &_toolBox;

		bool _edition = false;

		std::vector<std::string> _extensions{".ttf", ".otf", ".ttc", ".TTF"};

		int _fontSize = 13;
		std::wstring _text;
		std::string _fontPath = "";
		sf::Font _font;
		Color _color = Color::Black;
		std::string _selected = "";

		std::map<std::string, std::string> _fonts;

		bool _system = false;
	};
}


#endif //MYGIMP_TEXT_HPP
