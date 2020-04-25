//
// Created by Gegel85 on 25/04/2020.
//

#ifndef MYGIMP_IMAGEOPERATION_HPP
#define MYGIMP_IMAGEOPERATION_HPP


#include <TGUI/Gui.hpp>
#include "../Image.hpp"

namespace Mimp
{
	class ImageOperation {
	private:
		std::vector<std::string> _hierarchy;

	protected:
		ImageOperation(const std::vector<std::string> &&hierarchy);

	public:
		virtual void click(tgui::Gui &, Image &) const = 0;
		const std::vector<std::string> &getMenuHierarchy() const;
	};
}


#endif //MYGIMP_IMAGEOPERATION_HPP
