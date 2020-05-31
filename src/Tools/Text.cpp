#include "Text.hpp"
#include <TGUI/TGUI.hpp>

#include <iostream>

namespace Mimp {
	Text::Text(ToolBox &toolBox) : Tool("Text"), _toolBox(toolBox)
	{}

	void Text::onClick(Vector2<int> pos, MouseClick click, Image &image)
	{
		int position = 0;

		if (!this->_text.empty()) {
			this->_font.loadFromFile(this->_fontPath);
			for (auto &c : this->_text) {

				auto glyph = this->_font.getGlyph(c, this->_fontSize, false);
				auto texture = this->_font.getTexture(this->_fontSize);
				sf::Sprite sprite;

				sprite.setTexture(texture, false);
				sprite.setTextureRect(glyph.textureRect);
				sprite.setPosition(0, 0);
				sprite.setScale(1, 1);

				auto buffer = sprite.getTexture()->copyToImage();



				for (int y = 0; y < glyph.textureRect.height; y += 1) {
				for (int x = 0; x < glyph.textureRect.width; x += 1) {

						if (buffer.getPixel(x + glyph.textureRect.left, y + glyph.textureRect.top).a >= 100) {
							image.getSelectedLayer().buffer.setPixel({pos.x + x + position, pos.y + y}, Color::Red);
						}
					}
				}

				position += glyph.advance;

			}
		}
		//! @todo
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

