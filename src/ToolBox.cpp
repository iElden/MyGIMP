//
// Created by Gegel85 on 06/04/2020.
//

#include "ToolBox.hpp"
#include "Tools/ToolFactory.hpp"
#include "Exceptions.hpp"

namespace Mimp
{
	ToolBox::ToolBox() :
		_tools(ToolFactory::buildAll(*this))
	{
		this->_generateGuiWindow();
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
		return this->_window;
	}

	void ToolBox::_generateGuiWindow()
	{
		this->_window = tgui::ChildWindow::create();
		this->_window->loadWidgetsFromFile("widgets/tool_box.gui");

		for (auto &name : this->_window->getWidgetNames()) {
			if (name.substring(0, sizeof("Tool")) == "Tool") {
				try {
					auto index = std::stol(static_cast<std::string>(name.substring(sizeof("Tool"))));

					if (index >= this->_tools.size())
						throw CorruptedGuiFileException("Tool index out of range");
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
