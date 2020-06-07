#include "Effects.hpp"
#include "Effects/Light.hpp"

#include <iostream>

namespace Mimp {

	Effects::Effects() : ImageOperation({"Window", "Effects"}, {Keys::KEY_E, true, false, false})
	{
		this->_win = tgui::ChildWindow::create();
		this->_win->setTitle("Effects");

		this->_win->setPosition(0, 0);

		this->_effects.push_back(std::make_shared<Light>());
	}

	void Effects::click(tgui::Gui &gui, CanvasWidget::Ptr image, tgui::ChildWindow::Ptr window, Editor &editor) const
	{
		tgui::Layout2d layout2D = {0, 0};

		this->_win->setTitle("Effects (" + window->getTitle().toAnsiString() + ")");
		for (auto &e : this->_effects) {
			auto panel = e->getPanel(image);
			this->_win->add(panel, e->getName());
			/*std::cout << "X:" << panel->getSizeLayout().x.getValue() << "|";
			std::cout << "Y:" << panel->getSizeLayout().y.getValue() << "|";
			std::cout << std::endl;*/
			layout2D.x = std::max(panel->getSizeLayout().x.getValue(), layout2D.x.getValue());
			layout2D.y = std::max(panel->getSizeLayout().y.getValue(), layout2D.y.getValue());
		}

		this->_win->setSize(layout2D);
		this->_win->connect("Closed", [this, &gui]{
			gui.remove(this->_win);
		});
		if (this->_win->getPosition().y <= 0.0) {
			this->_win->setPosition(0, tgui::bindBottom(gui.get<tgui::MenuBar>("main_bar")));
		}
		gui.add(this->_win, "effects");
	}
}