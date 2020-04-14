//
// Created by Gegel85 on 06/04/2020.
//

#ifndef MYGIMP_CANVASWIDGET_HPP
#define MYGIMP_CANVASWIDGET_HPP


#include <TGUI/Widgets/ChildWindow.hpp>
#include <memory>
#include <thread>
#include "Layer/LayerManager.hpp"
#include "ToolBox.hpp"
#include "Image.hpp"

namespace Mimp
{
	//! @brief Class Canvas Widget
	//! @inherit tgui::ClickableWidget
	//! @inherit Image
	//! @details Widget on which you can fully draw, edit, paint...
	class CanvasWidget : public tgui::ClickableWidget, public Image {
	private:
		//! @details Mouse Position
		Vector2<int> _mousePos = {0, 0};
		//! @details ToolBox
		const ToolBox &_box;
		//! @details Mouse Right Click State
		bool _rightMouseDown = false;

		bool _destroyed = false;

		std::thread _renderThread;

		sf::Texture _drawBuffer;

		//! @details Private Constructor of the Canvas Widget class
		//! @param box ToolBox
		//! @param size Size of the canvas
		//! @param layers LayerManager of the canvas
		CanvasWidget(const ToolBox &box, Vector2<unsigned int> size, const LayerManager &layers);

		void _updateInternalBuffer();

	public:
		//! @brief Shared widget pointer
		typedef std::shared_ptr<CanvasWidget> Ptr; ///< Shared widget pointer
		//! @brief Shared constant widget pointer
		typedef std::shared_ptr<const CanvasWidget> ConstPtr; ///< Shared constant widget pointer

		//! @brief Public Constructor of the CanvasWidget class
		//! @param box ToolBox
		//! @param size Size of the Canvas
		CanvasWidget(const ToolBox &box, Vector2<unsigned int> size);
		//! @brief Public Constructor of the CanvasWidget class
		//! @param box ToolBox
		//! @param path Path of the Canvas file
		CanvasWidget(const ToolBox &box, const std::string &path);
		~CanvasWidget() override;

		//! @brief create a new Canvas pointer
		//! @param box ToolBox
		//! @param size Size of the canva
		//! @return CanvasWidget::Ptr
		static CanvasWidget::Ptr create(const ToolBox &box, Vector2<unsigned int> size);
		//! @brief create a new Canvas pointer
		//! @param box ToolBox
		//! @param path Path of the canva
		//! @return CanvasWidget::Ptr
		static CanvasWidget::Ptr create(const ToolBox &box, const std::string &path);

		void disableRendering();
		void mouseMoved(tgui::Vector2f pos) override;
		void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
		Widget::Ptr clone() const override;
		void setSize(const tgui::Layout2d& size) override;
		//! @brief Import an image
		//! @param path Path of the image
		void importImage(const std::string &path);
	};
}


#endif //MYGIMP_CANVASWIDGET_HPP
