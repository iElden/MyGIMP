//
// Created by Gegel85 on 14/05/2020.
//

#include <SFML/Graphics/Sprite.hpp>
#include "LayerWidget.hpp"

namespace Mimp
{
	LayerWidget::LayerWidget(const std::shared_ptr<Layer> &layer, Vector2<tgui::Layout> size) :
		_layer(layer)
	{
		this->m_size = {size.x, size.y};
	}

	LayerWidget::Ptr LayerWidget::create(const std::shared_ptr<Layer> &layer, Vector2<tgui::Layout> size)
	{
		return std::make_shared<LayerWidget>(layer, size);
	}

	bool LayerWidget::mouseOnWidget(tgui::Vector2f pos) const
	{
		return !this->_mouseDisabled && ClickableWidget::mouseOnWidget(pos);
	}

	void LayerWidget::draw(sf::RenderTarget &target, sf::RenderStates states) const
	{
		auto size = this->_layer->getSize();
		sf::Sprite sprite;
		float factorX = (this->m_size.x / size.x).getValue();
		float factorY = (this->m_size.y / size.y).getValue();
		float factor = std::min(factorX, factorY);
		auto pos = getPosition();

		pos.x += (factorX / factor - 1) * this->m_size.x.getValue() / (2.f * size.y / size.x);
		pos.y += (factorY / factor - 1) * this->m_size.y.getValue() / (2.f * size.x / size.y);
		this->_drawBuffer.create(size.x, size.y);
		this->_drawBuffer.update(this->_layer->buffer->getDrawBuffer(), size.x, size.y, 0, 0);
		states.transform.translate(pos);
		sprite.setTexture(this->_drawBuffer, true);
		sprite.setOrigin(size.x / 2, size.y / 2);
		sprite.setPosition(factor * size.x / 2, factor * size.y / 2);
		sprite.setScale({
			factor,
			factor
		});
		sprite.setRotation(this->_layer->rotation);
		target.draw(sprite, states);
	}

	tgui::Widget::Ptr LayerWidget::clone() const
	{
		return std::make_shared<LayerWidget>(this->_layer, Vector2<tgui::Layout>{this->m_size.x, this->m_size.y});
	}

	void LayerWidget::ignoreMouseEvent(bool ignored)
	{
		this->_mouseDisabled = ignored;
	}
}