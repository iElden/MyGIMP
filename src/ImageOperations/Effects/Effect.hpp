#ifndef MYGIMP_EFFECT_HPP
#define MYGIMP_EFFECT_HPP

#include <string>
#include <TGUI/TGUI.hpp>
#include "../../Widgets/CanvasWidget.hpp"

namespace Mimp {

	class Effect {
	public:
		Effect(std::shared_ptr<tgui::ChildWindow>) {};

		virtual void setImage(CanvasWidget::Ptr &image) { this->_image = image; }

	protected:
		CanvasWidget::Ptr _image;
	};

}

#endif //MYGIMP_EFFECT_HPP
