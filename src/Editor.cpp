//
// Created by Gegel85 on 06/04/2020.
//

#include <TGUI/TGUI.hpp>
#include <iostream>
#include "Editor.hpp"
#include "Utils.hpp"
#include "ImageOperations/ImageOperationFactory.hpp"

namespace Mimp
{
	Editor::Editor(const std::vector<std::string> &images) :
		_mainWindow({640, 480}, "Mimp"),
		_gui(this->_mainWindow),
		_toolBox(this->_gui),
		_imgOps(ImageOperationFactory::buildAll())
	{
		this->_mainWindow.setFramerateLimit(240);
		this->_gui.loadWidgetsFromFile("widgets/top_menu.gui");
		this->_setupButtonCallbacks();

		auto win = this->_toolBox.getWindow();

		win->connect("Closed", [this, win] {
			this->_gui.remove(win);
		});
		this->_gui.add(win, "ToolBox");

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
		this->_selectImage(canvas);
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
				if (event.type == sf::Event::KeyPressed && this->_selectedImageWindow) {
					KeyCombination comb{
						Editor::SFMLKeyToKey(event.key.code),
						event.key.control,
						event.key.shift,
						event.key.alt
					};

					try {
						this->_keysImgOps.at(comb)->click(this->_gui, *this->_getSelectedCanvas());
					} catch (std::out_of_range &) {}
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

		canvasPanel->getRenderer()->setBackgroundColor("transparent");
		window->setSize({
			600,
			420
		});
		window->connect("Closed", [this, menu, window, canvas] {
			this->_unselectImage();
			canvas->disableRendering();
			this->_gui.remove(window);
			for (auto &name : this->_gui.getWidgetNames()) {
				if (name.substring(0, strlen("Image")) == "Image") {
					this->setSelectedImage(this->_gui.get<tgui::ChildWindow>(name));
					break;
				}
			}
		});
		window->connect("Focused", [this, window]{
			this->setSelectedImage(window);
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

		for (auto &imgOp : this->_imgOps) {
			std::vector<sf::String> hierarchy;
			auto key = imgOp->getKeyStroke();

			for (auto &elem : imgOp->getMenuHierarchy())
				hierarchy.emplace_back(elem);

			if (key) {
				this->_keysImgOps[*key] = imgOp;
				hierarchy.back() += " (" + key->toString() + ")";
			}

			menu->addMenuItem(hierarchy);
			menu->setMenuItemEnabled(hierarchy, false);
			menu->connectMenuItem(hierarchy, [this, imgOp]{
				imgOp->click(this->_gui, *this->_getSelectedCanvas());
			});
		}

		menu->addMenuItem({"Window", "Tools"});
		menu->connectMenuItem({"Window", "Tools"}, [this, menu]{
			this->_gui.remove(this->_gui.get<tgui::Widget>("ToolBox"));
			this->_gui.add(this->_toolBox.getWindow(), "ToolBox");
		});
		menu->addMenu("Help");
		menu->connect("MouseEntered", [](tgui::Widget::Ptr bar, const std::string&){
			bar->moveToFront();
		});
		menu->connectMenuItem({"File", "New"}, [this, menu]{
			auto win = Utils::openWindowWithFocus(this->_gui, 200, 110);

			win->loadWidgetsFromFile("widgets/new.gui");
			win->setTitle("New image");

			auto ok = win->get<tgui::Button>("OK");
			auto cancel = win->get<tgui::Button>("Cancel");

			cancel->connect("Pressed", [win]{ win->close(); });
			ok->connect("Pressed", [this, win] {
				std::string width = win->get<tgui::EditBox>("Width")->getText();
				std::string height = win->get<tgui::EditBox>("Height")->getText();

				if (width.empty() || height.empty())
					return;

				auto w = std::stoul(width);
				auto h = std::stoul(height);
				auto widget = CanvasWidget::create(this->_toolBox, Vector2<unsigned>{w, h});
				auto window = _makeImagePanel(widget);

				window->setTitle("Untitled " + std::to_string(++this->_lastUntitled));
				this->_gui.add(window, "ImageUntitled " + std::to_string(this->_lastUntitled));
				this->_selectImage(window);
				win->close();
			});
		});
		menu->connectMenuItem({"File", "Open"}, [this, menu]{
			std::string path = Utils::openFileDialog("Load MIMP file", ".", {{".+[.]mimp", "MIMP image file"}});

			if (path.empty())
				return;
			try {
				auto widget = CanvasWidget::create(this->_toolBox, path);
				auto window = _makeImagePanel(widget);

				window->setTitle(path);
				this->_gui.add(window, "Image" + path);
				this->_selectImage(window);
			} catch (std::exception &e) {
				Utils::dispMsg("Loading error", Utils::getLastExceptionName() + ": " + e.what(), MB_ICONERROR);
			}
		});
		menu->connectMenuItem({"File", "Save"}, [this, menu] {
			std::string path = this->_gui.getWidgetName(this->_selectedImageWindow).substr(strlen("Image"));

			if (path.find_last_of('.') == std::string::npos || path.substr(path.find_last_of('.')) != ".mimp")
				path = Utils::saveFileDialog("Save MIMP file", path, {{".+[.]mimp", "MIMP image file"}});

			if (path.empty())
				return;

			this->_selectedImageWindow->setTitle(path);
			this->_gui.remove(this->_selectedImageWindow);
			this->_gui.add(this->_selectedImageWindow, "Image" + path);
			try {
				this->_getSelectedCanvas()->getLayers().save(path);
			} catch (std::exception &e) {
				Utils::dispMsg("Save error", Utils::getLastExceptionName() + ": " + e.what(), MB_ICONERROR);
			}
		});
		menu->connectMenuItem({"File", "Save as"}, [this, menu] {
			std::string name = this->_gui.getWidgetName(this->_selectedImageWindow).substr(strlen("Image"));
			std::string path = Utils::saveFileDialog("Save MIMP file", name, {{".+[.]mimp", "MIMP image file"}});

			if (path.empty())
				return;
			try {
				this->_getSelectedCanvas()->getLayers().save(path);
			} catch (std::exception &e) {
				Utils::dispMsg("Save error", Utils::getLastExceptionName() + ": " + e.what(), MB_ICONERROR);
			}
		});
		menu->connectMenuItem({"File", "Export"}, [this, menu] {
			std::string name = this->_gui.getWidgetName(this->_selectedImageWindow).substr(strlen("Image"));
			std::string path = Utils::saveFileDialog("Export image", name, {{".+[.]png", "Portable Network Graphics (PNG)"}});

			if (path.empty())
				return;
			try {
				this->_getSelectedCanvas()->exportImage(path);
			} catch (std::exception &e) {
				Utils::dispMsg("Export error", Utils::getLastExceptionName() + ": " + e.what(), MB_ICONERROR);
			}
		});
		menu->connectMenuItem({"File", "Close"}, [this]{
			this->_selectedImageWindow->close();
		});
		menu->connectMenuItem({"File", "Quit"}, [this]{
			this->_mainWindow.close();
		});
		menu->connectMenuItem({"File", "Import", "Link"}, [this]{
			auto win = Utils::openWindowWithFocus(this->_gui, 210, 70);

			win->loadWidgetsFromFile("widgets/import_link.gui");
			win->setTitle("Import image");

			auto ok = win->get<tgui::Button>("OK");
			auto cancel = win->get<tgui::Button>("Cancel");

			cancel->connect("Pressed", [win]{ win->close(); });
			ok->connect("Pressed", [this, win] {
				auto link = win->get<tgui::EditBox>("Link");

				try {
					std::string path = link->getText();

					if (path.empty())
						return;

					auto widget = CanvasWidget::create(this->_toolBox, Vector2<unsigned>{0, 0});

					widget->importImageFromMemory(Utils::resolveUrl(path));

					auto window = _makeImagePanel(widget);
					auto pos = path.find_last_of('/');

					window->setTitle(path);
					this->_gui.add(window, "Image" + (pos == std::string::npos ? "index.png" : path.substr(pos)));
					this->_selectImage(window);

					win->close();
				} catch (std::exception &e) {
					Utils::dispMsg("Import error", Utils::getLastExceptionName() + ": " + e.what(), MB_ICONERROR);
				}
			});
		});
		menu->connectMenuItem({"File", "Import", "Local file"}, [this, menu] {
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

				widget->importImageFromFile(path);

				auto window = _makeImagePanel(widget);

				window->setTitle(path);
				this->_gui.add(window, "Image" + path);
				this->_selectImage(window);
			} catch (std::exception &e) {
				Utils::dispMsg("Import error", Utils::getLastExceptionName() + ": " + e.what(), MB_ICONERROR);
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

	tgui::Panel::Ptr Editor::_getLayerPanelRightClickPanel(tgui::ChildWindow::Ptr win, CanvasWidget::Ptr canvas, tgui::Panel::Ptr layersPanel, Layer &layer, unsigned index)
	{
		auto &layers = canvas->getLayers();
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
		auto deleteLayer = panel->get<tgui::Button>("Delete");
		auto move = panel->get<tgui::Button>("Move");

		if (layers.size() == 1)
			deleteLayer->setEnabled(false);
		if (!index) {
			down->setEnabled(false);
			merge->setEnabled(false);
		}
		if (index == layers.size() - 1)
			up->setEnabled(false);

		visible->setText(layer.visible ? "Hide" : "Show");
		visible->connect("Pressed", [&layer, visible, index, layersPanel]{
			layer.visible = !layer.visible;
			layersPanel->get<tgui::Widget>("VisibleCancel" + std::to_string(index))->setVisible(!layer.visible);
		});
		locked->setText(layer.locked ? "Unlock" : "Lock");
		locked->connect("Pressed", [&layer, locked, index, layersPanel]{
			layer.locked = !layer.locked;
			layersPanel->get<tgui::Widget>("LockedCancel" + std::to_string(index))->setVisible(!layer.locked);
		});
		newLayer->connect("Pressed", [this, locked, win, canvas, index, &layers]{
			layers.addLayer(layers.getSize());
			layers.setLayerIndex(layers.size() - 1, index + 1);
			this->_makeLayersPanel(win, canvas);
		});
		duplicate->connect("Pressed", [this, &layer, locked, win, canvas, index, &layers]{
			auto &lay = layers.addLayer(layer);

			lay.visible = true;
			lay.locked = false;
			layers.setLayerIndex(layers.size() - 1, index + 1);
			this->_makeLayersPanel(win, canvas);
		});
		merge->connect("Pressed", [&layer, &layers, index, this, win, canvas]{
			layers.selectLayer(index - 1);
			layers.getSelectedLayer().buffer.drawFrameBuffer(layer.pos, layer.buffer);
			layers.deleteLayer(index);
			this->_makeLayersPanel(win, canvas);
		});
		deleteLayer->connect("Pressed", [&layers, index, this, win, canvas]{
			layers.deleteLayer(index);
			this->_makeLayersPanel(win, canvas);
		});
		up->connect("Pressed", [&layers, index, this, win, canvas]{
			layers.setLayerIndex(index, index + 1);
			this->_makeLayersPanel(win, canvas);
		});
		down->connect("Pressed", [&layers, index, this, win, canvas]{
			layers.setLayerIndex(index, index - 1);
			this->_makeLayersPanel(win, canvas);
		});
		resize->connect("Pressed", [&layer, this, win, canvas]{
			auto win = Utils::openWindowWithFocus(this->_gui, 200, 110);

			win->loadWidgetsFromFile("widgets/new.gui");
			win->setTitle("New image");

			auto ok = win->get<tgui::Button>("OK");
			auto cancel = win->get<tgui::Button>("Cancel");
			auto width = win->get<tgui::EditBox>("Width");
			auto height = win->get<tgui::EditBox>("Height");

			width->setText(std::to_string(layer.getSize().x));
			height->setText(std::to_string(layer.getSize().y));
			cancel->connect("Pressed", [win]{ win->close(); });
			ok->connect("Pressed", [this, win, &layer, width, height] {
				std::string wid = width->getText();
				std::string hei = height->getText();

				if (wid.empty() || hei.empty())
					return;

				auto w = std::stoul(wid);
				auto h = std::stoul(hei);

				layer.buffer = layer.buffer.getRectFromBuffer({0, 0}, {w, h});
			});
		});
		move->connect("Pressed", [&layer, this, win, canvas]{
			auto win = Utils::openWindowWithFocus(this->_gui, 200, 110);

			win->loadWidgetsFromFile("widgets/new.gui");
			win->setTitle("New image");

			auto ok = win->get<tgui::Button>("OK");
			auto cancel = win->get<tgui::Button>("Cancel");
			auto width = win->get<tgui::EditBox>("Width");
			auto height = win->get<tgui::EditBox>("Height");

			width->setText(std::to_string(layer.pos.x));
			height->setText(std::to_string(layer.pos.y));
			cancel->connect("Pressed", [win]{ win->close(); });
			ok->connect("Pressed", [this, win, &layer, width, height] {
				std::string wid = width->getText();
				std::string hei = height->getText();

				if (wid.empty() || hei.empty())
					return;

				auto w = std::stoul(wid);
				auto h = std::stoul(hei);

				layer.pos = Vector2<int>(w, h);
			});
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
			auto visible = tgui::BitmapButton::create();
			auto locked = tgui::BitmapButton::create();
			auto visibleCancel = tgui::Picture::create("icons/cancel.png");
			auto lockedCancel = tgui::Picture::create("icons/cancel.png");
			auto widget = tgui::Button::create();
			auto label = tgui::Label::create(layer.name);

			locked->setImage("icons/locked.png");
			locked->setSize(18, 18);
			locked->setPosition(2 + 66, (size - i - 1) * 66 + 2);
			locked->connect("Pressed", [lockedCancel, &layer]{
				layer.locked = !layer.locked;
				lockedCancel->setVisible(!layer.locked);
			});
			lockedCancel->ignoreMouseEvents();
			lockedCancel->setVisible(!layer.locked);
			lockedCancel->setPosition(2 + 66 + 1, (size - i - 1) * 66 + 2 + 1);

			visible->setSize(18, 18);
			visible->setPosition(2 + 66 + 18, (size - i - 1) * 66 + 2);
			visible->setImage("icons/visible.png");
			visible->connect("Pressed", [visibleCancel, &layer]{
				layer.visible = !layer.visible;
				visibleCancel->setVisible(!layer.visible);
			});
			visibleCancel->ignoreMouseEvents();
			visibleCancel->setVisible(!layer.visible);
			visibleCancel->setPosition(2 + 66 + 18 + 1, (size - i - 1) * 66 + 2 + 1);

			widget->setSize(64, 64);
			widget->setPosition(2, (size - i - 1) * 66 + 2);
			widget->connect("Clicked", [&layers, i]{
				layers.selectLayer(i);
			});
			widget->connect("RightClicked", [this, win, panel, widget, label, &layer, i, canvas](tgui::Vector2f pos){
				auto fakePanel = tgui::Panel::create({"100%", "100%"});
				auto pan = this->_getLayerPanelRightClickPanel(win, canvas, panel, layer, i);

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
			panel->add(visible, "Visible" + std::to_string(i));
			panel->add(locked, "Locked" + std::to_string(i));
			panel->add(visibleCancel, "VisibleCancel" + std::to_string(i));
			panel->add(lockedCancel, "LockedCancel" + std::to_string(i));
		}
		return panel;
	}

	void Editor::_selectImage(tgui::ChildWindow::Ptr win)
	{
		auto menu = this->_gui.get<tgui::MenuBar>("main_bar");

		menu->setMenuItemEnabled({"File", "Save"}, true);
		menu->setMenuItemEnabled({"File", "Save as"}, true);
		menu->setMenuItemEnabled({"File", "Export"}, true);
		menu->setMenuItemEnabled({"File", "Close"}, true);
		menu->setMenuItemEnabled({"File", "Close All"}, true);

		for (auto &imgOp : this->_imgOps) {
			std::vector<sf::String> hierarchy;
			auto key = imgOp->getKeyStroke();

			for (auto &elem : imgOp->getMenuHierarchy())
				hierarchy.emplace_back(elem);

			if (key)
				hierarchy.back() += " (" + key->toString() + ")";

			menu->setMenuItemEnabled(hierarchy, true);
		}

		this->_selectedImageWindow = win;
	}

	void Editor::_unselectImage()
	{
		auto menu = this->_gui.get<tgui::MenuBar>("main_bar");

		menu->setMenuItemEnabled({"File", "Save"}, false);
		menu->setMenuItemEnabled({"File", "Save as"}, false);
		menu->setMenuItemEnabled({"File", "Export"}, false);
		menu->setMenuItemEnabled({"File", "Close"}, false);
		menu->setMenuItemEnabled({"File", "Close All"}, false);

		for (auto &imgOp : this->_imgOps) {
			std::vector<sf::String> hierarchy;
			auto key = imgOp->getKeyStroke();

			for (auto &elem : imgOp->getMenuHierarchy())
				hierarchy.emplace_back(elem);

			if (key)
				hierarchy.back() += " (" + key->toString() + ")";

			menu->setMenuItemEnabled(hierarchy, true);
		}

		this->_selectedImageWindow = nullptr;
	}

	Key Editor::SFMLKeyToKey(sf::Keyboard::Key key)
	{
		switch (key) {
		case sf::Keyboard::Key::A:
			return KEY_A;
		case sf::Keyboard::Key::B:
			return KEY_B;
		case sf::Keyboard::Key::C:
			return KEY_C;
		case sf::Keyboard::Key::D:
			return KEY_D;
		case sf::Keyboard::Key::E:
			return KEY_E;
		case sf::Keyboard::Key::F:
			return KEY_F;
		case sf::Keyboard::Key::G:
			return KEY_G;
		case sf::Keyboard::Key::H:
			return KEY_H;
		case sf::Keyboard::Key::I:
			return KEY_I;
		case sf::Keyboard::Key::J:
			return KEY_J;
		case sf::Keyboard::Key::K:
			return KEY_K;
		case sf::Keyboard::Key::L:
			return KEY_L;
		case sf::Keyboard::Key::M:
			return KEY_M;
		case sf::Keyboard::Key::N:
			return KEY_N;
		case sf::Keyboard::Key::O:
			return KEY_O;
		case sf::Keyboard::Key::P:
			return KEY_P;
		case sf::Keyboard::Key::Q:
			return KEY_Q;
		case sf::Keyboard::Key::R:
			return KEY_R;
		case sf::Keyboard::Key::S:
			return KEY_S;
		case sf::Keyboard::Key::T:
			return KEY_T;
		case sf::Keyboard::Key::U:
			return KEY_U;
		case sf::Keyboard::Key::V:
			return KEY_V;
		case sf::Keyboard::Key::W:
			return KEY_W;
		case sf::Keyboard::Key::X:
			return KEY_X;
		case sf::Keyboard::Key::Y:
			return KEY_Y;
		case sf::Keyboard::Key::Z:
			return KEY_Z;
		case sf::Keyboard::Key::Delete:
			return KEY_DEL;
		case sf::Keyboard::Key::Escape:
			return KEY_ESC;
		case sf::Keyboard::Key::Up:
			return KEY_UP;
		case sf::Keyboard::Key::Down:
			return KEY_DOWN;
		case sf::Keyboard::Key::Left:
			return KEY_LEFT;
		case sf::Keyboard::Key::Right:
			return KEY_RIGHT;
		default:
			return KEY_UNKNOWN;
		}
	}
}