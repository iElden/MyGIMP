//
// Created by Gegel85 on 14/05/2020.
//

#ifndef MYGIMP_LAYERWIDGET_HPP
#define MYGIMP_LAYERWIDGET_HPP


#include <TGUI/Widgets/ClickableWidget.hpp>
#include "Layer/Layer.hpp"

namespace Mimp
{
	class LayerWidget : public tgui::ClickableWidget {
	private:
		Layer &_layer;
		bool _mouseDisabled;
		mutable sf::Texture _drawBuffer;

	public:
		//! @brief Shared widget pointer
		typedef std::shared_ptr<LayerWidget> Ptr; ///< Shared widget pointer
		//! @brief Shared constant widget pointer
		typedef std::shared_ptr<const LayerWidget> ConstPtr; ///< Shared constant widget pointer

		//! @brief Public Constructor of the CanvasWidget class
		//! @param box ToolBox
		//! @param size Size of the Preview
		LayerWidget(Layer &layer, Vector2<tgui::Layout> size);
		~LayerWidget() override = default;

		//! @brief create a new LayerWidget pointer
		//! @param layer Layer
		//! @param size Size of the Widget
		static LayerWidget::Ptr create(Layer &layer, Vector2<tgui::Layout> size = {32, 32});

		//! @brief Disable the rendering by joining the render thread
		bool mouseOnWidget(tgui::Vector2f pos) const override;
		void ignoreMouseEvent(bool ignored = true);
		void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
		Widget::Ptr clone() const override;
	};
}

#endif //MYGIMP_LAYERWIDGET_HPP
