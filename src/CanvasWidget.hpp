//
// Created by Gegel85 on 06/04/2020.
//

#ifndef MYGIMP_CANVASWIDGET_HPP
#define MYGIMP_CANVASWIDGET_HPP


#include <TGUI/Widgets/ChildWindow.hpp>
#include <memory>
#include "Layer/LayerManager.hpp"
#include "ToolBox.hpp"

namespace Mimp
{
	class CanvasWidget : public tgui::ClickableWidget {
	private:
		Vector2<int> _mousePos = {0, 0};
		LayerManager _layers;
		const ToolBox &_box;
		Vector2<unsigned int> _size;
		bool _rightMouseDown = false;

		CanvasWidget(const ToolBox &box, Vector2<unsigned int> size, const LayerManager &layers);

	public:
		typedef std::shared_ptr<CanvasWidget> Ptr; ///< Shared widget pointer
		typedef std::shared_ptr<const CanvasWidget> ConstPtr; ///< Shared constant widget pointer

		CanvasWidget(const ToolBox &box, Vector2<unsigned int> size);
		CanvasWidget(const ToolBox &box, const std::string &path);

		static CanvasWidget::Ptr create(const ToolBox &box, Vector2<unsigned int> size);
		static CanvasWidget::Ptr create(const ToolBox &box, const std::string &path);

		void mouseMoved(tgui::Vector2f pos) override;
		void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
		Widget::Ptr clone() const override;
		void setSize(const tgui::Layout2d& size) override;
	};
}


#endif //MYGIMP_CANVASWIDGET_HPP
