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

		void _generateGuiWindow();
	public:
		ToolBox();
		Tool &getSelectedTool() noexcept;
		const Tool &getSelectedTool() const noexcept;
		tgui::ChildWindow::Ptr getWindow() const;
	};
}


#endif //MYGIMP_TOOLBOX_HPP
