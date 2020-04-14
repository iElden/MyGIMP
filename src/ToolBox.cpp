//
// Created by Gegel85 on 06/04/2020.
//

#include <iostream>
#include <TGUI/TGUI.hpp>
#include "ToolBox.hpp"
#include "Tools/ToolFactory.hpp"
#include "Exceptions.hpp"

namespace Mimp
{
	ToolBox::ToolBox(tgui::Gui &gui) :
		_tools(ToolFactory::buildAll(*this))
	{
		this->_generateGuiWindow(gui);
		this->_tools[0]->onSelect();
	}

	std::shared_ptr<Tool> ToolBox::getSelectedTool() const
	{
		return this->_tools[this->_selectedTool];
	}

	tgui::ChildWindow::Ptr ToolBox::getWindow() const
	{
		this->_window->setPosition("&.w - w", 20);
		return this->_window;
	}

	void ToolBox::_generateGuiWindow(tgui::Gui &gui)
	{
		auto callback = [&gui](tgui::Button::Ptr button, Color *color){
			auto panel = tgui::Panel::create({"100%", "100%"});

			panel->getRenderer()->setBackgroundColor({0, 0, 0, 175});
			gui.add(panel);

			auto window = tgui::ChildWindow::create();
			window->setSize(271, 182);
			window->setPosition("(&.w - w) / 2", "(&.h - h) / 2");
			gui.add(window);

			window->setFocused(true);

			const bool tabUsageEnabled = gui.isTabKeyUsageEnabled();
			auto closeWindow = [&gui, window, panel, tabUsageEnabled]{
				gui.remove(window);
				gui.remove(panel);
				gui.setTabKeyUsageEnabled(tabUsageEnabled);
			};

			panel->connect("Clicked", closeWindow);
			window->connect({"Closed", "EscapeKeyPressed"}, closeWindow);
			window->loadWidgetsFromFile("widgets/color.gui");

			auto red = window->get<tgui::Slider>("Red");
			auto green = window->get<tgui::Slider>("Green");
			auto blue = window->get<tgui::Slider>("Blue");
			auto preview = window->get<tgui::TextBox>("Preview");
			auto sliderCallback = [red, green, blue, preview]{
				tgui::Color bufferColor{
					static_cast<unsigned char>(red->getValue()),
					static_cast<unsigned char>(green->getValue()),
					static_cast<unsigned char>(blue->getValue())
				};

				preview->getRenderer()->setBackgroundColor(bufferColor);
			};

			red->setValue(color->r);
			red->connect("ValueChanged", sliderCallback);
			green->setValue(color->g);
			green->connect("ValueChanged", sliderCallback);
			blue->setValue(color->b);
			blue->connect("ValueChanged", sliderCallback);
			preview->getRenderer()->setBackgroundColor({color->r, color->g, color->b, 255});
			window->get<tgui::Button>("Cancel")->connect("Clicked", [window]{
				window->close();
			});
			window->get<tgui::Button>("OK")->connect("Clicked", [red, green, blue, window, button, color]{
				Color bufferColor{
					static_cast<unsigned char>(red->getValue()),
					static_cast<unsigned char>(green->getValue()),
					static_cast<unsigned char>(blue->getValue())
				};

				*color = bufferColor;
				button->getRenderer()->setBackgroundColor({bufferColor.r, bufferColor.g, bufferColor.b, 255});
				button->getRenderer()->setBackgroundColorHover({bufferColor.r, bufferColor.g, bufferColor.b, 255});
				button->getRenderer()->setBackgroundColorDown({bufferColor.r, bufferColor.g, bufferColor.b, 255});
				window->close();
			});
		};

		this->_window = tgui::ChildWindow::create();
		this->_window->loadWidgetsFromFile("widgets/tool_box.gui");

		auto panel = this->_window->get<tgui::ScrollablePanel>("Panel");

		this->_colorButtons.first = this->_window->get<tgui::Button>("Color1");
		this->_colorButtons.second = this->_window->get<tgui::Button>("Color2");

		this->_colorButtons.first->getRenderer()->setBackgroundColor({this->_selectedColor.first.r, this->_selectedColor.first.g, this->_selectedColor.first.b, 255});
		this->_colorButtons.first->getRenderer()->setBackgroundColorHover({this->_selectedColor.first.r, this->_selectedColor.first.g, this->_selectedColor.first.b, 255});
		this->_colorButtons.first->getRenderer()->setBackgroundColorDown({this->_selectedColor.first.r, this->_selectedColor.first.g, this->_selectedColor.first.b, 255});
		this->_colorButtons.first->connect("Clicked", callback, this->_colorButtons.first, &this->_selectedColor.first);

		this->_colorButtons.second->getRenderer()->setBackgroundColor({this->_selectedColor.second.r, this->_selectedColor.second.g, this->_selectedColor.second.b, 255});
		this->_colorButtons.second->getRenderer()->setBackgroundColorHover({this->_selectedColor.second.r, this->_selectedColor.second.g, this->_selectedColor.second.b, 255});
		this->_colorButtons.second->getRenderer()->setBackgroundColorDown({this->_selectedColor.second.r, this->_selectedColor.second.g, this->_selectedColor.second.b, 255});
		this->_colorButtons.second->connect("Clicked", callback, this->_colorButtons.second, &this->_selectedColor.second);

		this->_window->setSize(panel->getSize());
		this->_window->setTitle("Tools");
		this->_window->connect("Closed", [this, &gui]{
			this->_generateGuiWindow(gui);
		});

		for (auto &widget : panel->getWidgets()) {
			auto name = panel->getWidgetName(widget);

			if (name.substr(0, strlen("Tool")) == "Tool") {
				try {
					size_t index = std::stol(static_cast<std::string>(name.substr(strlen("Tool"))));

					if (index >= this->_tools.size())
						throw CorruptedGuiFileException("Tool index out of range");

					widget->setToolTip(tgui::Label::create(this->_tools[index]->getName()));
					widget->connect("Pressed", [this, index]{
						this->getSelectedTool()->onUnselect();
						this->_selectedTool = index;
						this->getSelectedTool()->onSelect();
					});
				} catch (std::out_of_range &e) {
					throw CorruptedGuiFileException("Tool index out of range");
				} catch (std::invalid_argument &e) {
					throw CorruptedGuiFileException("Tool index is not a valid number");
				}
			}
		}
	}

	Color ToolBox::getSelectedColor(MouseClick click)
	{
		if (click == MIMP_LEFT_CLICK)
			return this->_selectedColor.first;
		return this->_selectedColor.second;
	}
}
