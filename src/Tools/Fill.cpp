/*
** EPITECH PROJECT, 2020
** MyGimp
** File description:
** Fill.cpp
*/

#include "Fill.hpp"
#include <TGUI/TGUI.hpp>

Mimp::Fill::Fill(Mimp::ToolBox &toolBox):
		Tool("Fill color"),
		_box(toolBox)
{
	this->setKeyCombination({Keys::KEY_F, false, false, false});
}

void Mimp::Fill::onClick(Mimp::Vector2<int> pos, Mimp::MouseClick click, Mimp::Image &image)
{
	if (image.getSelectedLayer().isLocked())
		return;

	image.takeFrameBufferSnapshot();
	auto &layer = image.getSelectedLayer();

	this->apply((pos - layer.pos).rotate(-layer.rotation, layer.getSize() / 2).to<int>(), layer, click);
}

void Mimp::Fill::onMouseDrag(Mimp::Vector2<int>, Mimp::Vector2<int> newPos, Mimp::MouseClick click, Mimp::Image &image)
{
	auto &layer = image.getSelectedLayer();

	this->apply((newPos - layer.pos).rotate(-layer.rotation, layer.getSize() / 2).to<int>(), layer, click);
}

void Mimp::Fill::apply(Mimp::Vector2<int> pos, Mimp::Layer &layer, MouseClick &click)
{
	if (layer.buffer->posIsOutOfBound(pos))
		return;
	auto target_color = layer.buffer->getPixel(pos);
	auto fill_color = this->_box.getSelectedColor(click);
	if (fill_color.diff(target_color, this->_alphaInTolerance) <= this->_tolerance)
		return;
	this->_spread_color(pos, layer, target_color, fill_color);
}

void Mimp::Fill::_spread_color(Vector2<int> pos, Layer &layer, Color target_color, Color fill_color)
{
	std::vector<Vector2<int>> spread_pos = {{-1,0}, {0,-1}, {1,0}, {0,1}};
	std::vector<Vector2<int>> points = {pos};
	std::vector<Vector2<int>> new_points;

	layer.buffer->setPixel(pos, fill_color);
	while (!points.empty()) {
		new_points.clear();
		for (auto pt : points)
			for (auto sp : spread_pos) {
				auto new_pos = pt + sp;
				if (!layer.buffer->posIsOutOfBound(new_pos) && layer.buffer->getPixel(new_pos).diff(target_color, this->_alphaInTolerance) <= this->_tolerance) {
					layer.buffer->setPixel(new_pos, fill_color);
					new_points.push_back(new_pos);
				}
			}
		points = new_points;
	}
}

tgui::ScrollablePanel::Ptr Mimp::Fill::getParametersPanel()
{
	auto panel = tgui::ScrollablePanel::create();

	panel->loadWidgetsFromFile("widgets/tools_cfg/fill_cfg.gui");

	auto toleranceSlider = panel->get<tgui::Slider>("Tolerance");
	auto alpha = panel->get<tgui::CheckBox>("Alpha");
	auto tolerancePreview = panel->get<tgui::TextBox>("TolerancePreview");

	tolerancePreview->setText(std::to_string(this->_tolerance));
	toleranceSlider->setValue(this->_tolerance);
	alpha->setChecked(this->_alphaInTolerance);

	toleranceSlider->connect("ValueChanged", [tolerancePreview, this, toleranceSlider]{
		this->_tolerance = toleranceSlider->getValue();
		tolerancePreview->setText(std::to_string(this->_tolerance));
	});
	alpha->connect("Changed", [alpha, this]{
		this->_alphaInTolerance = alpha->isChecked();
	});
	return panel;
}