#include <TGUI/TGUI.hpp>
#include <filesystem>
#include <algorithm>
#include <iostream>
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

	void Text::getFontsFromPath(std::string path)
	{
		for (auto &file : std::filesystem::directory_iterator(path)) {
			if (file.is_directory()) {
				this->getFontsFromPath(file.path().string());
			} else {
				if (std::find(this->_extensions.begin(), this->_extensions.end(), file.path().extension().string()) != this->_extensions.end())
					this->_fonts[file.path().stem().string()] = file.path().string();
			}
		}
		if (this->_fonts.empty()) throw std::exception();
	}

	void Text::getCustomFonts()
	{
		this->_fonts.clear();
		this->getFontsFromPath("fonts");
	}

	void Text::getSystemFonts()
	{
		this->_fonts.clear();
#ifdef _WIN32
		this->getFontsFromPath("C:/Windows/Fonts");
#else
		try {
			this->getFontsFromPath("/usr/local/share/fonts");
		} catch (...) {
			this->getFontsFromPath("/usr/share/fonts");
		}
#endif
	}

	void Text::getFonts()
	{
		this->_fonts.clear();
		try {
			getCustomFonts();
			this->_system = true;
		} catch (...) {
			try {
				getSystemFonts();
				this->_system = false;
			} catch (...) {
				this->_fonts[""] = "";
				throw NoFontException();
			}
		}
	}

	void Text::onClick(Mimp::Vector2<float> pos, Mimp::MouseClick click, Mimp::Image &image)
	{
		if (!this->_text.empty()) {
			int xpos = 0;
			int ypos = 0;

			this->_font.loadFromFile(this->_fontPath);

			image.takeFrameBufferSnapshot();
			auto &layer = image.getSelectedLayer();

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
								layer.buffer->setPixel(Vector2<float>{pos.x + x + xpos, pos.y + y + ypos + spacing}.to<int>(), !this->_boxColours ? this->_toolBox.getSelectedColor(click) : this->_color);
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

	void Text::onUnselect()
	{
		this->_edition = false;
	}

	tgui::ScrollablePanel::Ptr Text::getParametersPanel()
	{
		bool isbusy = false;
		auto panel = tgui::ScrollablePanel::create();

		panel->loadWidgetsFromFile("widgets/tools_cfg/text_cfg.gui");

		auto fontSize = panel->get<tgui::Slider>("FontSize");
		auto fontSizePreview = panel->get<tgui::TextBox>("FontSizePreview");
		auto input = panel->get<tgui::TextBox>("Input");
		auto fonts = panel->get<tgui::ListBox>("Fonts");
		auto fontDisplay = panel->get<tgui::TextBox>("FontDisplay");
		auto color = panel->get<tgui::Button>("Color");
		auto useColour = panel->get<tgui::Button>("UseColour");

		auto choose = tgui::Button::create("Custom Fonts");
		choose->setPosition("FontDisplay.x + FontDisplay.w + 10", "FontDisplay.y");
		panel->add(choose, "Choose");

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

		fontSize->connect("ValueChanged", [fontSizePreview, this, fontSize] {
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

		fontDisplay->setText(this->_selected);
		fontDisplay->connect("Unfocused", [fonts, &isbusy] {
			if (!isbusy)
				fonts->setSize(0, 0);
		});
		fontDisplay->connect("Focused", [fontDisplay, fonts, &isbusy] {
			fonts->setFocused(true);
			isbusy = true;
		});

		fonts->connect("Unfocused", [fonts, &isbusy] {
			fonts->setSize(0, 0);
			isbusy = false;
		});
		fonts->connect("Focused", [fonts, &isbusy] {
			fonts->setSize(150, 200);
			isbusy = true;
		});
		fonts->connect("ItemSelected", [fontDisplay, fonts, input, this, &isbusy] {
			this->_fontPath = fonts->getSelectedItemId();
			this->_selected = fonts->getSelectedItem();
			fonts->setSize(0, 0);
			fontDisplay->setText(this->_selected);
			auto lines = fontDisplay->getLinesCount();
			auto ysize = 20;
			auto ypos = 100;
			if (lines == 2) {
				ysize = 40;
				ypos = 120;
			}
			fontDisplay->setSize(150, ysize);
			input->setPosition(60, ypos);
			isbusy = false;
		});

		choose->connect("Pressed", [choose, fonts, this] {
			try {
				this->_system ? (choose->setText("Custom Fonts"), this->getSystemFonts()) : (choose->setText("System Fonts"), this->getCustomFonts());
				fonts->removeAllItems();
				for (auto &f : this->_fonts) {
					fonts->addItem(f.first, f.second);
				}
				fonts->setSelectedItem(this->_fonts.begin()->first);
			} catch (std::exception &e) {
				std::cerr << e.what() << std::endl;
				fonts->removeAllItems();
				this->_fontPath = "";
			}
			this->_system = !this->_system;
		});

		useColour->setText(this->_boxColours ? "Use ToolBox color" : "Use custom color");
		color->setEnabled(this->_boxColours);
		useColour->connect("Pressed", [useColour, color, this] {
			this->_boxColours = !this->_boxColours;
			color->setEnabled(this->_boxColours);
			useColour->setText(this->_boxColours ? "Use ToolBox color" : "Use custom color");
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
