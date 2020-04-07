//
// Created by Gegel85 on 07/04/2020.
//

#include "ToolFactory.hpp"

namespace Mimp
{
	const std::vector<std::function<std::shared_ptr<Tool>()>> ToolFactory::_builders{
		/* []{
		 * 	return std::make_shared<Tool>();
		 * }*/
	};

	std::vector<std::shared_ptr<Tool>> ToolFactory::buildAll()
	{
		std::vector<std::shared_ptr<Tool>> array{ToolFactory::_builders.size()};

		for (auto &func : ToolFactory::_builders)
			array.push_back(func());
		return array;
	}
}