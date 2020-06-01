#include <TGUI/TGUI.hpp>
#include <filesystem>
#include "Text.hpp"
#include "../Exceptions.hpp"
#include "../Utils.hpp"

namespace Mimp {
	Text::Text(ToolBox &toolBox) : Tool("Text"), _toolBox(toolBox)
	{
		this->setKeyCombination({Keys::KEY_T, false, false, false});
		try {
			this->getFonts();
		} catch (NoFontException &e) {
			std::cerr << e.what() << std::endl;
		}
	}

	void Text::getFonts()
	{
		this->_fonts.clear();
		try {
			for (auto &file : std::filesystem::directory_iterator("fonts")) {
				this->_fonts[file.path().stem().string()] = file.path().string();
			}
			if (this->_fonts.empty()) throw std::exception();
		} catch (...) {
			this->_fonts[""] = "";
			throw NoFontException();
		}
	}

	void Text::onClick(Vector2<int> pos, MouseClick, Image &image)
	{
		if (!this->_text.empty()) {
			int xpos = 0;
			int ypos = 0;

			this->_font.loadFromFile(this->_fontPath);

			auto &layer = image.getLayers().addLayer(image.getSelectedLayer().getSize());

			for (auto &c : this->_text) {
				auto glyph = this->_font.getGlyph(c, this->_fontSize, false);
				auto texture = this->_font.getTexture(this->_fontSize);
				int spacing = glyph.bounds.top;
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
								layer.buffer->setPixel({pos.x + x + xpos, pos.y + y + ypos + spacing}, this->_color);
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
		auto fonts = panel->get<tgui::ComboBox>("Fonts");
		auto color = panel->get<tgui::Button>("Color");

		auto reload = tgui::Button::create("Reload fonts");
		reload->setPosition("Fonts.x + Fonts.w + 10", "Fonts.y");
		panel->add(reload, "Reload");

		for (auto &f : this->_fonts) {
			fonts->addItem(f.first, f.second);
		}
		this->_selected = this->_selected.empty() ? this->_fonts.begin()->first : this->_selected;
		fonts->setSelectedItem(this->_selected);

		fontSizePreview->setText(std::to_string(this->_fontSize));
		fontSize->setValue(this->_fontSize);

		this->_fontSize = fontSize->getValue();
		this->_text = this->_text.empty() ? input->getText().toWideString() : this->_text;
		input->setText(this->_text);
		this->_fontPath = fonts->getSelectedItemId();

		fontSize->connect("ValueChanged", [fontSizePreview, this, fontSize]{
			this->_fontSize = fontSize->getValue();
			fontSizePreview->setText(std::to_string(this->_fontSize));
		});
		input->connect({"Focused", "TextChanged"}, [input, this] {
			this->_edition = true;
			this->_text = input->getText().toWideString();
		});
		input->connect("Unfocused", [this] {
			this->_edition = false;
		});
		fonts->connect("ItemSelected", [fonts, this] {
			this->_fontPath = fonts->getSelectedItemId();
			this->_selected = fonts->getSelectedItem();
		});
		reload->connect("Pressed", [fonts, this] {
			try {
				this->getFonts();
				fonts->removeAllItems();
				for (auto &f : this->_fonts) {
					fonts->addItem(f.first, f.second);
				}
				fonts->setSelectedItem(this->_fonts.begin()->first);
			} catch (NoFontException &e) {
				std::cerr << e.what() << std::endl;
				fonts->removeAllItems();
				this->_fontPath = "";
			}
		});

		color->connect("Pressed", [color, this] {
			Utils::makeColorPickWindow(this->_toolBox.getParent(), [this, color](Color newColor) {
				this->_color = newColor;

				tgui::Color buffer = {newColor.r, newColor.g, newColor.b, 255};
				color->getRenderer()->setBackgroundColor(buffer);
				color->getRenderer()->setBackgroundColorHover(buffer);
				color->getRenderer()->setBackgroundColorDown(buffer);
			}, this->_color);
		});
		tgui::Color buffer = {this->_color.r, this->_color.g, this->_color.b, 255};
		color->getRenderer()->setBackgroundColor(buffer);
		color->getRenderer()->setBackgroundColorHover(buffer);
		color->getRenderer()->setBackgroundColorDown(buffer);

		return panel;
	}
}
