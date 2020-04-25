//
// Created by Gegel85 on 25/04/2020.
//

#ifndef MYGIMP_IMAGEOPERATIONFACTORY_HPP
#define MYGIMP_IMAGEOPERATIONFACTORY_HPP


#include <vector>
#include "ImageOperation.hpp"

namespace Mimp
{
	class ImageOperationFactory {
	private:
		static const std::vector<std::function<std::shared_ptr<ImageOperation>()>> _builders;

	public:
		static std::vector<std::shared_ptr<ImageOperation>> buildAll();
	};
}

#endif //MYGIMP_IMAGEOPERATIONFACTORY_HPP
