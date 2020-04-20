//
// Created by Gegel85 on 07/04/2020.
//

#ifdef __GNUG__
#include <cxxabi.h>
#endif
#include <regex>
#include <codecvt>
#include <SFML/Graphics.hpp>
#include <TGUI/TGUI.hpp>
#include <iostream>
#include <numeric>
#include "Utils.hpp"
#include "Exceptions.hpp"

namespace Mimp::Utils
{
	static const std::map<std::string, std::string> _icons{
		{"folder", "icons/folder.png"     },
		{".rar",   "icons/archive.png"    },
		{".zip",   "icons/archive.png"    },
		{".7z",    "icons/archive.png"    },
		{".tgz",   "icons/archive.png"    },
		{".gz",    "icons/archive.png"    },
		{".xz",    "icons/archive.png"    },
		{".htm",   "icons/webFile.png"    },
		{".html",  "icons/webFile.png"    },
		{".css",   "icons/webFile.png"    },
		{".mimp",  "icons/mimpFile.png"   },
		{".iso",   "icons/discFile.png"   },
		{".txt",   "icons/textFile.png"   },
		{".doc",   "icons/textFile.png"   },
		{".mid",   "icons/midiFile.png"   },
		{".midi",  "icons/midiFile.png"   },
		{".class", "icons/javaFile.png"   },
		{".jar",   "icons/javaFile.png"   },
		{".ttf",   "icons/fontsFile.png"  },
		{".otf",   "icons/fontsFile.png"  },
		{".wav",   "icons/musicFile.png"  },
		{".ogg",   "icons/musicFile.png"  },
		{".mp3",   "icons/musicFile.png"  },
		{".png",   "icons/imageFile.png"  },
		{".jpg",   "icons/imageFile.png"  },
		{".jpeg",  "icons/imageFile.png"  },
		{".bmp",   "icons/imageFile.png"  },
		{".gif",   "icons/imageFile.png"  },
		{".exe",   "icons/binaryFile.png" },
		{".o",     "icons/binaryFile.png" },
		{".out",   "icons/binaryFile.png" },
		{".a",     "icons/binaryFile.png" },
		{".gch",   "icons/binaryFile.png" },
		{".dll",   "icons/binaryFile.png" },
		{".so",    "icons/binaryFile.png" },
		{".xml",   "icons/configFile.png" },
		{".ini",   "icons/configFile.png" },
		{".json",  "icons/configFile.png" },
		{".md",    "icons/configFile.png" },
		{".c",     "icons/sourceFile.png" },
		{".h",     "icons/sourceFile.png" },
		{".hpp",   "icons/sourceFile.png" },
		{".cpp",   "icons/sourceFile.png" },
		{".lua",   "icons/sourceFile.png" },
		{".java",  "icons/sourceFile.png" },
		{".py",    "icons/sourceFile.png" },
		{".asm",   "icons/sourceFile.png" },
		{".php",   "icons/sourceFile.png" },
		{".js",    "icons/sourceFile.png" },
		{".sh",    "icons/shellScript.png"},
		{".run",   "icons/shellScript.png"},
		{".bat",   "icons/shellScript.png"},
		{"",       "icons/unknownFile.png"},
	};

	std::wstring utf8ToWstring(const std::string& str)
	{
		std::wstring_convert<std::codecvt_utf8<wchar_t>> myconv;
		return myconv.from_bytes(str);
	}

	std::string wstringToUtf8(const std::wstring& str)
	{
		std::wstring_convert<std::codecvt_utf8<wchar_t>> myconv;
		return myconv.to_bytes(str);
	}

	std::string pathToString(const std::filesystem::path &path) {
#ifdef _GLIBCXX_FILESYSTEM_IS_WINDOWS
		std::string result;
		std::wstring p = path;

		result.reserve(p.size());
		for (wchar_t c : p)
			if (c > 255)
				result.push_back('?');
			else
				result.push_back(c);
		return result;
#else
		return path;
#endif
	}

