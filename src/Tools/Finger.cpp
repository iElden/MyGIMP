#include <TGUI/TGUI.hpp>
#include "Finger.hpp"

namespace Mimp {

	Finger::Finger(Mimp::ToolBox &box) : SelectionTool("Finger", box), _est(box)
	{
		this->setKeyCombination({Keys::KEY_F, false, true, false});
	}

	void Finger::onMouseDrag(Vector2<int>, Vector2<int> newPos, MouseClick, Image &image)
	{
		this->_apply(newPos, image);
	}

	void Finger::onClick(Vector2<int> pos, MouseClick, Image &image)
	{
		image.takeFrameBufferSnapshot();
		this->_apply(pos, image);
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

		std::vector<Color> pixels;

		for (int i = xmin; i < xmax; i += 1) {
			for (int j = ymin; j < ymax; j += 1) {
				if (this->_est.point_in_ellipse(i - pos.x, j - pos.y, this->_radius, this->_radius)) {
					pixels.push_back(buffer->getPixel({i , j}));
				}
			}
		}

		if (pixels.empty())
			return;

		int r = 0;
		int g = 0;
		int b = 0;

		for (auto &px : pixels) {
			r += px.r;
			g += px.g;
			b += px.b;
		}
		r /= pixels.size();
		g /= pixels.size();
		b /= pixels.size();

		if (r > 255) r = 255;
		if (r < 0) r = 0;
		if (g > 255) g = 255;
		if (g < 0) g = 0;
		if (b > 255) b = 255;
		if (b < 0) b = 0;

		for (int i = xmin; i < xmax; i += 1) {
			for (int j = ymin; j < ymax; j += 1) {
				if (this->_est.point_in_ellipse(i - pos.x, j - pos.y, this->_radius, this->_radius)) {
					buffer->drawPixel({i, j}, Color(r, g, b, buffer->getPixel({i, j}).a));
				}
			}
		}
	}
}