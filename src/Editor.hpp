//
// Created by Gegel85 on 06/04/2020.
//

#ifndef MYGIMP_EDITOR_HPP
#define MYGIMP_EDITOR_HPP


#include <SFML/Graphics.hpp>
#include <TGUI/TGUI.hpp>
#include "ToolBox.hpp"
#include "Widgets/CanvasWidget.hpp"
#include "ImageOperations/ImageOperation.hpp"
#include "Keys.hpp"
#include "ShortcutManager.hpp"

namespace Mimp
{
	//! @brief Define the Editor
	class Editor {
	private:
		sf::RenderWindow _mainWindow; //!< Main Window
		tgui::Gui _gui; //!< Main GUI
		unsigned _lastUntitled = 0; //< Last Untitled index
		ToolBox _toolBox; //!< Global ToolBox
		std::vector<std::shared_ptr<ImageOperation>> _imgOps; //!< Contains all the ImageOperation available.
		std::map<Keys::KeyCombination, std::shared_ptr<ImageOperation>> _keysImgOps; //!< Contains all the shortcuts to invoke a specific ImageOperation
		tgui::ChildWindow::Ptr _selectedImageWindow; //!< The focused window
		std::map<tgui::ChildWindow::Ptr, Vector2<Vector2<float>>> _minimizedWindows; //!< A map to the minimized windows
		std::vector<std::string> _recents; //!< The recent mimp files
		std::vector<unsigned int> _signals; //!< Holds the signals used by tgui
		Vector2<unsigned> _lastSize = {640, 480}; //!< Save the last size configuration.

		ShortcutManager _shortcutManager;

		//! @brief Setup Button Callbacks
		void _setupButtonCallbacks();

		void _selectImage(tgui::ChildWindow::Ptr win);
		void _unselectImage();
		void _addToRecents(const std::string &path);
		void _updateRecentMenu();

		//! @brief Makes image panel
		//! @param canvas Canvas used to make image panel
		//! @return tgui::ChildWindow::Ptr The new window created
		tgui::ChildWindow::Ptr _makeImagePanel(CanvasWidget::Ptr canvas);

		CanvasWidget::Ptr _getSelectedCanvas();

		bool _saveImage(tgui::ChildWindow::Ptr win);
		void _checkClose(const std::function<void()> &endHandler, const std::function<void(tgui::ChildWindow::Ptr)> &handler = {});
		bool _checkSaved(std::string fileName, CanvasWidget::Ptr canvas, const std::function<void()> &noHandler, const std::function<void()> &yesHandler);

		tgui::Panel::Ptr _getLayerPanelRightClickPanel(const tgui::ChildWindow::Ptr& win, const CanvasWidget::Ptr& canvas, const tgui::Panel::Ptr& layersPanel, Layer &layer, unsigned index);

	public:
		//! @brief Create a panel containing the layers.
		//! @param win The focused window used to edit images.
		//! @param canvas The object containing the layers.
		tgui::Panel::Ptr _makeLayersPanel(tgui::ChildWindow::Ptr win, CanvasWidget::Ptr canvas);

		//! @brief Copy Constructor of the Editor
		Editor(const Editor &) = delete;

		//! @brief Constructor of the Editor class
		//! @param images Vector of images used to build the Editor
		Editor(const std::vector<std::string> &images = {});

		//! @brief Editor Destructor
		~Editor();

		//! @brief Set selected images
		//! @param _canvas Canvas to edit
		void setSelectedImage(tgui::ChildWindow::Ptr _canvas);

		//! @brief Get selected images
		//! @return tgui::ChildWindow::Ptr Selected image build into a Child window
		tgui::ChildWindow::Ptr getSelectedImage() const;

		void refreshSelectedLayerWidgets();

		//! @brief Run the editor
		//! @return int Errors
		int run();
	};
}


#endif //MYGIMP_EDITOR_HPP
