//
// Created by Gegel85 on 07/04/2020.
//

#ifndef MYGIMP_TOOLFACTORY_HPP
#define MYGIMP_TOOLFACTORY_HPP


#include <vector>
#include <functional>
#include <memory>
#include "Tool.hpp"

namespace Mimp
{
	//! @brief Class ToolBox
	class ToolBox;

	//! @brief Class ToolFactory
	class ToolFactory {
	private:
		//! @brief Tools of the tool box
		//! @details Contains all the Tools under shared pointers
		static const std::vector<std::function<std::shared_ptr<Tool>(ToolBox &)>> _builders;
		static std::vector<std::shared_ptr<Tool>> tls;

	public:
		//! @brief Build all the tools
		//! @details Build all the tools under shared pointers
		//! @param toolBox ToolBox where the tools are built
		//! @return std::vector<std::shared_ptr<Tool>> Return a vector of Tools Shared Pointers
		static std::vector<std::shared_ptr<Tool>> buildAll(ToolBox &toolBox);

		//! @brief Get all the Tools.
		static std::unordered_map<std::string, std::shared_ptr<Tool>> get();
	};
}

#endif //MYGIMP_TOOLFACTORY_HPP