	std::string getLastExceptionName()
	{
#ifdef __GNUG__
		int status;
		char *value;
		std::string name;

		auto val = abi::__cxa_current_exception_type();

		if (!val)
			return "No exception";

		value = abi::__cxa_demangle(val->name(), nullptr, nullptr, &status);
		name = value;
		free(value);
		return name;
#else
		return "Unknown exception";
#endif
	}

	int	dispMsg(const std::string &title, const std::string &content, int variate)
	{
#ifdef _WIN32
		return (MessageBox(nullptr, content.c_str(), title.c_str(), variate));
#else
//		sf::RenderWindow win{{700, 220}, title, sf::Style::Titlebar | sf::Style::Close};
//		tgui::Gui gui{win};
#endif
	}

	static void _makeFolders(
		std::filesystem::path &currentPath,
		const tgui::ScrollablePanel::Ptr &panel,
		const tgui::EditBox::Ptr &file,
		const std::function<void()> &open,
		const std::regex &pattern = std::regex(".*", std::regex_constants::icase)
	) {
		auto pos = 10;
		std::vector<std::filesystem::directory_entry> paths = {
			std::filesystem::directory_entry("."),
			std::filesystem::directory_entry("..")
		};

		for (auto &entry : std::filesystem::directory_iterator(currentPath))
			paths.push_back(entry);

		panel->removeAllWidgets();
		for (auto &entry : paths) {
			std::string pic;
			const auto &filePath = entry.path();
			auto fileStr = pathToString(filePath.filename());

			if (entry.is_directory())
				pic = _icons.at("folder");
			else if (!std::regex_search(pathToString(filePath), pattern))
				continue;
			else
				try {
					pic = _icons.at(pathToString(filePath.extension()));
				} catch (std::out_of_range &) {
					pic = _icons.at("");
				}

			auto button = tgui::Button::create("");
			auto picture = tgui::Picture::create(pic);
			auto label = tgui::Label::create(fileStr);
			auto renderer = button->getRenderer();

			button->setPosition(10, pos);
			button->setSize({"&.w - 40", 20});
			button->connect("Clicked", [button, file, fileStr, &open]{
				if (file->getText() == fileStr)
					open();
				else
					file->setText(fileStr);
			});
			renderer->setBackgroundColor("transparent");
			renderer->setBackgroundColorFocused("blue");
			renderer->setBackgroundColorHover("#00BFFF");
			renderer->setBorderColor("transparent");
			renderer->setBorderColorHover("#00BFFF");
			label->setPosition(40, pos + 2);
			label->ignoreMouseEvents();
			picture->setPosition(12, pos + 2);
			picture->ignoreMouseEvents();
			panel->add(button);
			panel->add(label);
			panel->add(picture);
			pos += 30;
		}

		auto label = tgui::Label::create();

		label->setPosition(40, pos - 11);
		label->setSize(10, 9);
		panel->add(label);

		panel->setVerticalScrollAmount(30);
		panel->setVerticalScrollbarValue(0);
	}

	std::string cleanPath(const std::string &path)
	{
		std::vector<std::string> files = {};
		std::istringstream iss{path};
		std::string item;

		while (std::getline(iss, item, static_cast<char>(std::filesystem::path::preferred_separator)))
			if (item == "..") {
				if (files.size() > 1)
					files.pop_back();
			} else if (item != ".")
				files.push_back(item);

		return std::accumulate(
			files.begin() + 1,
			files.end(),
			files[0],
			[](const std::string &a, const std::string &b){
				return a + static_cast<char>(std::filesystem::path::preferred_separator) + b;
			}
		);
	}

