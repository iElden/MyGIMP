//
// Created by Gegel85 on 07/04/2020.
//

#ifdef __GNUG__
#include <cxxabi.h>
#endif
#include <iostream>
#include "Utils.hpp"
#include "Exceptions.hpp"

namespace Mimp::Utils
{
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
#else
	std::string openFileDialog(const std::string &basePath, const std::vector<std::pair<std::string, std::string>> &patterns)
	{
		return "";
	}

	std::string saveFileDialog(const std::string &basePath, const std::vector<std::pair<std::string, std::string>> &patterns)
	{
		return "";
	}
#endif
}