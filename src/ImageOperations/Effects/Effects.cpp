#include "Effects.hpp"

#include <iostream>

namespace Mimp {

	Effects::Effects() : ImageOperation({"Window", "Effects"}, {Keys::KEY_E, true, false, false})
	{
		this->_win = tgui::ChildWindow::create();
		this->_win->loadWidgetsFromFile("widgets/effects.gui");

		this->_win->setTitle("Effects");
		this->_win->setSize("Label1.x + Label1.w + Light.x + Light.w + LightPreview.x ° LightPreview.w + 10", "Label1.y + Label1.h + 10");
	}

	void Effects::click(tgui::Gui &gui, CanvasWidget::Ptr image, tgui::ChildWindow::Ptr window, Editor &editor) const
	{
		//! @todo Image Manipulation
		image->takeFrameBufferSnapshot();

		auto lightSlider = this->_win->get<tgui::Slider>("Light");
		auto lightPreview = this->_win->get<tgui::TextBox>("LightPreview");

		lightSlider->connect("ValueChanged", [lightSlider, lightPreview] {
			lightPreview->setText(std::to_string(lightSlider->getValue()));

		});
		lightSlider->connect("MouseLeft", [lightSlider, image] {
			auto buffer = image->getSelectedLayer().buffer;
			auto size = buffer->getSize();

			for (unsigned int x = 0; x < size.x; x += 1) {
				for (unsigned int y = 0; y < size.y; y += 1) {
					auto newColor = buffer->getPixel(Vector2<int>(x, y));

					newColor.a = lightSlider->getValue();
					buffer->setPixel(Vector2<int>(x, y), newColor);
				}
			}
		});

		this->_win->connect("Closed", [this, &gui]{
			gui.remove(this->_win);
		});
		gui.add(this->_win, "effects");
	}
}