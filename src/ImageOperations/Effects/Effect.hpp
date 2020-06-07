//
// Created by Louprenard on 06/06/2020.
//

#ifndef MYGIMP_EFFECT_HPP
#define MYGIMP_EFFECT_HPP

#include <string>
#include "../../Widgets/CanvasWidget.hpp"

namespace Mimp {

	class Effect {
	public:
		Effect(const std::string &name, const std::string &configFile) : _name(name) {
			this->_panel = tgui::ScrollablePanel::create();
			this->_panel->loadWidgetsFromFile(configFile);
		}

		tgui::ScrollablePanel::Ptr getPanel(CanvasWidget::Ptr image) {
			this->_image = image;
			return this->_panel;
		}

		std::string getName() { return this->_name; }

	protected:
		tgui::ScrollablePanel::Ptr _panel;
		CanvasWidget::Ptr _image;

	private:
		std::string _name;

	};

}

#endif //MYGIMP_EFFECT_HPP
