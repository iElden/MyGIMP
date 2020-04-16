//
// Created by Gegel85 on 07/04/2020.
//

#ifdef __GNUG__
#include <cxxabi.h>
#endif
#include <filesystem>
#include <codecvt>
#include <SFML/Graphics.hpp>
#include <TGUI/TGUI.hpp>
#include <iostream>
#include "Utils.hpp"
#include "Exceptions.hpp"

namespace Mimp::Utils
{
	static const std::pair<std::string, std::string> _icons[] = {
		{"icons/folder.png",     ""},
		{"icons/archive.png",    ".rar"},
		{"icons/archive.png",    ".zip"},
		{"icons/archive.png",    ".7z"},
		{"icons/archive.png",    ".tgz"},
		{"icons/archive.png",    ".tar.gz"},
		{"icons/archive.png",    ".tar.xz"},
		{"icons/webFile.png",    ".htm"},
		{"icons/webFile.png",    ".html"},
		{"icons/webFile.png",    ".css"},
		{"icons/discFile.png",   ".iso"},
		{"icons/textFile.png",   ".txt"},
		{"icons/textFile.png",   ".doc"},
		{"icons/midiFile.png",   ".mid"},
		{"icons/midiFile.png",   ".midi"},
		{"icons/javaFile.png",   ".class"},
		{"icons/javaFile.png",   ".jar"},
		{"icons/fontsFile.png",  ".ttf"},
		{"icons/fontsFile.png",  ".otf"},
		{"icons/musicFile.png",  ".wav"},
		{"icons/musicFile.png",  ".ogg"},
		{"icons/musicFile.png",  ".mp3"},
		{"icons/imageFile.png",  ".png"},
		{"icons/imageFile.png",  ".jpg"},
		{"icons/imageFile.png",  ".jpeg"},
		{"icons/imageFile.png",  ".bmp"},
		{"icons/imageFile.png",  ".gif"},
		{"icons/binaryFile.png", ".exe"},
		{"icons/binaryFile.png", ".o"},
		{"icons/binaryFile.png", ".out"},
		{"icons/binaryFile.png", ".a"},
		{"icons/binaryFile.png", ".gch"},
		{"icons/binaryFile.png", ".dll"},
		{"icons/binaryFile.png", ".so"},
		{"icons/configFile.png", ".xml"},
		{"icons/configFile.png", ".ini"},
		{"icons/configFile.png", ".json"},
		{"icons/configFile.png", ".md"},
		{"icons/sourceFile.png", ".c"},
		{"icons/sourceFile.png", ".h"},
		{"icons/sourceFile.png", ".hpp"},
		{"icons/sourceFile.png", ".cpp"},
		{"icons/sourceFile.png", ".lua"},
		{"icons/sourceFile.png", ".java"},
		{"icons/sourceFile.png", ".py"},
		{"icons/sourceFile.png", ".asm"},
		{"icons/sourceFile.png", ".php"},
		{"icons/sourceFile.png", ".js"},
		{"icons/shellScript.png",".sh"},
		{"icons/shellScript.png",".run"},
		{"icons/shellScript.png",".bat"},
		{"icons/unknownFile.png",""},
	};

	std::wstring utf8_to_wstring(const std::string& str)
	{
		std::wstring_convert<std::codecvt_utf8<wchar_t>> myconv;
		return myconv.from_bytes(str);
	}

