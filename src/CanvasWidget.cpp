//
// Created by Gegel85 on 06/04/2020.
//

#include <SFML/Graphics/Sprite.hpp>
#include <iostream>
#include <SFML/Graphics/RectangleShape.hpp>
#include "CanvasWidget.hpp"

namespace Mimp
{
	CanvasWidget::CanvasWidget(const ToolBox &box, const std::string &path):
		CanvasWidget(box, Vector2<unsigned>{0, 0}, LayerManager(path))
	{
		this->_size = this->_layers.getSize();
		this->m_size = {this->_size.x, this->_size.y};
	}

	CanvasWidget::CanvasWidget(const ToolBox &box, Vector2<unsigned int> size, const LayerManager &layers):
		Image(size, layers),
		_box(box)
	{
		this->m_size = {size.x, size.y};
		this->m_type = "Canvas";

		this->onMousePress.connect([this](tgui::Vector2f pos){
			Vector2<int> realPos;

			realPos.x = pos.x;
			realPos.y = pos.y;
			this->_box.getSelectedTool()->onClick(realPos, MIMP_LEFT_CLICK, *this);
		});
		this->onMouseRelease.connect([this](tgui::Vector2f pos){
			Vector2<int> realPos;

			realPos.x = pos.x;
			realPos.y = pos.y;
			this->_box.getSelectedTool()->onMouseRelease(realPos, MIMP_LEFT_CLICK, *this);
		});
		this->onRightMousePress.connect([this](tgui::Vector2f pos){
			Vector2<int> realPos;

			realPos.x = pos.x;
			realPos.y = pos.y;
			this->_rightMouseDown = true;
			this->_box.getSelectedTool()->onClick(realPos, MIMP_RIGHT_CLICK, *this);
		});
		this->onRightMouseRelease.connect([this](tgui::Vector2f pos){
			Vector2<int> realPos;

			realPos.x = pos.x;
			realPos.y = pos.y;
			this->_rightMouseDown = false;
			this->_box.getSelectedTool()->onMouseRelease(realPos, MIMP_RIGHT_CLICK, *this);
		});
		this->_renderThread = std::thread([this]{
			/*while (!this->_destroyed) {
				this->_updateInternalBuffer();
				std::this_thread::sleep_for(std::chrono::milliseconds(10));
			}*/
		});
		this->_drawBuffer.create(size.x, size.y);
	}

	CanvasWidget::CanvasWidget(const ToolBox &box, Vector2<unsigned int> size):
		Image(size, LayerManager(size, 1, Color::White)),
		_box(box)
	{
		this->m_size = {size.x, size.y};
		this->m_type = "Canvas";

		this->onMousePress.connect([this](tgui::Vector2f pos){
			Vector2<int> realPos;

			realPos.x = pos.x;
			realPos.y = pos.y;
			this->_box.getSelectedTool()->onClick(realPos, MIMP_LEFT_CLICK, *this);
		});
		this->onMouseRelease.connect([this](tgui::Vector2f pos){
			Vector2<int> realPos;

			realPos.x = pos.x;
			realPos.y = pos.y;
			this->_box.getSelectedTool()->onMouseRelease(realPos, MIMP_LEFT_CLICK, *this);
		});
		this->onRightMousePress.connect([this](tgui::Vector2f pos){
			Vector2<int> realPos;

			realPos.x = pos.x;
			realPos.y = pos.y;
			this->_rightMouseDown = true;
			this->_box.getSelectedTool()->onClick(realPos, MIMP_RIGHT_CLICK, *this);
		});
		this->onRightMouseRelease.connect([this](tgui::Vector2f pos){
			Vector2<int> realPos;

			realPos.x = pos.x;
			realPos.y = pos.y;
			this->_rightMouseDown = false;
			this->_box.getSelectedTool()->onMouseRelease(realPos, MIMP_RIGHT_CLICK, *this);
		});
		this->_drawBuffer.create(size.x, size.y);
		this->_renderThread = std::thread([this]{
			/*while (!this->_destroyed) {
				this->_updateInternalBuffer();
				std::this_thread::sleep_for(std::chrono::milliseconds(10));
			}*/
		});
	}

