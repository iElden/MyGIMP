//
// Created by Gegel85 on 06/04/2020.
//

#ifndef MYGIMP_CANVASWIDGET_HPP
#define MYGIMP_CANVASWIDGET_HPP


#include <TGUI/Widgets/ChildWindow.hpp>
#include <memory>
#include <thread>
#include "../Layer/LayerManager.hpp"
#include "../ToolBox.hpp"
#include "../Image.hpp"

namespace Mimp
{
	//! @brief Define a CanvasWidget
	class CanvasWidget : public tgui::ClickableWidget, public Image {
	private:
		Vector2<int> _mousePos = {0, 0}; //!< Mouse Position
		const ToolBox &_box; //!< The ToolBox used by the CanvasWidget
		bool _rightMouseDown = false; //!< Mouse right click state

		mutable bool _counterUp = true;

		bool _edited = false;
		float _zoom = 1.f;

		bool _drawGrid = false;
		int _gridSize = 10;

		Vector2<bool> _symmetry = {false, false};
		Vector2<int> _axis = {0, 0};

		mutable unsigned char _colorCounter = 0;

		mutable sf::Texture _drawBuffer;

		//! @details Private Constructor of the Canvas Widget class
		//! @param box ToolBox
		//! @param size Size of the canvas
		//! @param layers LayerManager of the canvas
		CanvasWidget(const ToolBox &box, Vector2<unsigned int> size, const LayerManager &layers);

		void _makeCallbacks();

	public:
		typedef std::shared_ptr<CanvasWidget> Ptr; //!< Shared widget pointer
		typedef std::shared_ptr<const CanvasWidget> ConstPtr; //!< Shared constant widget pointer

		//! @brief Construct a CanvasWidget
		//! @param box ToolBox linked to the CanvasWidget
		//! @param size Size of the CanvasWidget
		CanvasWidget(const ToolBox &box, Vector2<unsigned int> size);

		//! @brief Public Constructor of the CanvasWidget class
		//! @param box ToolBox linked to the CanvasWidget
		//! @param path Path of the CanvasWidget file
		CanvasWidget(const ToolBox &box, const std::string &path);

		//! @brief CanvasWidget Destructor
		~CanvasWidget() override = default;

		//! @brief Create a new CanvasWidget pointer
		//! @param box ToolBox linked to the CanvasWidget
		//! @param size Size of the CanvasWidget
		//! @return CanvasWidget::Ptr
		static CanvasWidget::Ptr create(const ToolBox &box, Vector2<unsigned int> size);

		//! @brief Create a new CanvasWidget pointer
        //! @param box ToolBox linked to the CanvasWidget
        //! @param path Path of the CanvasWidget file
        //! @return CanvasWidget::Ptr
		static CanvasWidget::Ptr create(const ToolBox &box, const std::string &path);

		//! @brief Get the status of the Canvas
		bool isEdited() const;

        //! @brief Set the status of the CanvasWidget.
        //! @param edited The status of the CanvasWidget. Default is true
		void setEdited(bool edited = true);

		//! @brief Set the zoom level of the canvas
		//! @param zoom The zoom level
		void setZoomLevel(float zoom);

		//! @brief Get the zoom level of the canvas
		float getZoomLevel() const;

		//! @brief Handles mouse movements inside the canvas.
		//! @param pos The position of the Mouse
		void mouseMoved(tgui::Vector2f pos) override;

		//! @brief Draw the canvas
		//! @param target Where to draw
        //! @param states How to draw
		void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

		//! @brief Clone the CanvasWidget
		//! @return Widget::Ptr
		Widget::Ptr clone() const override;

		//! @brief Import an image in the canvas
		//! @param path Path of the image
		void importImageFromFile(const std::string &path);

		//! @brief Import an image in the canvas
		//! @param data Image data as string
		void importImageFromMemory(const std::string &data);

		void updateGrid() { this->_drawGrid = !this->_drawGrid; };

		void increaseGrid();

		void decreaseGrid();

		void setSymmetry(Vector2<bool> &symmetry);

		void setSymmetryAxis(Vector2<int> &axis);
	};
}


#endif //MYGIMP_CANVASWIDGET_HPP
