#include <iostream>
#include <fstream>
#include "ShortcutManager.hpp"
#include "ShortcutComparator.hpp"
#include "Exceptions.hpp"

namespace Mimp {

	ShortcutManager::ShortcutManager(std::map<std::string, std::shared_ptr<Tool>> tb, std::map<std::string, std::shared_ptr<ImageOperation>> io) :
		_io(io), _tb(tb)
	{
		for (auto &i : _io) {
			this->_shortcuts[i.first] = i.second;
		}
		for (auto &i : _tb) {
			this->_shortcuts[i.first] = i.second;
		}

		std::ifstream input{"shortcuts.ini"};

		if (input.fail()) {
			std::cout << "No shortcuts.ini file found. Creating default one..." << std::endl;
			std::ofstream output{"shortcuts.ini"};

			for (auto &i : _shortcuts) {
				output << i.first << ":" << i.second->getKeyCombination().toString() << "\n";
			}
			output.close();
			return;
		}

		try {
			std::map<std::string, std::string> shortcuts;

			std::string tmp;
			while (std::getline(input, tmp, '\n')) {
				std::size_t pos = tmp.find(':');
				if (pos == std::string::npos) {
					throw std::exception();
				}
				std::string key = tmp.substr(0, pos);
				std::string value = tmp.substr(pos + 1, tmp.length());

				shortcuts[key] = value;
			}

			for (auto &s : shortcuts) {
				if (_shortcuts.find(s.first) == _shortcuts.end()) {
					throw std::exception();
				}
			}

			for (auto &s : shortcuts) {
				Keys::KeyCombination kc{};
				kc.fromString(s.second);
				_shortcuts[s.first]->setKeyCombination(kc);
			}
		} catch (...) {
			std::cout << "Problem while reading shortcuts.ini, using default settings." << std::endl;
		}
		input.close();
	}

	ShortcutManager::~ShortcutManager() {
		std::ofstream output{"shortcuts.ini"};

		for (auto &i : _shortcuts) {
			output << i.first << ":" << i.second->getKeyCombination().toString() << "\n";
		}
		output.close();
	}

	bool ShortcutManager::isValid(std::map<std::string, Keys::KeyCombination>& other)
	{
		for (auto &s : other) {
			if (s.second.key != Keys::KEY_UNKNOWN && std::count(other.begin(), other.end(), Compare(s.second)) > 1) {
				return false;
			}
		}
		return true;
	}
}