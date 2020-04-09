//
// Created by Gegel85 on 06/04/2020.
//

#include <TGUI/TGUI.hpp>
#include "Editor.hpp"
#include "Utils.hpp"

namespace Mimp
{
	Editor::Editor(const std::vector<std::string> &images) :
		_toolBox(),
		_mainWindow({640, 480}, "Mimp"),
		_gui(this->_mainWindow)
	{
		this->_mainWindow.setFramerateLimit(60);
		this->_gui.loadWidgetsFromFile("widgets/top_menu.gui");
		this->_setupButtonCallbacks();
		this->_gui.add(this->_toolBox.getWindow(), "ToolBox");
		for (auto &image : images) {
			try {
				auto widget = CanvasWidget::create(this->_toolBox, image);

				this->_gui.add(_makeImagePanel(widget), "Image");
				this->_selectedImage = widget;
			} catch (std::exception &e) {
				Utils::dispMsg(
					"Error",
					"Cannot load " + image + "\n\n" +
					Utils::getLastExceptionName() + ":\n" + e.what(),
					MB_ICONERROR
				);
			}
		}
	}

	void Editor::setSelectedImage(const std::shared_ptr<CanvasWidget> &canvas)
	{
		this->_selectedImage = canvas;
	}

	CanvasWidget::Ptr Editor::getSelectedImage() const
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

	tgui::ChildWindow::Ptr Editor::_makeImagePanel(CanvasWidget::Ptr canvas)
	{
		auto window = tgui::ChildWindow::create("Unnamed");

		window->setPosition(0, 30);
		window->add(canvas, "Canvas");
		return window;
	}

	void Editor::_setupButtonCallbacks()
	{
		auto menu = this->_gui.get<tgui::MenuBar>("main_bar");

		menu->connect("MouseEntered", [](tgui::Widget::Ptr bar, const std::string&){
			bar->moveToFront();
		});
		menu->connectMenuItem({"File", "New"}, [this, menu]{
			auto widget = CanvasWidget::create(this->_toolBox, Vector2<unsigned>{640, 480});
			auto window = _makeImagePanel(widget);

			window->setTitle("Untitled " + std::to_string(++this->_lastUntitled));
			window->setSize({
				widget->getLayers().getSize().x,
				widget->getLayers().getSize().y
			});
			window->connect("Closed", [menu] {
				menu->setMenuItemEnabled({"File", "Save"}, false);
				menu->setMenuItemEnabled({"File", "Save as"}, false);
			});
			this->_gui.add(_makeImagePanel(widget), "ImageUntitled" + std::to_string(this->_lastUntitled));
			this->_selectedImage = widget;
			menu->setMenuItemEnabled({"File", "Save"}, true);
			menu->setMenuItemEnabled({"File", "Save as"}, true);
		});
		menu->connectMenuItem({"File", "Open"}, [this, menu]{
			try {
				auto widget = CanvasWidget::create(this->_toolBox, "test.mimp");
				auto window = _makeImagePanel(widget);

				menu->setMenuItemEnabled({"File", "Save"}, true);
				menu->setMenuItemEnabled({"File", "Save as"}, true);

				window->setSize({
					widget->getLayers().getSize().x,
					widget->getLayers().getSize().y
				});
				window->setTitle("test.mimp");
				window->connect("Closed", [menu] {
					menu->setMenuItemEnabled({"File", "Save"}, false);
					menu->setMenuItemEnabled({"File", "Save as"}, false);
				});
				this->_gui.add(window, "Image" "test.mimp");
				this->_selectedImage = widget;
			} catch (std::exception &e) {
				auto window = tgui::ChildWindow::create("Loading error");
				auto label = tgui::Label::create(
					"Cannot load file " "test.mimp""\n" +
					Utils::getLastExceptionName() + ":\n" + e.what()
				);

				window->setPosition(16, 16);
				window->add(label);
				window->getRenderer()->setBackgroundColor(tgui::Color("white"));
				window->setSize(label->getSize());
				this->_gui.add(window);
			}
		});
		menu->connectMenuItem({"File", "Save"}, [this, menu] {
			this->_selectedImage->getLayers().save("test.mimp");
		});
	}
}