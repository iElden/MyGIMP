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
		unsigned _lastUntitled = 0;
		ToolBox _toolBox;
		sf::RenderWindow _mainWindow;
		tgui::Gui _gui;
		tgui::ChildWindow::Ptr _selectedImage;

		void _setupButtonCallbacks();

		tgui::ChildWindow::Ptr _makeImagePanel(CanvasWidget::Ptr canvas);
	public:
		Editor(const Editor &) = delete;
		Editor(const std::vector<std::string> &images = {});

		void setSelectedImage(tgui::ChildWindow::Ptr _canvas);
		tgui::ChildWindow::Ptr getSelectedImage() const;
		int run();
	};
}


#endif //MYGIMP_EDITOR_HPP
