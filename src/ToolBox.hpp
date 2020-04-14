//
// Created by Gegel85 on 06/04/2020.
//

#ifndef MYGIMP_TOOLBOX_HPP
#define MYGIMP_TOOLBOX_HPP


#include <TGUI/Widgets/ChildWindow.hpp>
#include <vector>
#include "Tools/Tool.hpp"

namespace Mimp
{
	//! @brief Class ToolBox
	//! @details Contains all the tools required in Mimp
	class ToolBox {
	private:
		//! @brief Tools as shared pointers
		std::vector<std::shared_ptr<Tool>> _tools;
		//! @brief Tool index that is selected
		unsigned int _selectedTool = 0;
		//! @brief Window of the toolbox
		tgui::ChildWindow::Ptr _window;
		//! @brief Pair of Selected Colors
		std::pair<Color, Color> _selectedColor = {
			Color::Black,
			Color::White
		};

		std::pair<tgui::Button::Ptr, tgui::Button::Ptr> _colorButtons;

		//! @brief Generates the GUI Window
		void _generateGuiWindow(tgui::Gui &gui);
	public:
		//! @brief Constructor of ToolBox Class
		ToolBox(tgui::Gui &gui);
		//! @brief Get the selected Tool as Shared pointer
		//! @return std::shared_ptr<Tool> The selected Tool as Shared Pointer
		std::shared_ptr<Tool> getSelectedTool() const;
		//! @brief Get the window of the toolbox
		//! @return tgui::ChildWindow::Ptr Window of the toolbox
		tgui::ChildWindow::Ptr getWindow() const;
		//! @brief Get the selected color
		//! @param click The mouse click state
		//! @return Color The selected color
		Color getSelectedColor(MouseClick click);
	};
}


#endif //MYGIMP_TOOLBOX_HPP
