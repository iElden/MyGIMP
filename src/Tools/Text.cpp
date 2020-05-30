#include "Text.hpp"
#include <TGUI/TGUI.hpp>

#include <iostream>

namespace Mimp {
	Text::Text(ToolBox &toolBox) : Tool("Text"), _toolBox(toolBox)
	{}

	void Text::onClick(Vector2<int> pos, MouseClick click, Image &image)
	{
		image.getSelectedLayer().text.content = this->_text;
		image.getSelectedLayer().text.fontSize = this->_fontSize;
		image.getSelectedLayer().text.font.loadFromFile(this->_fontPath);
	}

	void Text::onUnselect() {
		this->_edition = false;
	}

	tgui::ScrollablePanel::Ptr Text::getParametersPanel()
	{
		auto panel = tgui::ScrollablePanel::create();

		panel->loadWidgetsFromFile("widgets/tools_cfg/text_cfg.gui");

		auto fontSize = panel->get<tgui::Slider>("FontSize");
		auto fontSizePreview = panel->get<tgui::TextBox>("FontSizePreview");
		auto input = panel->get<tgui::TextBox>("Input");

		/*
		 * Maybe a combobox to select the font ? @todo
		 */
		this->_fontPath = "DejaVuSansMono.ttf";


		fontSizePreview->setText(std::to_string(this->_fontSize));
		fontSize->setValue(this->_fontSize);

		fontSize->connect("ValueChanged", [fontSizePreview, this, fontSize]{
			this->_fontSize = fontSize->getValue();
			fontSizePreview->setText(std::to_string(this->_fontSize));
		});

		this->_text = std::string(input->getText());
		input->connect("Focused", [input, this] {
			this->_edition = true;
			this->_text = std::string(input->getText());
		});
		input->connect("Unfocused", [this] {
			this->_edition = false;
		});

		input->connect("TextChanged", [input, this] {
			this->_edition = true;
			this->_text = std::string(input->getText());
		});

		return panel;
	}
}

