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
	ToolBox::ToolBox() :
		_tools(ToolFactory::buildAll(*this))
	{
		this->_generateGuiWindow();
		this->_tools[0]->onSelect();
	}

	Tool &ToolBox::getSelectedTool() noexcept
	{
		return *this->_tools[this->_selectedTool];
	}

	const Tool &ToolBox::getSelectedTool() const noexcept
	{
		return *this->_tools[this->_selectedTool];
	}

	tgui::ChildWindow::Ptr ToolBox::getWindow() const
	{
		this->_window->setPosition("&.w - w", 20);
		return this->_window;
	}

	void ToolBox::_generateGuiWindow()
	{
		this->_window = tgui::ChildWindow::create();
		this->_window->loadWidgetsFromFile("widgets/tool_box.gui");

		auto panel = this->_window->get<tgui::ScrollablePanel>("Panel");

		this->_window->setSize(panel->getSize());
		this->_window->setTitle("Tools");
		this->_window->connect("Closed", [this]{
			this->_generateGuiWindow();
		});

		for (auto &widget : panel->getWidgets()) {
			auto name = panel->getWidgetName(widget);

			if (name.substr(0, strlen("Tool")) == "Tool") {
				try {
					size_t index = std::stol(static_cast<std::string>(name.substr(strlen("Tool"))));

					if (index >= this->_tools.size())
						throw CorruptedGuiFileException("Tool index out of range");

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
