#include "ShortcutManager.hpp"
#include <iostream>
#include <fstream>
#include "Exceptions.hpp"

namespace Mimp {

	ShortcutManager::ShortcutManager(ToolBox &tb, std::map<std::string, std::shared_ptr<ImageOperation>> io) :
		_io(io)
	{
		std::ifstream input{"shortcuts.ini"};

		if (input.fail()) {
			std::cout << "No shortcuts.ini file found. Creating default one..." << std::endl;
			std::ofstream output{"shortcuts.ini"};

			for (auto &i : io) {
				output << i.first << ":" << i.second->getKeyStroke()->toString() << "\n";
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
				if (io.find(s.first) == io.end()) {
					throw std::exception();
				}
			}

			for (auto &s : shortcuts) {
				Keys::KeyCombination kc{};
				kc.fromString(s.second);
				io[s.first]->setKeyStroke(kc);
			}
		} catch (...) {
			std::cout << "Problem while reading shortcuts.ini, using default settings." << std::endl;
		}
		input.close();
	}

	ShortcutManager::~ShortcutManager() {
		std::ofstream output{"shortcuts.ini"};

		for (auto &i : _io) {
			output << i.first << ":" << i.second->getKeyStroke()->toString() << "\n";
		}
		output.close();
	}
}