	std::string openFileDialog(const std::string &title, const std::string &basePath, const std::vector<std::pair<std::string, std::string>> &patterns, bool overWriteWarning, bool mustExist)
	{
		sf::RenderWindow window{{500, 300}, title, sf::Style::Titlebar};
		tgui::Gui gui{window};
		std::string result;
		std::string startText;
		std::filesystem::path currentPath = basePath;
		sf::Event event;

		currentPath = std::filesystem::absolute(currentPath);
		while (!std::filesystem::is_directory(currentPath)) {
			if (!startText.empty())
				startText += std::filesystem::path::preferred_separator;
			startText += pathToString(currentPath.filename());
			currentPath = currentPath.parent_path();
		}

		gui.loadWidgetsFromFile("widgets/open_file_dialog.gui");

		auto path = gui.get<tgui::TextBox>("Path");
		auto file = gui.get<tgui::EditBox>("file");
		auto box = gui.get<tgui::ComboBox>("Patterns");
		auto panel = gui.get<tgui::ScrollablePanel>("Folders");
		std::function<void()> open = [&gui, &result, &window, path, box, file, &currentPath, panel, &open, mustExist, overWriteWarning]{
			if (file->getText().isEmpty())
				return;

			std::string ext = box->getSelectedItemId();

			if (std::filesystem::path(file->getText()).is_relative())
				result = path->getText() + std::filesystem::path::preferred_separator + file->getText();
			else
				result = file->getText();

			if (std::filesystem::is_directory(result)) {
				result = cleanPath(result);
				currentPath = result + static_cast<char>(std::filesystem::path::preferred_separator);
				path->setText(pathToString(currentPath));
				file->setText("");
				_makeFolders(currentPath, panel, file, open, std::regex(box->getSelectedItemId().toAnsiString(), std::regex_constants::icase));
				return;
			}

			if (mustExist && !std::filesystem::exists(result))
				return;

			if (overWriteWarning && std::filesystem::exists(result)) {
				auto pan = tgui::Panel::create({"100%", "100%"});
				pan->getRenderer()->setBackgroundColor({0, 0, 0, 175});
				gui.add(pan);

				auto win = tgui::ChildWindow::create();
				win->setPosition("(&.w - w) / 2", "(&.h - h) / 2");
				gui.add(win);

				win->setFocused(true);

				const bool tabUsageEnabled = gui.isTabKeyUsageEnabled();
				auto closeWindow = [&gui, win, pan, tabUsageEnabled]{
					gui.remove(win);
					gui.remove(pan);
					gui.setTabKeyUsageEnabled(tabUsageEnabled);
				};

				pan->connect("Clicked", closeWindow);
				win->connect({"Closed", "EscapeKeyPressed"}, closeWindow);
				win->loadWidgetsFromFile("widgets/overwrite_warning.gui");

				auto label = win->get<tgui::Label>("Label");

				label->setText(result + label->getText());
				win->setSize(label->getSize().x + 20, 100);
				win->get<tgui::Button>("Yes")->connect("Clicked", [&window]{
					window.close();
				});
				win->get<tgui::Button>("No")->connect("Clicked", [win]{
					win->close();
				});
				return;
			}

			window.close();
		};

		gui.get<tgui::Button>("Cancel")->connect("Clicked", [&result, &window]{
			result = "";
			window.close();
		});
		gui.get<tgui::Button>("Open")->connect("Clicked", open);

		for (auto &pair : patterns)
			box->addItem(pair.second, pair.first);
		box->addItem("All files", ".*");
		box->setSelectedItemByIndex(0);
		box->connect("ItemSelected", [&currentPath, &panel, &file, &path, &box, &open]{
			_makeFolders(currentPath, panel, file, open, std::regex(box->getSelectedItemId().toAnsiString(), std::regex_constants::icase));
		});

		path->setText(pathToString(currentPath));
		file->setText(startText);
		_makeFolders(currentPath, panel, file, open, std::regex(box->getSelectedItemId().toAnsiString(), std::regex_constants::icase));

		while (window.isOpen()) {
			while (window.pollEvent(event)) {
				if (event.type == sf::Event::Closed) {
					result = "";
					window.close();
				} else if (event.type == sf::Event::Resized) {
					window.setView(sf::View{sf::FloatRect(0, 0, event.size.width, event.size.height)});
					gui.setView(sf::View{sf::FloatRect(0, 0, event.size.width, event.size.height)});
				}
				gui.handleEvent(event);
			}
			window.clear({200, 200, 200});
			gui.draw();
			window.display();
		}
		return result;
	}

	std::string saveFileDialog(const std::string &title, const std::string &basePath, const std::vector<std::pair<std::string, std::string>> &patterns)
	{
		return openFileDialog(title, basePath, patterns, true, false);
	}
}