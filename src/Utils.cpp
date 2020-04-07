//
// Created by Gegel85 on 07/04/2020.
//

#include <cxxabi.h>
#include "Utils.hpp"

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
}