//
// Created by Gegel85 on 25/04/2020.
//

#include "ImageOperationFactory.hpp"
#include "Selection/FillSelectionOperation.hpp"
#include "Selection/InvertSelectionOperation.hpp"
#include "Selection/UnselectOperation.hpp"
#include "Selection/SelectAllOperation.hpp"
#include "Selection/DelSelectionOperation.hpp"
#include "Selection/ExpandSelection.hpp"
#include "Selection/ExpandMoreSelection.hpp"
#include "Selection/ShrinkSelection.hpp"
#include "Selection/ShrinkMoreSelection.hpp"
#include "Selection/OutlineSelectionOperation.hpp"
#include "Selection/OutlineMoreSelectionOperation.hpp"
#include "Clipboard/PasteOperation.hpp"
#include "Clipboard/CopyOperation.hpp"
#include "Clipboard/CutOperation.hpp"
#include "Layer/MoveLeft.hpp"
#include "Layer/MoveRight.hpp"
#include "Layer/MoveUp.hpp"
#include "Layer/MoveDown.hpp"
#include "Layer/RotateRight90.hpp"

namespace Mimp
{
	const std::vector<std::function<std::shared_ptr<ImageOperation>()>> ImageOperationFactory::_builders{
		[]{
			return std::make_shared<CutOperation>();
		},
		[]{
			return std::make_shared<CopyOperation>();
		},
		[]{
			return std::make_shared<PasteOperation>();
		},
		[]{
			return std::make_shared<SelectAllOperation>();
		},
		[]{
			return std::make_shared<UnselectOperation>();
		},
		[]{
			return std::make_shared<InvertSelectionOperation>();
		},
		[]{
			return std::make_shared<FillSelectionOperation>();
		},
		[]{
			return std::make_shared<DelSelectionOperation>();
		},
		[]{
			return std::make_shared<ExpandSelection>();
		},
		[]{
			return std::make_shared<ExpandMoreSelection>();
		},
		[]{
			return std::make_shared<ShrinkSelection>();
		},
		[]{
			return std::make_shared<ShrinkMoreSelection>();
		},
		[]{
			return std::make_shared<OutlineSelectionOperation>();
		},
		[]{
			return std::make_shared<OutlineMoreSelectionOperation>();
		},
		[]{
			return std::make_shared<MoveUp>();
		},
		[]{
			return std::make_shared<MoveDown>();
		},
		[]{
			return std::make_shared<MoveLeft>();
		},
		[]{
			return std::make_shared<MoveRight>();
		},
		[]{
			return std::make_shared<RotateRight90>();
		}
	};

	std::vector<std::shared_ptr<ImageOperation>> ImageOperationFactory::ios{};

	std::vector<std::shared_ptr<ImageOperation>> ImageOperationFactory::buildAll()
	{
		for (auto &fct : ImageOperationFactory::_builders)
			ImageOperationFactory::ios.push_back(fct());
		return ios;
	}

	std::map<std::string, std::shared_ptr<ImageOperation>> ImageOperationFactory::get()
	{
		std::map<std::string, std::shared_ptr<ImageOperation>> result;

		for (auto &io : ImageOperationFactory::ios) {
			result[io->name] = io;
		}
		return result;
	}
}