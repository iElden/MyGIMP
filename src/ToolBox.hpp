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
		std::vector<std::unique_ptr<Tool>> _tools;
		unsigned int _selectedTool = 0;

	public:
		ToolBox();
		Tool &getSelectedTool() noexcept;
		tgui::ChildWindow::Ptr makeWindow();
	};
}


#endif //MYGIMP_TOOLBOX_HPP
