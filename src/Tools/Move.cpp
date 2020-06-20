//
// Created by Gegel85 on 24/05/2020.
//

#include <TGUI/TGUI.hpp>
#include "Move.hpp"

#include <iostream>

namespace Mimp {

	std::string moveTypeToString(MoveType mt)
	{
		std::string s;

		switch (mt) {
			case MOVE_LAYER:
				s = "move_layer";
				break;
			case MOVE_SELECTION:
				s = "move_selection";
				break;
			case MOVE_AREA:
				s = "move_area";
				break;
			default:
				s = "no_move";
		}

		return s;
	}

	MoveType stringToMoveType(const std::string &s)
	{
		MoveType mt;

		if (s == "move_layer") mt = MOVE_LAYER;
		else if (s == "move_selection") mt = MOVE_SELECTION;
		else if (s == "move_area") mt = MOVE_AREA;
		else mt = NO_MOVE;

		return mt;
	}
}

namespace Mimp {
	Move::Move() : Tool("Move Layer")
	{
		this->setKeyCombination({Keys::KEY_M, false, false, false});
	}

	void Move::onMouseDrag(Vector2<int> oldPos, Vector2<int> newPos, MouseClick, Image &image)
	{
		switch (this->_mt) {
			case MOVE_LAYER:
				this->_moveLayer(oldPos, newPos, image);
				break;
			case MOVE_SELECTION:
				this->_moveSelection(oldPos, newPos, image);
				break;
			case MOVE_AREA:
				//this->_moveArea(oldPos, newPos, image);
				break;
			default:
				return;
		}

	}

	void Move::onClick(Vector2<int> pos, MouseClick, Image &image)
	{
		switch (this->_mt) {
			case MOVE_LAYER:
				image.takeLayerSnapshot();
				break;
			case MOVE_SELECTION:
				image.takeSelectionSnapshot();
				break;
			case MOVE_AREA:
				image.takeSelectionSnapshot();
				image.takeFrameBufferSnapshot();
				break;
			default:
				break;
		}
	}

	tgui::ScrollablePanel::Ptr Move::getParametersPanel()
	{
		auto panel = tgui::ScrollablePanel::create();
		auto box = tgui::ComboBox::create();

		box->addItem("Move layer", moveTypeToString(MOVE_LAYER));
		box->addItem("Move selection", moveTypeToString(MOVE_SELECTION));
		box->addItem("Move area", moveTypeToString(MOVE_AREA));

		box->setSelectedItemById(moveTypeToString(this->_mt));
		box->onItemSelect.connect([this, box]() {
			this->_mt = stringToMoveType(box->getSelectedItemId());
		});

		panel->add(box);
		return panel;
	}

	void Move::_moveSelection(Vector2<int> oldPos, Vector2<int> newPos, Image &image)
	{
		auto diff = newPos - oldPos;
		auto points = image.selectedArea->getPoints();

		image.selectedArea->clear();
		for (auto p : points) {
			image.selectedArea->add(p + diff);
		}
	}

	void Move::_moveLayer(Vector2<int> oldPos, Vector2<int> newPos, Image &image)
	{
		image.getSelectedLayer().pos -= oldPos - newPos;
	}

	void Move::_moveArea(Vector2<int> oldPos, Vector2<int> newPos, Image &image)
	{
		auto diff = newPos - oldPos;
		auto points = image.selectedArea->getPoints();
		auto buffer = image.getSelectedLayer().buffer;
		auto layer = image.getSelectedLayer();

		image.selectedArea->clear();
		for (auto p : points) {
			auto pixel = buffer->getPixel(p);
			buffer->setPixel(p - layer.pos, Color::Transparent);
			buffer->setPixel(p + diff - layer.pos, pixel);
			image.selectedArea->add(p + diff);
		}
	}

}
