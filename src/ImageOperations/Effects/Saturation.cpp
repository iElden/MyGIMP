#include <TGUI/TGUI.hpp>
#include "Saturation.hpp"

namespace Mimp {
	Saturation::Saturation(std::shared_ptr<tgui::ChildWindow> window) : Effect(window)
	{
		auto redPreview = window->get<tgui::TextBox>("SaturationRedPreview");
		auto greenPreview = window->get<tgui::TextBox>("SaturationGreenPreview");
		auto bluePreview = window->get<tgui::TextBox>("SaturationBluePreview");

		auto redSlider = window->get<tgui::Slider>("SaturationRedSlider");
		auto greenSlider = window->get<tgui::Slider>("SaturationGreenSlider");
		auto blueSlider = window->get<tgui::Slider>("SaturationBlueSlider");

		auto previewCallback = [](tgui::TextBox::Ptr box, tgui::Slider::Ptr slider) {
			box->setText(std::to_string(slider->getValue()));
		};
		auto sliderCallback = [this](tgui::Slider::Ptr slider) {
			this->_image->takeFrameBufferSnapshot();

			auto buffer = this->_image->getSelectedLayer().buffer;
			auto size = buffer->getSize();
			auto value = slider->getValue();

			/*
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
			}*/
			slider->setValue(0);
		};

		redSlider->connect("ValueChanged", previewCallback, redPreview, redSlider);
		greenSlider->connect("ValueChanged", previewCallback, greenPreview, greenSlider);
		blueSlider->connect("ValueChanged", previewCallback, bluePreview, blueSlider);

		redSlider->connect("MouseLeft", sliderCallback, redSlider);
		greenSlider->connect("MouseLeft", sliderCallback, greenSlider);
		blueSlider->connect("MouseLeft", sliderCallback, blueSlider);
	}
}