#include "ShortcutManager.hpp"
#include <iostream>
#include <fstream>
#include "Exceptions.hpp"

namespace Mimp {

	ShortcutManager::ShortcutManager(ToolBox &tb, std::unordered_map<std::string, std::shared_ptr<ImageOperation>> io) :
			_io(io)
	{
		/*
		std::cout << "Tools :" << std::endl;
		for (auto &t : tb.getTools()) {
			std::cout << t.first << ":" << t.second->getParametersPanel()->getSize().x << ","
			          << t.second->getParametersPanel()->getSize().y << std::endl;
		}

		std::cout << "Image Operations :" << std::endl;
		for (auto &i : io) {
			std::cout << i.first << ":" << i.second->getKeyStroke()->toString() << std::endl;
		}

		io["Select all"]->setKeyStroke({Keys::KEY_U, true, false, true});

				std::cout << "Image Operations 2 :" << std::endl;
		for (auto &i : io) {
			std::cout << i.first << ":" << i.second->getKeyStroke()->toString() << std::endl;
		}
	*/
		std::ifstream input;
		input.open("shortcuts.ini", std::ios::in | std::ios::out);

		if (input.fail()) {
			std::cout << "No shortcuts.ini file found. Creating default one..." << std::endl;
			std::ofstream output{"shortcuts.ini"};

			for (auto &i : io) {
				output << i.first << ":" << i.second->getKeyStroke()->toString() << "\n";
			}
			output.close();
		} else {
			try {
				std::stringstream s;

				s << input.rdbuf();

				std::unordered_map<std::string, std::string> shortcuts;

				std::string tmp;
				while (std::getline(s, tmp, '\n')) {
					std::size_t pos = tmp.find(":");
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
					std::cout << io.find(s.first)->second->name << ">>>" << kc.toString() << std::endl;
				}
			} catch (...) {
				std::cout << "Problem while reading shortcuts.ini, using default settings." << std::endl;
			}
		}
	}

	ShortcutManager::~ShortcutManager() {
		std::ofstream output{"shortcuts.ini"};

		for (auto &i : _io) {
			output << i.first << ":" << i.second->getKeyStroke()->toString() << "\n";
		}
		output.close();
	}
}