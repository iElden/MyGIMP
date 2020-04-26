//
// Created by Gegel85 on 25/04/2020.
//

#include <TGUI/TGUI.hpp>
#include "FillSelectionOperation.hpp"

namespace Mimp
{
	FillSelectionOperation::FillSelectionOperation() :
		ImageOperation({"Selection", "Fill area"})
	{
	}

	void FillSelectionOperation::click(tgui::Gui &gui, Image &image) const
	{
		auto panel = tgui::Panel::create({"100%", "100%"});

		panel->getRenderer()->setBackgroundColor({0, 0, 0, 175});
		gui.add(panel);

		auto window = tgui::ChildWindow::create();
		window->setSize(271, 182);
		window->setPosition("(&.w - w) / 2", "(&.h - h) / 2");
		gui.add(window);

		window->setFocused(true);

		const bool tabUsageEnabled = gui.isTabKeyUsageEnabled();
		auto closeWindow = [&gui, window, panel, tabUsageEnabled]{
			gui.remove(window);
			gui.remove(panel);
			gui.setTabKeyUsageEnabled(tabUsageEnabled);
		};

		panel->connect("Clicked", closeWindow);
		window->connect({"Closed", "EscapeKeyPressed"}, closeWindow);
		window->loadWidgetsFromFile("widgets/color.gui");

		auto red = window->get<tgui::Slider>("Red");
		auto green = window->get<tgui::Slider>("Green");
		auto blue = window->get<tgui::Slider>("Blue");
		auto preview = window->get<tgui::TextBox>("Preview");
		auto sliderCallback = [red, green, blue, preview]{
			tgui::Color bufferColor{
				static_cast<unsigned char>(red->getValue()),
				static_cast<unsigned char>(green->getValue()),
				static_cast<unsigned char>(blue->getValue())
			};

			preview->getRenderer()->setBackgroundColor(bufferColor);
		};

		red->connect("ValueChanged", sliderCallback);
		green->connect("ValueChanged", sliderCallback);
		blue->connect("ValueChanged", sliderCallback);
		preview->getRenderer()->setBackgroundColor({0, 0, 0, 255});
		window->get<tgui::Button>("Cancel")->connect("Clicked", [window]{
			window->close();
		});
		window->get<tgui::Button>("OK")->connect("Clicked", [&image, red, green, blue, window]{
			Color bufferColor{
				static_cast<unsigned char>(red->getValue()),
				static_cast<unsigned char>(green->getValue()),
				static_cast<unsigned char>(blue->getValue())
			};

			FillSelectionOperation::_fill(image.getSelectedLayer(), image.selectedArea, bufferColor);
			window->close();
		});
	}

	void FillSelectionOperation::_fill(Layer &layer, const SelectedArea &area, const Color &color)
	{
		if (area.isAnAreaSelected())
			for (const auto &pt : area)
				layer.buffer.setPixel(pt, color);
	}
}