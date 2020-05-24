//
// Created by Gegel85 on 07/04/2020.
//

#include "ToolFactory.hpp"
#include "Pencil.hpp"
#include "Fill.hpp"
#include "ColorPick.hpp"
#include "FillSelection.hpp"
#include "RectSelectTool.hpp"
#include "SelectByColorTool.hpp"
#include "EllipseSelectionTool.hpp"
#include "Eraser.hpp"
#include "Move.hpp"

namespace Mimp
{
	const std::vector<std::function<std::shared_ptr<Tool>(ToolBox &)>> ToolFactory::_builders{
		[](ToolBox &box){
			return std::make_shared<Pencil>(box);
		},
		[](ToolBox &box){
			return std::make_shared<Fill>(box);
		},
		[](ToolBox &box){
			return std::make_shared<ColorPick>(box);
		},
		[](ToolBox &box){
			return std::make_shared<FillSelection>(box);
		},
		[](ToolBox &box){
			return std::make_shared<RectSelectTool>(box);
		},
		[](ToolBox &box){
			return std::make_shared<EllipseSelectionTool>(box);
		},
		[](ToolBox &box){
			return std::make_shared<SelectByColorTool>(box);
		},
		[](ToolBox &box){
			return std::make_shared<Eraser>(box);
		},
		[](ToolBox &){
			return std::make_shared<Move>();
		}
	};

	std::vector<std::shared_ptr<Tool>> ToolFactory::buildAll(ToolBox &box)
	{
		std::vector<std::shared_ptr<Tool>> array;

		array.reserve(ToolFactory::_builders.size());
		for (auto &func : ToolFactory::_builders)
			array.push_back(func(box));
		return array;
	}
}