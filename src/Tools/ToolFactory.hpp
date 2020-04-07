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
	class ToolFactory {
	private:
		static const std::vector<std::function<std::shared_ptr<Tool>()>> _builders;

	public:
		static std::vector<std::shared_ptr<Tool>> buildAll();
	};
}


#endif //MYGIMP_TOOLFACTORY_HPP
