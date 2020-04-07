//
// Created by Gegel85 on 06/04/2020.
//

#ifndef MYGIMP_EDITOR_HPP
#define MYGIMP_EDITOR_HPP


#include <SFML/Graphics.hpp>
#include <TGUI/Gui.hpp>
#include "ToolBox.hpp"
#include "CanvasWidget.hpp"

namespace Mimp
{
	class Editor {
	private:
		ToolBox _toolBox;
		sf::RenderWindow _mainWindow;
		tgui::Gui _gui;
		std::shared_ptr<CanvasWidget> _selectedImage;

	public:
		Editor(const std::vector<std::string> &images = {});

		void setSelectedImage(const std::shared_ptr<CanvasWidget> &_canvas);
		std::shared_ptr<CanvasWidget> getSelectedImage() const;
		int run();
	};
}


#endif //MYGIMP_EDITOR_HPP
