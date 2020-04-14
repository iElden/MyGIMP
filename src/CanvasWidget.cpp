//
// Created by Gegel85 on 06/04/2020.
//

#include <SFML/Graphics/Sprite.hpp>
#include <iostream>
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
			this->_box.getSelectedTool()->onClick(realPos, MIMP_LEFT_CLICK, this->_layers.getSelectedLayer());
		});
		this->onRightMousePress.connect([this](tgui::Vector2f pos){
			Vector2<int> realPos;

			realPos.x = pos.x;
			realPos.y = pos.y;
			this->_rightMouseDown = true;
			this->_box.getSelectedTool()->onClick(realPos, MIMP_RIGHT_CLICK, this->_layers.getSelectedLayer());
		});
		this->onRightMouseRelease.connect([this](){
			this->_rightMouseDown = false;
		});
		this->_renderThread = std::thread([this]{
			while (!this->_destroyed) {
				this->_updateInternalBuffer();
				std::this_thread::sleep_for(std::chrono::milliseconds(10));
			}
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
			this->_box.getSelectedTool()->onClick(realPos, MIMP_LEFT_CLICK, this->_layers.getSelectedLayer());
		});
		this->onRightMousePress.connect([this](tgui::Vector2f pos){
			Vector2<int> realPos;

			realPos.x = pos.x;
			realPos.y = pos.y;
			this->_rightMouseDown = true;
			this->_box.getSelectedTool()->onClick(realPos, MIMP_RIGHT_CLICK, this->_layers.getSelectedLayer());
		});
		this->onRightMouseRelease.connect([this](){
			this->_rightMouseDown = false;
		});
		this->_drawBuffer.create(size.x, size.y);
		this->_renderThread = std::thread([this]{
			while (!this->_destroyed) {
				this->_updateInternalBuffer();
				std::this_thread::sleep_for(std::chrono::milliseconds(10));
			}
		});
	}

	void CanvasWidget::_updateInternalBuffer()
	{
		FrameBuffer buffer({
			static_cast<unsigned>(this->getSize().x),
			static_cast<unsigned>(this->getSize().y)
		});
		auto size = buffer.getSize();

		this->_layers.render(buffer);

		auto pixelArray = new sf::Color[size.x * size.y];

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

		realPos.x = pos.x;
		realPos.y = pos.y;
		if (this->m_mouseDown)
			this->_box.getSelectedTool()->onMouseDrag(this->_mousePos, realPos, MIMP_LEFT_CLICK, this->_layers.getSelectedLayer());
		if (this->_rightMouseDown)
			this->_box.getSelectedTool()->onMouseDrag(this->_mousePos, realPos, MIMP_RIGHT_CLICK, this->_layers.getSelectedLayer());
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
		sf::Sprite sprite;

		states.transform.translate(getPosition());
		sprite.setTexture(this->_drawBuffer);
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

	void CanvasWidget::importImage(const std::string &path)
	{
		this->_layers.importImage(path);
		this->_size = {
			this->_layers.getSize().x,
			this->_layers.getSize().y
		};
		this->m_size = {
			this->_size.x,
			this->_size.x
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