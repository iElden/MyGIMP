//
// Created by Gegel85 on 06/04/2020.
//

#include <TGUI/TGUI.hpp>
#include <iostream>
#include "Editor.hpp"
#include "Utils.hpp"

namespace Mimp
{
	Editor::Editor(const std::vector<std::string> &images) :
		_mainWindow({640, 480}, "Mimp"),
		_gui(this->_mainWindow),
		_toolBox(this->_gui)
	{
		this->_mainWindow.setFramerateLimit(240);
		this->_gui.loadWidgetsFromFile("widgets/top_menu.gui");
		this->_setupButtonCallbacks();
		this->_gui.add(this->_toolBox.getWindow(), "ToolBox");

		auto menu = this->_gui.get<tgui::MenuBar>("main_bar");

		for (auto &image : images) {
			try {
				auto widget = CanvasWidget::create(this->_toolBox, image);
				auto window = _makeImagePanel(widget);

				window->setTitle(image);
				this->_gui.add(window, "Image" + image);
				this->_selectedImage = window;
				menu->setMenuItemEnabled({"File", "Save"}, true);
				menu->setMenuItemEnabled({"File", "Save as"}, true);
				menu->setMenuItemEnabled({"File", "Export"}, true);
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

	void Editor::setSelectedImage(tgui::ChildWindow::Ptr canvas)
	{
		this->_selectedImage = canvas;
	}

	tgui::ChildWindow::Ptr Editor::getSelectedImage() const
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
		auto menu = this->_gui.get<tgui::MenuBar>("main_bar");
		auto window = tgui::ChildWindow::create("Unnamed");

		window->setSize({
			canvas->getLayers().getSize().x,
			canvas->getLayers().getSize().y
		});
		window->connect("Closed", [this, menu, window, canvas] {
			menu->setMenuItemEnabled({"File", "Save"}, false);
			menu->setMenuItemEnabled({"File", "Save as"}, false);
			menu->setMenuItemEnabled({"File", "Export"}, false);
			this->_selectedImage = nullptr;
			canvas->disableRendering();
			this->_gui.remove(window);
		});
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
			this->_gui.add(window, "ImageUntitled " + std::to_string(this->_lastUntitled));
			this->_selectedImage = window;
			menu->setMenuItemEnabled({"File", "Save"}, true);
			menu->setMenuItemEnabled({"File", "Save as"}, true);
			menu->setMenuItemEnabled({"File", "Export"}, true);
		});
		menu->connectMenuItem({"File", "Open"}, [this, menu]{
			std::string path = Utils::openFileDialog("Load MIMP file", ".", {{".+[.]mimp", "MIMP image file"}});

			if (path.empty())
				return;
			try {

				auto widget = CanvasWidget::create(this->_toolBox, path);
				auto window = _makeImagePanel(widget);

				menu->setMenuItemEnabled({"File", "Save"}, true);
				menu->setMenuItemEnabled({"File", "Save as"}, true);
				menu->setMenuItemEnabled({"File", "Export"}, true);

				window->setTitle(path);
				this->_gui.add(window, "Image" + path);
				this->_selectedImage = window;
			} catch (std::exception &e) {
				auto window = tgui::ChildWindow::create("Loading error");
				auto label = tgui::Label::create(
					"Cannot load file " + path + "\n" +
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
			std::string path = this->_gui.getWidgetName(this->_selectedImage).substr(strlen("Image"));

			if (path.substr(path.find_last_of('.')) != ".mimp")
				path = Utils::saveFileDialog("Save MIMP file", path, {{".+[.]mimp", "MIMP image file"}});

			if (path.empty())
				return;

			this->_selectedImage->setTitle(path);
			this->_gui.remove(this->_selectedImage);
			this->_gui.add(this->_selectedImage, "Image" + path);
			this->_selectedImage->get<CanvasWidget>("Canvas")->getLayers().save(path);
		});
		menu->connectMenuItem({"File", "Save as"}, [this, menu] {
			std::string name = this->_gui.getWidgetName(this->_selectedImage).substr(strlen("Image"));
			std::string path = Utils::saveFileDialog("Save MIMP file", name, {{".+[.]mimp", "MIMP image file"}});

			if (path.empty())
				return;
			this->_selectedImage->get<CanvasWidget>("Canvas")->getLayers().save(path);
		});
		menu->connectMenuItem({"File", "Export"}, [this, menu] {
			std::string name = this->_gui.getWidgetName(this->_selectedImage).substr(strlen("Image"));
			std::string path = Utils::saveFileDialog("Export image", name, {{".+[.]png", "Portable Network Graphics (PNG)"}});

			if (path.empty())
				return;
			this->_selectedImage->get<CanvasWidget>("Canvas")->exportImage(path);
		});
		menu->connectMenuItem({"File", "Import"}, [this, menu] {
			std::string path = Utils::openFileDialog("Load MIMP file", ".", {
				{".+[.]png", "Portable Network Graphics (PNG)"},
				{".+[.]jpg", "Joint Photographic Experts Group (JPEG)"},
				{".+[.]bmp", "Windows Bitmap (BMP)"},
				{".+[.]gif", "Graphics Interchange Format (GIF)"},
			});

			try {
				if (path.empty())
					return;

				auto widget = CanvasWidget::create(this->_toolBox, Vector2<unsigned>{0, 0});

				widget->importImage(path);

				auto window = _makeImagePanel(widget);

				menu->setMenuItemEnabled({"File", "Save"}, true);
				menu->setMenuItemEnabled({"File", "Save as"}, true);
				menu->setMenuItemEnabled({"File", "Export"}, true);

				window->setTitle(path);
				this->_gui.add(window, "Image" + path);
				this->_selectedImage = window;
			} catch (std::exception &e) {
				auto window = tgui::ChildWindow::create("Loading error");
				auto label = tgui::Label::create(
					"Cannot load file " + path + "\n" +
					Utils::getLastExceptionName() + ":\n" + e.what()
				);

				window->setPosition(16, 16);
				window->add(label);
				window->getRenderer()->setBackgroundColor(tgui::Color("white"));
				window->setSize(label->getSize());
				this->_gui.add(window);
			}
		});
	}
}