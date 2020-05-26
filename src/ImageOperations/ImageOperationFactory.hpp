//
// Created by Gegel85 on 25/04/2020.
//

#ifndef MYGIMP_IMAGEOPERATIONFACTORY_HPP
#define MYGIMP_IMAGEOPERATIONFACTORY_HPP


#include <vector>
#include "ImageOperation.hpp"

namespace Mimp
{
	//! @brief Define the ImageOperationFactory.
	class ImageOperationFactory {
	private:
		static const std::vector<std::function<std::shared_ptr<ImageOperation>()>> _builders;
		static std::vector<std::shared_ptr<ImageOperation>> ios;

	public:
		//! @brief Build all the operations.
		//! @return A vector containing all the operations.
		static std::vector<std::shared_ptr<ImageOperation>> buildAll();

		static std::map<std::string, std::shared_ptr<ImageOperation>> get();
	};
}

#endif //MYGIMP_IMAGEOPERATIONFACTORY_HPP
