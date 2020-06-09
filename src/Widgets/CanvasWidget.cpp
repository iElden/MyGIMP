//
// Created by Gegel85 on 06/04/2020.
//

#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/RenderTexture.hpp>
#include "CanvasWidget.hpp"

namespace Mimp
{
	CanvasWidget::CanvasWidget(const ToolBox &box, const std::string &path):
		CanvasWidget(box, Vector2<unsigned>{0, 0}, LayerManager(path))
	{
		this->_size = this->_layers.getSize();
		this->m_size = {this->_size.x, this->_size.y};
		this->selectedArea.setSize(this->_size);
	}

	CanvasWidget::CanvasWidget(const ToolBox &box, Vector2<unsigned int> size, const LayerManager &layers):
		Image(size, layers),
		_box(box)
	{
		this->m_size = {size.x, size.y};
		this->m_type = "Canvas";
		this->_drawBuffer.create(size.x, size.y);
		this->_makeCallbacks();
	}

	CanvasWidget::CanvasWidget(const ToolBox &box, Vector2<unsigned int> size):
		Image(size, LayerManager(size, 1, Color::White)),
		_box(box)
	{
		this->m_size = {size.x, size.y};
		this->m_type = "Canvas";
		this->_drawBuffer.create(size.x, size.y);
		this->_makeCallbacks();
	}

	void CanvasWidget::mouseMoved(tgui::Vector2f pos)
	{
		Vector2<int> realPos;

		this->_edited |= this->m_mouseDown || this->_rightMouseDown;
		realPos.x = (pos.x - this->getPosition().x) / this->_zoom;
		realPos.y = (pos.y - this->getPosition().y) / this->_zoom;
		if (this->m_mouseDown)
			this->_box.getSelectedTool()->onMouseDrag(this->_mousePos, realPos, MIMP_LEFT_CLICK, *this);
		if (this->_rightMouseDown)
			this->_box.getSelectedTool()->onMouseDrag(this->_mousePos, realPos, MIMP_RIGHT_CLICK, *this);
		this->_mousePos = realPos;
	}

	tgui::Widget::Ptr CanvasWidget::clone() const
	{
		return CanvasWidget::Ptr(new CanvasWidget(this->_box, this->_size, this->_layers));
	}

	void CanvasWidget::draw(sf::RenderTarget &target, sf::RenderStates states) const
	{
		sf::RectangleShape rect;
		sf::Sprite sprite;
		auto size = this->_size;
		FrameBuffer buffer{size};
		auto color = Color{this->_colorCounter, this->_colorCounter, this->_colorCounter, 120};
		auto realSize = size * this->_zoom;

		this->_colorCounter += (this->_counterUp * 2 - 1) * 20;
		this->_counterUp = (this->_counterUp && this->_colorCounter < 240) || !this->_colorCounter;
		if (this->selectedArea.isAnAreaSelected())
			for (auto &pt : this->selectedArea.getPoints())
				buffer.drawPixel(pt, color, SET);

		states.transform.translate(getPosition());

		if (this->m_parent) {
			auto parentSize = this->m_parent->getSize();

			parentSize.x -= this->getPosition().x;
			parentSize.y -= this->getPosition().y;
			realSize.x = std::min(parentSize.x, realSize.x);
			realSize.y = std::min(parentSize.y, realSize.y);
		}

		for (auto &layer : this->_layers) {
			if (!layer->visible)
				continue;

			auto s = layer->getSize();

			this->_drawBuffer.create(s.x, s.y);
			this->_drawBuffer.update(layer->buffer->getDrawBuffer(), s.x, s.y, 0, 0);
			sprite.setTexture(this->_drawBuffer, true);
			sprite.setPosition((layer->pos.x + size.x / 2.f) * this->_zoom, (layer->pos.y + size.y / 2.f) * this->_zoom);
			sprite.setScale(this->_zoom, this->_zoom);
			sprite.setOrigin(size.x / 2.f, size.y / 2.f);
			sprite.setRotation(layer->rotation);
			target.draw(sprite, states);
		}
		this->_drawBuffer.create(size.x, size.y);
		this->_drawBuffer.update(buffer.getDrawBuffer(), size.x, size.y, 0, 0);
		sprite.setTexture(this->_drawBuffer, true);
		sprite.setPosition(0, 0);
		sprite.setOrigin(0, 0);
		sprite.setScale(this->_zoom, this->_zoom);
		target.draw(sprite, states);

		//! Basic grid implementation.
		if (this->_drawGrid) {
			auto realGridSize = this->_gridSize * this->_zoom;
			sf::RectangleShape rs;
			rs.setSize({realGridSize, realGridSize});
			rs.setOutlineThickness(1.0);
			rs.setOutlineColor(sf::Color::Black);
			rs.setFillColor(sf::Color::Transparent);

			for (int i = 0; i * realGridSize <= realSize.x; i += 1) {
				for (int j = 0; j * realGridSize <= realSize.y; j += 1) {
					rs.setPosition(i * rs.getSize().x, j * rs.getSize().y);
					target.draw(rs, states);
				}
			}
		}

		//! @todo Basic symmetry implementation. Optimization with sf::Vertex ?
		if (this->_symmetry.x) {
			sf::RectangleShape rs;
			rs.setSize({this->_size.x * this->_zoom, 1});
			rs.setRotation(0);
			rs.setPosition(0, this->_axis.y * this->_zoom);
			rs.setFillColor(sf::Color::Cyan);
			target.draw(rs, states);
		}
		if (this->_symmetry.y) {
			sf::RectangleShape rs;
			rs.setSize({this->_size.y * this->_zoom, 1});
			rs.setRotation(90);
			rs.setPosition(this->_axis.x * this->_zoom, 0);
			rs.setFillColor(sf::Color::Cyan);
			target.draw(rs, states);
		}
	}

