#ifndef MYGIMP_SATURATION_HPP
#define MYGIMP_SATURATION_HPP


#include "Effect.hpp"

namespace Mimp {
	class Saturation : public Effect {
	public:
		Saturation(std::shared_ptr<tgui::ChildWindow> window);
	};
}

#endif //MYGIMP_SATURATION_HPP
