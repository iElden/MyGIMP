//
// Created by Gegel85 on 14/05/2020.
//

#ifndef MYGIMP_LAYERWIDGET_HPP
#define MYGIMP_LAYERWIDGET_HPP


#include <TGUI/Widgets/ClickableWidget.hpp>
#include "../Layer/Layer.hpp"

namespace Mimp
{
    //! @brief Define the LayerWidget.
	class LayerWidget : public tgui::ClickableWidget {
	private:
		const std::shared_ptr<Layer> &_layer;
		bool _mouseDisabled;
		mutable sf::Texture _drawBuffer;

	public:
		typedef std::shared_ptr<LayerWidget> Ptr; //!< Shared widget pointer
		typedef std::shared_ptr<const LayerWidget> ConstPtr; //!< Shared constant widget pointer

		//! @brief Constructor of the LayerWidget
		//! @param layer The Layer to handle.
		//! @param size Size of the Preview
		LayerWidget(const std::shared_ptr<Layer> &layer, Vector2<tgui::Layout> size);

		//! @brief LayerWidget destructor
		~LayerWidget() override = default;

		//! @brief Create a new LayerWidget pointer
		//! @param layer The Layer to handle
		//! @param size Size of the Widget. Default is 32x32.
		static LayerWidget::Ptr create(const std::shared_ptr<Layer> &layer, Vector2<tgui::Layout> size = {32, 32});

		//! @brief Detect if the mouse is on the LayerWidget.
		//! @param pos The mouse position.
		//! @return bool
		bool mouseOnWidget(tgui::Vector2f pos) const override;

		//! @brief Set if the mouse is ignored upon the LayerWIdget or not.
		//! @param ignored Is the mouse ignore or not. Default is true.
		void ignoreMouseEvent(bool ignored = true);

		//! @brief Draw the LayerWidget.
		//! @param target Where to draw.
		//! @param states How to draw.
		void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

		//! @brief Clone the LayerWidget.
		//! @return A pointer to the clone.
		Widget::Ptr clone() const override;
	};
}

#endif //MYGIMP_LAYERWIDGET_HPP
