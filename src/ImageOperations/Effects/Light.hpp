#ifndef MYGIMP_LIGHT_HPP
#define MYGIMP_LIGHT_HPP

#include "Effect.hpp"
#include "../../Widgets/CanvasWidget.hpp"

namespace Mimp {
	class Light : public Effect {
	public:
		Light(std::shared_ptr<tgui::ChildWindow> window);
	};
}


#endif //MYGIMP_LIGHT_HPP
