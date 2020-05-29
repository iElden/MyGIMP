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
    //! @brief Define the ToolBox.
    class ToolBox {
	private:
		std::vector<std::shared_ptr<Tool>> _tools; //!< Tools as shared pointers
		unsigned int _selectedTool = 0; //!< Index of the selected tool.
		tgui::ChildWindow::Ptr _window; //!< Window of the toolbox
		std::pair<Color, Color> _selectedColor = {
			Color::Black,
			Color::White
		}; //!< Pair of Selected Colors. Default are Black and White.

		std::pair<tgui::Button::Ptr, tgui::Button::Ptr> _colorButtons;

		//! @brief Generates the GUI Window
		//! @param gui The gui
		void _generateGuiWindow(tgui::Gui &gui);

		//! @brief Change the Selected Color
		//! @param button State of the button
		//! @param color Color used
		//! @param newColor Color to use
		void _changeSelectedColor(tgui::Button::Ptr button, Color *color, Color newColor);

		void _addSelectedToolConfigPanel(tgui::Panel::Ptr pan);
	public:
		//! @brief Constructor of ToolBox Class
		//! @param gui The gui to draw the ToolBox.
		ToolBox(tgui::Gui &gui);

		//! @brief Get the selected Tool as shared pointer
		//! @return std::shared_ptr<Tool> The selected Tool as Shared Pointer
		std::shared_ptr<Tool> getSelectedTool() const;

		//! @brief Get the window of the ToolBox
		//! @return tgui::ChildWindow::Ptr Window of the toolbox
		tgui::ChildWindow::Ptr getWindow() const;

		//! @brief Get the selected Color
		//! @param click The mouse click state
		//! @return Color The selected Color
		Color getSelectedColor(MouseClick click);

		//! @brief Set the selected Color
		//! @param click Mouse click state
		//! @param newColor Color to use
		void setSelectedColor(MouseClick click, Color newColor);

		//! @brief Get the tools of the ToolBox.
	    std::map<std::string, std::shared_ptr<Tool>> getTools();

	    void selectTool(Keys::KeyCombination kc);

	    void refreshToolBox();
	};
}


#endif //MYGIMP_TOOLBOX_HPP
