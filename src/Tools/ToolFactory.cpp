//
// Created by Gegel85 on 07/04/2020.
//

#include "ToolFactory.hpp"
#include "Pencil.hpp"

namespace Mimp
{
	const std::vector<std::function<std::shared_ptr<Tool>(ToolBox &)>> ToolFactory::_builders{
		[](ToolBox &box){
			return std::make_shared<Pencil>(box);
		}

	};

	std::vector<std::shared_ptr<Tool>> ToolFactory::buildAll(ToolBox &box)
	{
		std::vector<std::shared_ptr<Tool>> array{ToolFactory::_builders.size()};

		for (auto &func : ToolFactory::_builders)
			array.push_back(func(box));
		return array;
	}
}