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
	class ToolBox {
	private:
		std::vector<std::shared_ptr<Tool>> _tools;
		unsigned int _selectedTool = 0;
		tgui::ChildWindow::Ptr _window;
		std::pair<Color, Color> _selectedColor = {
			Color::Black,
			Color::White
		};

		void _generateGuiWindow();
	public:
		ToolBox();
		std::shared_ptr<Tool> getSelectedTool() const;
		tgui::ChildWindow::Ptr getWindow() const;
		Color getSelectedColor(MouseClick click);
	};
}


#endif //MYGIMP_TOOLBOX_HPP
