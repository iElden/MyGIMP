#include <TGUI/TGUI.hpp>
#include "Finger.hpp"
#include "../Utils.hpp"

namespace Mimp
{
	Finger::Finger(ToolBox &box):
		SelectionTool("Finger", box)
	{
		this->setKeyCombination({Keys::KEY_F, false, true, false});
	}

	void Finger::onMouseDrag(Vector2<float>, Vector2<float> newPos, MouseClick, Image &image)
	{
		this->_apply(newPos.to<int>(), image);
	}

	void Finger::onClick(Vector2<float> pos, MouseClick, Image &image)
	{
		image.takeFrameBufferSnapshot();
		this->_apply(pos.to<int>(), image);
	}

	tgui::ScrollablePanel::Ptr Finger::getParametersPanel()
	{
		auto panel = tgui::ScrollablePanel::create();

		panel->loadWidgetsFromFile("widgets/tools_cfg/finger_cfg.gui");

		auto radiusSlider = panel->get<tgui::Slider>("Radius");
		auto radiusPreview = panel->get<tgui::TextBox>("Preview");

		radiusPreview->setText(std::to_string(this->_radius));
		radiusSlider->setValue(this->_radius);
		radiusSlider->connect("ValueChanged", [radiusPreview, this, radiusSlider]{
			this->_radius = radiusSlider->getValue();
			radiusPreview->setText(std::to_string(this->_radius));
		});
		return panel;
	}

	void Finger::_apply(Vector2<int> pos, Image &image)
	{
		int xmin = pos.x - this->_radius;
		int xmax = pos.x + this->_radius;
		int ymin = pos.y - this->_radius;
		int ymax = pos.y + this->_radius;

		auto &buffer = image.getSelectedLayer().buffer;

		std::vector<std::pair<Vector2<int>, Color>> pixels;

		for (int i = xmin; i < xmax; i += 1) {
			for (int j = ymin; j < ymax; j += 1) {
				if (Utils::point_in_ellipse(i - pos.x, j - pos.y, this->_radius, this->_radius)
				  && !Utils::isOutOfBound({i, j}, image.getImageSize())
				  && buffer->getPixel({i, j}).a
				  ) {
					pixels.emplace_back(Vector2{i, j}, buffer->getPixel({i , j}));
				}
			}
		}

		if (pixels.empty())
			return;

		int r = 0;
		int g = 0;
		int b = 0;
		int a = 0;

		for (auto &px : pixels) {
			r += px.second.r;
			g += px.second.g;
			b += px.second.b;
			a += px.second.b;
		}
		r /= pixels.size();
		g /= pixels.size();
		b /= pixels.size();
		a /= pixels.size();

		r = std::max(std::min(r, 255), 0);
		g = std::max(std::min(g, 255), 0);
		b = std::max(std::min(b, 255), 0);
		a = std::max(std::min(a, 255), 0);

		for (auto &px: pixels)
			buffer->drawPixel(px.first, Color(r, g, b, a));
	}
}