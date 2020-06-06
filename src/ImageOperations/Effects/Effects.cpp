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
		auto lightSlider = this->_win->get<tgui::Slider>("Light");
		auto lightPreview = this->_win->get<tgui::TextBox>("LightPreview");

		lightSlider->connect("ValueChanged", [lightSlider, lightPreview] {
			lightPreview->setText(std::to_string(lightSlider->getValue()));

		});
		lightSlider->connect("MouseLeft", [lightSlider, image] {
			image->takeFrameBufferSnapshot();

			auto buffer = image->getSelectedLayer().buffer;
			auto size = buffer->getSize();
			auto value = lightSlider->getValue();

			for (unsigned int x = 0; x < size.x; x += 1) {
				for (unsigned int y = 0; y < size.y; y += 1) {
					auto newColor = buffer->getPixel(Vector2<int>(x, y));

					if (newColor.r + value <= 0) newColor.r = 0;
					else if (newColor.r + value >= 255) newColor.r = 255;
					else newColor.r += value;
					if (newColor.g + value <= 0) newColor.g = 0;
					else if (newColor.g + value >= 255) newColor.g = 255;
					else newColor.g += value;
					if (newColor.b + value <= 0) newColor.b = 0;
					else if (newColor.b + value >= 255) newColor.b = 255;
					else newColor.b += value;
					buffer->setPixel(Vector2<int>(x, y), newColor);
				}
			}
			lightSlider->setValue(0);
		});

		this->_win->connect("Closed", [this, &gui]{
			gui.remove(this->_win);
		});
		gui.add(this->_win, "effects");
	}
}