	void CanvasWidget::_updateInternalBuffer()
	{
		FrameBuffer buffer(
			{
				static_cast<unsigned>(this->getSize().x),
				static_cast<unsigned>(this->getSize().y)
			},
			Color::Transparent
		);
		auto size = buffer.getSize();

		this->_layers.render(buffer);

		auto pixelArray = new sf::Color[size.x * size.y];
		auto color = Color{this->_colorCounter, this->_colorCounter, this->_colorCounter, 120};

		this->_colorCounter += (this->_counterUp * 2 - 1) * 20;
		this->_counterUp = (this->_counterUp && this->_colorCounter < 240) || !this->_colorCounter;
		if (this->selectedArea.isAnAreaSelected())
			for (auto &pt : this->selectedArea.getPoints())
				buffer.drawPixel(pt, color);

		for (unsigned x = 0; x < size.x; x++)
			for (unsigned y = 0; y < size.y; y++)
				pixelArray[x + y * size.x] = buffer.getPixel({static_cast<int>(x), static_cast<int>(y)});
		this->_drawBuffer.create(size.x, size.y);
		this->_drawBuffer.update(reinterpret_cast<const sf::Uint8 *>(pixelArray), buffer.getSize().x, buffer.getSize().y, 0, 0);
		delete[] pixelArray;
	}

	void CanvasWidget::mouseMoved(tgui::Vector2f pos)
	{
		Vector2<int> realPos;

		realPos.x = pos.x - this->getPosition().x;
		realPos.y = pos.y - this->getPosition().y;
		if (this->m_mouseDown)
			this->_box.getSelectedTool()->onMouseDrag(this->_mousePos, realPos, MIMP_LEFT_CLICK, *this);
		if (this->_rightMouseDown)
			this->_box.getSelectedTool()->onMouseDrag(this->_mousePos, realPos, MIMP_RIGHT_CLICK, *this);
		this->_mousePos = realPos;
	}

	tgui::Widget::Ptr CanvasWidget::clone() const
	{
		return std::shared_ptr<CanvasWidget>(new CanvasWidget(this->_box, this->_size, this->_layers));
	}

	void CanvasWidget::setSize(const tgui::Layout2d &)
	{}

	void CanvasWidget::draw(sf::RenderTarget &target, sf::RenderStates states) const
	{
		sf::RectangleShape rect;
		sf::Sprite sprite;
		bool dark = false;
		auto size = this->_size;
		FrameBuffer buffer{size};
		auto color = Color{this->_colorCounter, this->_colorCounter, this->_colorCounter, 120};

		this->_colorCounter += (this->_counterUp * 2 - 1) * 20;
		this->_counterUp = (this->_counterUp && this->_colorCounter < 240) || !this->_colorCounter;
		if (this->selectedArea.isAnAreaSelected())
			for (auto &pt : this->selectedArea.getPoints())
				buffer.drawPixel(pt, color, SET);

		states.transform.translate(getPosition());

		rect.setOutlineThickness(0);
		for (unsigned x = 0; x < size.x; x += 10) {
			dark = x % 20;
			for (unsigned y = 0; y < size.y; y += 10) {
				rect.setFillColor(dark ? sf::Color{0x888888FF} : sf::Color::White);
				rect.setPosition(x, y);
				rect.setSize({
					static_cast<float>(size.x - x > 10 ? 10 : size.x - x),
					static_cast<float>(size.y - y > 10 ? 10 : size.y - y)
				});
				target.draw(rect, states);
				dark = !dark;
			}
		}

		for (auto &layer : this->_layers) {
			if (!layer->visible)
				continue;
			this->_drawBuffer.create(layer->getSize().x, layer->getSize().y);
			this->_drawBuffer.update(layer->buffer.getDrawBuffer(), layer->getSize().x, layer->getSize().y, 0, 0);
			sprite.setTexture(this->_drawBuffer, true);
			sprite.setPosition(layer->pos.x, layer->pos.y);
			target.draw(sprite, states);
		}
		this->_drawBuffer.create(size.x, size.y);
		this->_drawBuffer.update(buffer.getDrawBuffer(), size.x, size.y, 0, 0);
		sprite.setTexture(this->_drawBuffer, true);
		sprite.setPosition(0, 0);
		target.draw(sprite, states);
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
	}

	CanvasWidget::~CanvasWidget()
	{
		this->_destroyed = true;
		if (this->_renderThread.joinable())
			this->_renderThread.join();
	}

	void CanvasWidget::disableRendering()
	{
		this->_destroyed = true;
		if (this->_renderThread.joinable())
			this->_renderThread.join();
	}
}