	CanvasWidget::Ptr CanvasWidget::create(const ToolBox &box, Vector2<unsigned int> size)
	{
		return std::make_shared<CanvasWidget>(box, size);
	}

	CanvasWidget::Ptr CanvasWidget::create(const ToolBox &box, const std::string &path)
	{
		return std::make_shared<CanvasWidget>(box, path);
	}

	void CanvasWidget::importImageFromFile(const std::string &path)
	{
		this->_layers.importImageFromFile(path);
		this->_size = {
			this->_layers.getSize().x,
			this->_layers.getSize().y
		};
		this->m_size = {
			this->_size.x,
			this->_size.y
		};
		this->_drawBuffer.create(this->_size.x, this->_size.y);
		this->selectedArea.setSize(this->_size);
	}

	void CanvasWidget::importImageFromMemory(const std::string &path)
	{
		this->_layers.importImageFromMemory(path);
		this->_size = {
			this->_layers.getSize().x,
			this->_layers.getSize().y
		};
		this->m_size = {
			this->_size.x,
			this->_size.y
		};
		this->_drawBuffer.create(this->_size.x, this->_size.y);
		this->selectedArea.setSize(this->_size);
	}

	void CanvasWidget::setZoomLevel(float zoom)
	{
		this->_zoom = zoom;
		this->setSize({
			this->_size.x * zoom,
			this->_size.y * zoom,
		});
	}

	float CanvasWidget::getZoomLevel() const
	{
		return this->_zoom;
	}

	bool CanvasWidget::isEdited() const
	{
		return this->_edited;
	}

	void CanvasWidget::setEdited(bool edited)
	{
		this->_edited = edited;
	}

	void CanvasWidget::_makeCallbacks()
	{
		this->onMousePress.connect([this](tgui::Vector2f pos){
			Vector2<int> realPos;

			realPos.x = pos.x / this->_zoom;
			realPos.y = pos.y / this->_zoom;
			this->_edited = true;
			this->_box.getSelectedTool()->onClick(realPos, MIMP_LEFT_CLICK, *this);
		});
		this->onMouseRelease.connect([this](tgui::Vector2f pos){
			Vector2<int> realPos;

			realPos.x = pos.x / this->_zoom;
			realPos.y = pos.y / this->_zoom;
			this->_box.getSelectedTool()->onMouseRelease(realPos, MIMP_LEFT_CLICK, *this);
		});
		this->onRightMousePress.connect([this](tgui::Vector2f pos){
			Vector2<int> realPos;

			realPos.x = pos.x / this->_zoom;
			realPos.y = pos.y / this->_zoom;
			this->_rightMouseDown = true;
			this->_edited = true;
			this->_box.getSelectedTool()->onClick(realPos, MIMP_RIGHT_CLICK, *this);
		});
		this->onRightMouseRelease.connect([this](tgui::Vector2f pos){
			Vector2<int> realPos;

			realPos.x = pos.x / this->_zoom;
			realPos.y = pos.y / this->_zoom;
			this->_rightMouseDown = false;
			this->_box.getSelectedTool()->onMouseRelease(realPos, MIMP_RIGHT_CLICK, *this);
		});
	}

	void CanvasWidget::increaseGrid()
	{
		if (this->_gridSize < 100)
			this->_gridSize += 10;
	}

	void CanvasWidget::decreaseGrid()
	{
		if (this->_gridSize > 10)
			this->_gridSize -= 10;
	}

	void CanvasWidget::setSymmetry(Vector2<bool> symmetry)
	{
		this->_layers.getSelectedLayer().buffer->setSymmetry(symmetry);
		this->_symmetry = symmetry;
	}

	void CanvasWidget::setSymmetryAxis(Vector2<int> axis)
	{
		this->_layers.getSelectedLayer().buffer->setSymmetryAxis(axis);
		this->_axis = axis;
	}
}