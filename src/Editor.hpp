//
// Created by Gegel85 on 06/04/2020.
//

#ifndef MYGIMP_EDITOR_HPP
#define MYGIMP_EDITOR_HPP


#include <SFML/Graphics.hpp>
#include <TGUI/Gui.hpp>
#include "ToolBox.hpp"
#include "CanvasWidget.hpp"

namespace Mimp
{
	//! @brief Class Editor
	//! @details Main window editor
	class Editor {
	private:
		//! @brief Main Window
		sf::RenderWindow _mainWindow;
		//! @brief Gui
		tgui::Gui _gui;
		//! @brief Last Untitled
		unsigned _lastUntitled = 0;
		//! @brief ToolBox
		ToolBox _toolBox;
		//! @brief Selected Image
		tgui::ChildWindow::Ptr _selectedImageWindow;

		//! @brief Setup Button Callbacks
		void _setupButtonCallbacks();

		//! @brief Makes image panel
		//! @param canvas Canvas used to make image panel
		//! @return tgui::ChildWindow::Ptr The new window created
		tgui::ChildWindow::Ptr _makeImagePanel(CanvasWidget::Ptr canvas);

		CanvasWidget::Ptr _getSelectedCanvas();

		tgui::Panel::Ptr _getLayerRightClickPanel();
		tgui::Panel::Ptr _getLayerPanelRightClickPanel();
		tgui::Panel::Ptr _makeLayersPanel(tgui::ChildWindow::Ptr win, CanvasWidget::Ptr canvas);
	public:
		//! @brief Copy Constructor of the Editor class not used
		Editor(const Editor &) = delete;
		//! @brief Constructor of the Editor class
		//! @param images Vector of images used to build the Editor
		Editor(const std::vector<std::string> &images = {});

		//! @brief Set selected images
		//! @param _canvas Canvas used to be selected
		void setSelectedImage(tgui::ChildWindow::Ptr _canvas);
		//! @brief Get selected images
		//! @return tgui::ChildWindow::Ptr Selected image build into a Child window
		tgui::ChildWindow::Ptr getSelectedImage() const;
		//! @brief Run the editor
		//! @return int Errors
		int run();
	};
}


#endif //MYGIMP_EDITOR_HPP
