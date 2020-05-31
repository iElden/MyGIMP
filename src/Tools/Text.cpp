#include "Text.hpp"
#include <TGUI/TGUI.hpp>

#include <iostream>

namespace Mimp {
	Text::Text(ToolBox &toolBox) : Tool("Text"), _toolBox(toolBox)
	{}

	void Text::onClick(Vector2<int> pos, MouseClick click, Image &image)
	{


		if (!this->_text.empty()) {
			int xpos = 0;
			int ypos = 0;

			this->_font.loadFromFile(this->_fontPath);

			//! @todo
			//auto layer = image.getLayers().addLayer(image.getSelectedLayer().getSize());
			auto &layer = image.getSelectedLayer();

			for (auto &c : this->_text) {
				auto glyph = this->_font.getGlyph(c, this->_fontSize, false);
				auto texture = this->_font.getTexture(this->_fontSize);
				sf::Sprite sprite;

				sprite.setTexture(texture, false);
				sprite.setTextureRect(glyph.textureRect);
				sprite.setPosition(0, 0);
				sprite.setScale(1, 1);

				auto buffer = sprite.getTexture()->copyToImage();

				if (c != '\n') {
					for (int y = 0; y < glyph.textureRect.height; y += 1) {
						for (int x = 0; x < glyph.textureRect.width; x += 1) {
							if (buffer.getPixel(x + glyph.textureRect.left, y + glyph.textureRect.top).a >= 100) {
								layer.buffer.setPixel({pos.x + x + xpos, pos.y + y + ypos}, Color::Red);
							}
						}
					}
					xpos += glyph.advance;
				} else {
					xpos = 0;
					ypos += this->_fontSize;
				}
			}
		}
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

		this->_text = input->getText().toWideString();
		input->connect("Focused", [input, this] {
			this->_edition = true;
			this->_text = input->getText().toWideString();
		});
		input->connect("Unfocused", [this] {
			this->_edition = false;
		});

		input->connect("TextChanged", [input, this] {
			this->_edition = true;
			this->_text = input->getText().toWideString();
		});

		return panel;
	}
}

