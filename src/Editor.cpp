//
// Created by Gegel85 on 06/04/2020.
//

#include "Editor.hpp"
#include "Utils.hpp"

namespace Mimp
{
	Editor::Editor(const std::vector<std::string> &images) :
		_toolBox(),
		_mainWindow({640, 480}, "Mimp"),
		_gui(this->_mainWindow)
	{
		this->_gui.add(this->_toolBox.getWindow(), "ToolBox");
	}

	void Editor::setSelectedImage(const std::shared_ptr<CanvasWidget> &canvas)
	{
		this->_selectedImage = canvas;
	}

	std::shared_ptr<CanvasWidget> Editor::getSelectedImage() const
	{
		return this->_selectedImage;
	}

	int Editor::run()
	{
#ifndef _DEBUG
		try {
#endif
			while (this->_mainWindow.isOpen()) {
				sf::Event event;

				while (this->_mainWindow.pollEvent(event)) {
					if (event.type == sf::Event::Closed)
						this->_mainWindow.close();
					if (event.type == sf::Event::Resized) {
						this->_mainWindow.setView(sf::View{sf::FloatRect(0, 0, event.size.width, event.size.height)});
						this->_gui.setView(sf::View{sf::FloatRect(0, 0, event.size.width, event.size.height)});
					}
					this->_gui.handleEvent(event);
				}
				this->_mainWindow.clear();
				this->_gui.draw();
				this->_mainWindow.display();
			}
#ifndef _DEBUG
		} catch (std::exception &e) {
			Utils::dispMsg(
				"Fatal Error",
				"An unrecoverable error occurred\n\n" +
				Utils::getLastExceptionName() + ":\n" + e.what() + "\n\n"
				"Click OK to close the application",
				MB_ICONERROR
			);
		}
#endif
		return EXIT_SUCCESS;
	}
}