/*
** EPITECH PROJECT, 2020
** MyGimp
** File description:
** Eraser.cpp
*/

#include "Eraser.hpp"
#include "../Utils.hpp"
#include <TGUI/TGUI.hpp>

namespace Mimp
{
	Eraser::Eraser(ToolBox &box) :
			Tool("Eraser"),
			_box(box)
	{
	}

	void Eraser::onMouseDrag(Vector2<int> oldPos, Vector2<int> newPos, MouseClick, Image &image)
	{
		if (image.getSelectedLayer().isLocked())
			return;

		auto &layer = image.getSelectedLayer();

		layer.buffer.drawLine(oldPos - layer.pos, newPos - layer.pos, Color::Transparent, this->_radius, this->_shape, DrawStrategy::SET);
	}

	void Eraser::onClick(Vector2<int> pos, MouseClick, Image &image)
	{
		if (image.getSelectedLayer().isLocked())
			return;

		image.takeFrameBufferSnapshot();
		auto &layer = image.getSelectedLayer();

		layer.buffer.drawAt(pos - layer.pos, Color::Transparent, this->_radius, this->_shape, DrawStrategy::SET);
	}

	tgui::ScrollablePanel::Ptr Eraser::getParametersPanel()
	{
		auto panel = tgui::ScrollablePanel::create();

		panel->loadWidgetsFromFile("widgets/tools_cfg/pencil_cfg.gui");

		auto radiusSlider = panel->get<tgui::Slider>("Radius");
		auto shapeBox = panel->get<tgui::ComboBox>("Shape");
		auto radiusPreview = panel->get<tgui::TextBox>("RadiusPreview");

		radiusPreview->setText(std::to_string(this->_radius));
		radiusSlider->setValue(this->_radius);
		shapeBox->removeAllItems();
		for (int i = 0; i < NB_OF_SHAPES; i++)
			shapeBox->addItem(Utils::DrawShapeToString(static_cast<DrawShape>(i)));
		shapeBox->setSelectedItemByIndex(CIRCLE);

		radiusSlider->connect("ValueChanged", [radiusPreview, this, radiusSlider]{
			this->_radius = radiusSlider->getValue();
			radiusPreview->setText(std::to_string(this->_radius));
		});
		shapeBox->connect("ItemSelected", [this, shapeBox]{
			this->_shape = static_cast<DrawShape>(shapeBox->getSelectedItemIndex());
		});
		return panel;
	}
}