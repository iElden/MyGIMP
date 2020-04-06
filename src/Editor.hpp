//
// Created by Gegel85 on 06/04/2020.
//

#ifndef MYGIMP_EDITOR_HPP
#define MYGIMP_EDITOR_HPP


#include <SFML/Graphics.hpp>
#include <TGUI/Gui.hpp>
#include "ToolBox.hpp"

namespace Mimp
{
	class Editor {
	private:
		ToolBox _toolBox;
		sf::RenderWindow _mainWindow;
		tgui::Gui _gui;

	public:
		Editor(const std::vector<std::string> &images = {});

		int run();
	};
}


#endif //MYGIMP_EDITOR_HPP