	std::string wstring_to_utf8(const std::wstring& str)
	{
		std::wstring_convert<std::codecvt_utf8<wchar_t>> myconv;
		return myconv.to_bytes(str);
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
/*
#ifdef _WIN32
	std::string openFileDialog(const std::string &title, const std::string &basePath, const std::vector<std::pair<std::string, std::string>> &patterns)
	{
		OPENFILENAME  ofn;
		char *filters = nullptr;
		size_t length = strlen("All Files\0*\0\0");
		char file[MAX_PATH];
		TCHAR** lppPart={nullptr};

		if (!GetFullPathName(
			basePath.c_str(),
			sizeof(file),
			file,
			lppPart
		))
			throw InvalidArgumentException("GetFullPathName failed with code " + std::to_string(GetLastError()));

		strcat(file, "\\*");
		for (auto &pair : patterns)
			length += pair.first.size() + pair.second.size() + 2;

		if (!patterns.empty()) {
			size_t pos = 0;

			filters = new char[length];
			for (auto &pair : patterns) {
				strcpy(&filters[pos], pair.second.c_str());
				pos += pair.second.size() + 1;
				strcpy(&filters[pos], pair.first.c_str());
				pos += pair.first.size() + 1;
			}
			memcpy(&filters[pos], "All Files\0*\0\0", strlen("All Files\0*\0\0"));
		}

		memset(&ofn, 0, sizeof(ofn));
		ofn.lStructSize       = sizeof(ofn);
		ofn.hwndOwner         = nullptr;
		ofn.lpstrFilter       = filters;
		ofn.lpstrFile         = file;
		ofn.nMaxFile          = sizeof(file);
		ofn.lpstrTitle        = title.c_str();
		ofn.nFilterIndex      = 1;
		ofn.Flags             = OFN_NONETWORKBUTTON | OFN_FILEMUSTEXIST;

		if (GetOpenFileName(&ofn)) {
			delete[] filters;
			return file;
		}
		delete[] filters;
		return "";
	}

	std::string saveFileDialog(const std::string &title, const std::string &basePath, const std::vector<std::pair<std::string, std::string>> &patterns)
	{
		OPENFILENAME  ofn;
		char *filters = nullptr;
		size_t length = strlen("All Files\0*\0\0");
		char file[MAX_PATH];
		TCHAR** lppPart={nullptr};

		if (!GetFullPathName(
			basePath.c_str(),
			sizeof(file),
			file,
			lppPart
		))
			throw InvalidArgumentException("GetFullPathName failed with code " + std::to_string(GetLastError()));

		if (GetFileAttributesA(file) != INVALID_FILE_ATTRIBUTES && (GetFileAttributesA(file) & FILE_DIRECTORY_FILE))
			strcat(file, "\\*");
		else if (!patterns.empty()) {
			auto pattern = patterns[0].first;
			auto pos = pattern.find_last_of('*');

			strcpy(file, (pattern.substr(0, pos) + file + pattern.substr(pos + 1)).c_str());
		}

		for (auto &pair : patterns)
			length += pair.first.size() + pair.second.size() + 2;

		if (!patterns.empty()) {
			size_t pos = 0;

			filters = new char[length];
			for (auto &pair : patterns) {
				strcpy(&filters[pos], pair.second.c_str());
				pos += pair.second.size() + 1;
				strcpy(&filters[pos], pair.first.c_str());
				pos += pair.first.size() + 1;
			}
			memcpy(&filters[pos], "All Files\0*\0\0", strlen("All Files\0*\0\0"));
		}

		memset(&ofn, 0, sizeof(ofn));
		ofn.lStructSize       = sizeof(ofn);
		ofn.hwndOwner         = nullptr;
		ofn.lpstrFilter       = filters;
		ofn.lpstrFile         = file;
		ofn.nMaxFile          = sizeof(file);
		ofn.nFilterIndex      = 1;
		ofn.lpstrTitle        = title.c_str();
		ofn.Flags             = OFN_NONETWORKBUTTON | OFN_OVERWRITEPROMPT;

		if (GetSaveFileName(&ofn)) {
			delete[] filters;
			return file;
		}
		delete[] filters;
		return "";
	}
#else*/
	std::string openFileDialog(const std::string &title, const std::string &basePath, const std::vector<std::pair<std::string, std::string>> &patterns)
	{
		sf::RenderWindow window{{500, 300}, title};
		tgui::Gui gui{window};
		std::string result;
		std::string startText;
		std::filesystem::path currentPath = basePath;
		sf::Event event;

		currentPath = std::filesystem::absolute(currentPath);
		std::cout << "'" << currentPath << "' !! '" << startText << "'" << std::endl;
		while (!std::filesystem::is_directory(currentPath)) {
			if (!startText.empty())
				startText += std::filesystem::path::preferred_separator;
			#ifdef _GLIBCXX_FILESYSTEM_IS_WINDOWS
			startText += wstring_to_utf8(currentPath.filename());
			#else
			startText += currentPath.filename();
			#endif
			currentPath = currentPath.parent_path();
			std::cout << "'" << currentPath << "' !! '" << startText << "'" << std::endl;
		}

		gui.loadWidgetsFromFile("widgets/open_file_dialog.gui");

		auto path = gui.get<tgui::TextBox>("Path");
		auto file = gui.get<tgui::EditBox>("file");
		auto box = gui.get<tgui::ComboBox>("Patterns");
		auto open = [&result, &window, &path, box, file]{
			if (file->getText().isEmpty())
				return;

			std::string ext = box->getSelectedItemId();

			if (ext.find_first_of('*') != std::string::npos)
				ext = ext.substr(ext.find_first_of('*') + 1);

			result = path->getText() + std::filesystem::path::preferred_separator + file->getText();
			if (result.find_last_of('.') == std::string::npos)
				result += ext;
			window.close();
		};

		gui.get<tgui::Button>("Cancel")->connect("Clicked", [&result, &window]{
			result = "";
			window.close();
		});
		gui.get<tgui::Button>("Open")->connect("Clicked", open);

		for (auto &pair : patterns)
			box->addItem(pair.second, pair.first);
		box->addItem("All files");
		box->setSelectedItemByIndex(0);

		#ifdef _GLIBCXX_FILESYSTEM_IS_WINDOWS
		path->setText(wstring_to_utf8(currentPath));
		#else
		path->setText(static_cast<std::string>(currentPath));
		#endif
		file->setText(startText);

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
		return openFileDialog(title, basePath, patterns);
	}
//#endif
}