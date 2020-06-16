/*
** EPITECH PROJECT, 2020
** MyGimp
** File description:
** SelectByColorTool.cpp
*/
#include "SelectByColorTool.hpp"
#include <TGUI/TGUI.hpp>

Mimp::SelectByColorTool::SelectByColorTool(ToolBox &toolBox):
	SelectionTool("SelectByColor", toolBox)
{
	this->setKeyCombination({Keys::KEY_U, true, false, false});
}

void Mimp::SelectByColorTool::onClick(Mimp::Vector2<int> pos, Mimp::MouseClick click, Mimp::Image &image)
{
	auto &layer = image.getSelectedLayer();

	image.takeSelectionSnapshot();
	image.selectedArea->clear();
	this->_updateSelectedArea(image, layer.buffer->getPixel((pos - layer.pos).rotate(-layer.rotation, layer.getSize() / 2).to<int>()));

	if (click == MouseClick::MIMP_RIGHT_CLICK)
		image.selectedArea->invert();
}

void Mimp::SelectByColorTool::_updateSelectedArea(Image &image, const Color &target_color)
{
	auto &layer = image.getSelectedLayer();
	unsigned max_x = layer.getSize().x;
	unsigned max_y = layer.getSize().y;

	for (unsigned j = 0; j < max_y; j++)
		for (unsigned i = 0; i < max_x; i++) {
			if (layer.buffer->operator[](j * max_x + i).diff(target_color, this->_alpha_in_tolerance) <= this->_tolerance) {
				auto vec = Vector2<unsigned>{i, j}.rotate(layer.rotation, layer.getSize() / 2);

				image.selectedArea->add(vec.to<int>() + layer.pos);
				image.selectedArea->add(Vector2<float>(vec.x, std::ceil(vec.y)).to<int>() + layer.pos);
				image.selectedArea->add(Vector2<float>(std::ceil(vec.x), vec.y).to<int>() + layer.pos);
				image.selectedArea->add(Vector2<float>(std::ceil(vec.x), std::ceil(vec.y)).to<int>() + layer.pos);
			}
		}
}

tgui::ScrollablePanel::Ptr Mimp::SelectByColorTool::getParametersPanel()
{
	auto panel = tgui::ScrollablePanel::create();

	panel->loadWidgetsFromFile("widgets/tools_cfg/fill_cfg.gui");

	auto toleranceSlider = panel->get<tgui::Slider>("Tolerance");
	auto alpha = panel->get<tgui::CheckBox>("Alpha");
	auto tolerancePreview = panel->get<tgui::TextBox>("TolerancePreview");

	tolerancePreview->setText(std::to_string(this->_tolerance));
	toleranceSlider->setValue(this->_tolerance);
	alpha->setChecked(true);

	toleranceSlider->connect("ValueChanged", [tolerancePreview, this, toleranceSlider]{
		this->_tolerance = toleranceSlider->getValue();
		tolerancePreview->setText(std::to_string(this->_tolerance));
	});
	return panel;
}