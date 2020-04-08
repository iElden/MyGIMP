//
// Created by Gegel85 on 06/04/2020.
//

#include <SFML/Graphics/Sprite.hpp>
#include "CanvasWidget.hpp"

namespace Mimp
{
	CanvasWidget::CanvasWidget(const ToolBox &box, const std::string &path) :
		CanvasWidget(box, Vector2<unsigned>{0, 0})
	{
		//TODO: Load file
	}

	CanvasWidget::CanvasWidget(const ToolBox &box, Vector2<unsigned int> size, const LayerManager &layers) :
		_layers(layers),
		_box(box),
		_size(size)
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
			this->_box.getSelectedTool()->onClick(realPos, MIMP_LEFT_CLICK, this->_layers.getSelectedLayer());
		});
		this->onRightMouseRelease.connect([this](){
			this->_rightMouseDown = false;
		});
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

	CanvasWidget::CanvasWidget(const ToolBox &box, Vector2<unsigned int> size) :
		_layers(size, 1, Color::White),
		_box(box),
		_size(size)
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
	}

	tgui::Widget::Ptr CanvasWidget::clone() const
	{
		return std::shared_ptr<CanvasWidget>(new CanvasWidget(this->_box, this->_size, this->_layers));
	}

	void CanvasWidget::setSize(const tgui::Layout2d &)
	{}

	void CanvasWidget::draw(sf::RenderTarget &target, sf::RenderStates states) const
	{
		sf::Texture texture;
		sf::Sprite sprite;
		FrameBuffer buffer({
			static_cast<unsigned>(this->getSize().x),
			static_cast<unsigned>(this->getSize().y)
		});
		auto size = buffer.getSize();

		states.transform.translate(getPosition());
		this->_layers.render(buffer);

		texture.create(size.x, size.y);

		auto pixelArray = new sf::Color[size.x * size.y];

		for (unsigned x = 0; x < size.x; x++)
			for (unsigned y = 0; y < size.y; y++)
				pixelArray[x + y * size.x] = buffer.getPixel({static_cast<int>(x), static_cast<int>(y)});
		texture.update(reinterpret_cast<const sf::Uint8 *>(pixelArray));

		sprite.setTexture(texture);

		target.draw(sprite, states);
		delete[] pixelArray;
	}

	CanvasWidget::Ptr CanvasWidget::create(const ToolBox &box, Vector2<unsigned int> size)
	{
		return std::make_shared<CanvasWidget>(box, size);
	}

	CanvasWidget::Ptr CanvasWidget::create(const ToolBox &box, const std::string &path)
	{
		return std::make_shared<CanvasWidget>(box, path);
	}
}