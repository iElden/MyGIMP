#include "Light.hpp"

#include <iostream>

namespace Mimp {

	Light::Light() : Effect("light", "widgets/effects_cfg/light.gui")
	{
		auto lightSlider = this->_panel->get<tgui::Slider>("Light");
		auto lightPreview = this->_panel->get<tgui::TextBox>("LightPreview");

		lightSlider->connect("ValueChanged", [lightSlider, lightPreview] {
			lightPreview->setText(std::to_string(lightSlider->getValue()));
		});

		lightSlider->connect("MouseLeft", [lightSlider, this] {
			this->_image->takeFrameBufferSnapshot();

			auto buffer = this->_image->getSelectedLayer().buffer;
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
	}
}