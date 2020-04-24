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
				this->_selectedImageWindow = window;
				menu->setMenuItemEnabled({"File", "Save"}, true);
				menu->setMenuItemEnabled({"File", "Save as"}, true);
				menu->setMenuItemEnabled({"File", "Export"}, true);
				menu->setMenuItemEnabled({"File", "Close"}, true);
				menu->setMenuItemEnabled({"File", "Close All"}, true);
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
		this->_selectedImageWindow = canvas;
	}

	tgui::ChildWindow::Ptr Editor::getSelectedImage() const
	{
		return this->_selectedImageWindow;
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
		auto layersPanel = this->_makeLayersPanel(window, canvas);
		auto canvasPanel = tgui::ScrollablePanel::create({400, 400});

		window->setSize({
			600,
			420
		});
		window->connect("Closed", [this, menu, window, canvas] {
			menu->setMenuItemEnabled({"File", "Save"}, false);
			menu->setMenuItemEnabled({"File", "Save as"}, false);
			menu->setMenuItemEnabled({"File", "Export"}, false);
			menu->setMenuItemEnabled({"File", "Close"}, false);
			menu->setMenuItemEnabled({"File", "Close All"}, false);
			this->_selectedImageWindow = nullptr;
			canvas->disableRendering();
			this->_gui.remove(window);
		});
		window->setPosition(0, 30);

		layersPanel->setPosition(10, 10);
		window->add(layersPanel, "Layers");

		canvasPanel->setPosition(190, 10);
		canvasPanel->add(canvas, "Canvas");
		window->add(canvasPanel, "Canvas");
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
			this->_selectedImageWindow = window;
			menu->setMenuItemEnabled({"File", "Save"}, true);
			menu->setMenuItemEnabled({"File", "Save as"}, true);
			menu->setMenuItemEnabled({"File", "Export"}, true);
			menu->setMenuItemEnabled({"File", "Close"}, true);
			menu->setMenuItemEnabled({"File", "Close All"}, true);
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
				menu->setMenuItemEnabled({"File", "Close"}, true);
				menu->setMenuItemEnabled({"File", "Close All"}, true);

				window->setTitle(path);
				this->_gui.add(window, "Image" + path);
				this->_selectedImageWindow = window;
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
			std::string path = this->_gui.getWidgetName(this->_selectedImageWindow).substr(strlen("Image"));

			if (path.substr(path.find_last_of('.')) != ".mimp")
				path = Utils::saveFileDialog("Save MIMP file", path, {{".+[.]mimp", "MIMP image file"}});

			if (path.empty())
				return;

			this->_selectedImageWindow->setTitle(path);
			this->_gui.remove(this->_selectedImageWindow);
			this->_gui.add(this->_selectedImageWindow, "Image" + path);
			this->_getSelectedCanvas()->getLayers().save(path);
		});
		menu->connectMenuItem({"File", "Save as"}, [this, menu] {
			std::string name = this->_gui.getWidgetName(this->_selectedImageWindow).substr(strlen("Image"));
			std::string path = Utils::saveFileDialog("Save MIMP file", name, {{".+[.]mimp", "MIMP image file"}});

			if (path.empty())
				return;
			this->_getSelectedCanvas()->getLayers().save(path);
		});
		menu->connectMenuItem({"File", "Export"}, [this, menu] {
			std::string name = this->_gui.getWidgetName(this->_selectedImageWindow).substr(strlen("Image"));
			std::string path = Utils::saveFileDialog("Export image", name, {{".+[.]png", "Portable Network Graphics (PNG)"}});

			if (path.empty())
				return;
			this->_getSelectedCanvas()->exportImage(path);
		});
		menu->connectMenuItem({"File", "Close"}, [this]{
			this->_selectedImageWindow->close();
		});
		menu->connectMenuItem({"File", "Quit"}, [this]{
			this->_mainWindow.close();
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
				menu->setMenuItemEnabled({"File", "Close"}, true);
				menu->setMenuItemEnabled({"File", "Close All"}, true);

				window->setTitle(path);
				this->_gui.add(window, "Image" + path);
				this->_selectedImageWindow = window;
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

	CanvasWidget::Ptr Editor::_getSelectedCanvas()
	{
		if (!this->_selectedImageWindow)
			return nullptr;
		return this->_selectedImageWindow->get<tgui::ScrollablePanel>("Canvas")->get<CanvasWidget>("Canvas");
	}

	tgui::Panel::Ptr Editor::_getLayerRightClickPanel()
	{
		auto panel = tgui::Panel::create();

		return panel;
	}

	tgui::Panel::Ptr Editor::_getLayerPanelRightClickPanel(tgui::ChildWindow::Ptr win, CanvasWidget::Ptr canvas, tgui::Widget::Ptr widget, tgui::Label::Ptr label, Layer &layer, unsigned index)
	{
		auto panel = tgui::Panel::create({110, 230});

		panel->getRenderer()->setBackgroundColor({"#D8D8D8"});
		panel->loadWidgetsFromFile("widgets/context_box.gui");

		auto visible = panel->get<tgui::Button>("Visible");
		auto locked = panel->get<tgui::Button>("Locked");
		auto rename = panel->get<tgui::Button>("Rename");
		auto newLayer = panel->get<tgui::Button>("New layer");
		auto duplicate = panel->get<tgui::Button>("Duplicate");
		auto merge = panel->get<tgui::Button>("Merge");
		auto up = panel->get<tgui::Button>("Up");
		auto down = panel->get<tgui::Button>("Down");
		auto resize = panel->get<tgui::Button>("Resize");
		auto deleteLayaer = panel->get<tgui::Button>("Delete");

		visible->setText(layer.visible ? "Hide" : "Show");
		visible->connect("Pressed", [&layer, visible]{
			layer.visible = !layer.visible;
		});
		locked->setText(layer.locked ? "Unlock" : "Lock");
		locked->connect("Pressed", [&layer, locked]{
			layer.locked = !layer.locked;
		});
		newLayer->connect("Pressed", [this, locked, win, canvas, index]{
			auto &layers = canvas->getLayers();

			layers.addLayer(layers.getSize());
			layers.setLayerIndex(layers.size() - 1, index + 1);
			this->_makeLayersPanel(win, canvas);
		});
		duplicate->connect("Pressed", [this, &layer, locked, win, canvas, index]{
			auto &layers = canvas->getLayers();

			layers.addLayer(layer);
			layers.setLayerIndex(layers.size() - 1, index + 1);
			this->_makeLayersPanel(win, canvas);
		});
		return panel;
	}

	tgui::Panel::Ptr Editor::_makeLayersPanel(tgui::ChildWindow::Ptr win, CanvasWidget::Ptr canvas)
	{
		auto panel = win->get<tgui::ScrollablePanel>("Layers");
		auto &layers = canvas->getLayers();
		auto size = layers.size();

		if (!panel)
			panel = tgui::ScrollablePanel::create({170, 400});
		else
			panel->removeAllWidgets();

		for (size_t i = 0; i < size; i++) {
			auto &layer = layers[i];
			auto widget = tgui::Button::create();
			auto label = tgui::Label::create(layer.name);

			widget->setSize(64, 64);
			widget->setPosition(2, (size - i - 1) * 66 + 2);
			widget->connect("Clicked", [&layers, i]{
				layers.selectLayer(i);
			});
			widget->connect("RightClicked", [this, win, panel, widget, label, &layer, i, canvas](tgui::Vector2f pos){
				auto fakePanel = tgui::Panel::create({"100%", "100%"});
				auto pan = this->_getLayerPanelRightClickPanel(win, canvas, widget, label, layer, i);

				fakePanel->getRenderer()->setBackgroundColor({0, 0, 0, 0});
				fakePanel->connect("Clicked", [this, pan, fakePanel]{
					this->_gui.remove(pan);
					this->_gui.remove(fakePanel);
				});
				for (auto &wid : pan->getWidgets())
					wid->connect("Pressed", [this, pan, fakePanel]{
						this->_gui.remove(pan);
						this->_gui.remove(fakePanel);
					});
				pos.x += win->getPosition().x + panel->getPosition().x;
				pos.y += win->getPosition().y + panel->getPosition().y;
				pan->setPosition(pos);
				this->_gui.add(fakePanel);
				this->_gui.add(pan);
			});

			label->setPosition(66, (size - i - 1) * 66 + 26);

			panel->add(widget, "Widget" + std::to_string(i));
			panel->add(label, "Label" + std::to_string(i));
		}
		return panel;
	}
}