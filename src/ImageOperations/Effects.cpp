#include "Effects.hpp"
#include "Effects/Light.hpp"
#include "Effects/Saturation.hpp"
#include "Effects/Symmetry.hpp"

namespace Mimp {

	Effects::Effects() : ImageOperation({"Window", "Effects"}, {Keys::KEY_E, true, false, false})
	{
		this->_win = tgui::ChildWindow::create();
		this->_win->setTitle("Effects");
		this->_win->loadWidgetsFromFile("widgets/effects.gui");
		this->_win->setPosition(0, 0);

		this->_effects.push_back(std::make_shared<Light>(this->_win));
		this->_effects.push_back(std::make_shared<Saturation>(this->_win));
		this->_effects.push_back(std::make_shared<Symmetry>(this->_win));
	}

	void Effects::click(tgui::Gui &gui, CanvasWidget::Ptr image, tgui::ChildWindow::Ptr window, Editor &editor) const
	{
		this->_win->setTitle("Effects (" + window->getTitle().toAnsiString() + "/" + image->getSelectedLayer().name + ")");
		for (auto &e : this->_effects) {
			e->setImage(image);
		}
		this->_win->connect("Closed", [this, &gui]{
			gui.remove(this->_win);
		});
		if (this->_win->getPosition().y <= 0.0) {
			this->_win->setPosition(0, tgui::bindBottom(gui.get<tgui::MenuBar>("main_bar")));
		}
		gui.add(this->_win, "effects");
	}
}