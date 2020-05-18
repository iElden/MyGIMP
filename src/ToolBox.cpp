//
// Created by Gegel85 on 06/04/2020.
//

#include <iostream>
#include <TGUI/TGUI.hpp>
#include "ToolBox.hpp"
#include "Tools/ToolFactory.hpp"
#include "Exceptions.hpp"
#include "Utils.hpp"

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
		auto callback = [this, &gui](tgui::Button::Ptr button, Color *color){
			Utils::makeColorPickWindow(gui, [this, button, color](Color col){
				this->_changeSelectedColor(button, color, col);
			}, *color);
		};

		this->_window = tgui::ChildWindow::create();
		this->_window->loadWidgetsFromFile("widgets/tool_box.gui");

		auto panel = this->_window->get<tgui::ScrollablePanel>("Panel");

		panel->setSize(panel->getSize().x * 2, panel->getSize().y);
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

		this->_window->setSize(panel->getSize().x, panel->getSize().y + 300);
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
					widget->connect("Pressed", [this, index, panel]{
						this->getSelectedTool()->onUnselect();
						this->_selectedTool = index;
						this->_addSelectedToolConfigPanel(panel);
						this->getSelectedTool()->onSelect();
					});
				} catch (std::out_of_range &e) {
					throw CorruptedGuiFileException("Tool index out of range");
				} catch (std::invalid_argument &e) {
					throw CorruptedGuiFileException("Tool index is not a valid number");
				}
			}
		}
		this->_addSelectedToolConfigPanel(panel);
	}

	Color ToolBox::getSelectedColor(MouseClick click)
	{
		if (click == MIMP_LEFT_CLICK)
			return this->_selectedColor.first;
		return this->_selectedColor.second;
	}

	void ToolBox::_changeSelectedColor(tgui::Button::Ptr button, Color *color, Color newColor)
	{
		tgui::Color buffer = {newColor.r, newColor.g, newColor.b, 255};

		*color = newColor;
		button->getRenderer()->setBackgroundColor(buffer);
		button->getRenderer()->setBackgroundColorHover(buffer);
		button->getRenderer()->setBackgroundColorDown(buffer);
	}

	void ToolBox::setSelectedColor(MouseClick click, Color newColor)
	{
		if (click == MIMP_LEFT_CLICK)
			this->_changeSelectedColor(this->_colorButtons.first, &this->_selectedColor.first, newColor);
		else if (click == MIMP_RIGHT_CLICK)
			this->_changeSelectedColor(this->_colorButtons.second, &this->_selectedColor.second, newColor);
	}

	void ToolBox::_addSelectedToolConfigPanel(tgui::Panel::Ptr pan)
	{
		auto panel = this->getSelectedTool()->getParametersPanel();

		this->_window->remove(this->_window->get<tgui::Widget>("cfg"));
		panel->setPosition(10, pan->getSize().y + 10);
		panel->setSize(pan->getSize().x - 20, 280);
		this->_window->add(panel, "cfg");
	}
}
