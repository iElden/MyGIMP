#ifndef MYGIMP_KEYWIDGET_HPP
#define MYGIMP_KEYWIDGET_HPP

#include <TGUI/TGUI.hpp>
#include "../ImageOperations/ImageOperation.hpp"

namespace Mimp {
	//! @brief Define a KeyWidget
	class KeyWidget : public tgui::Button {
	public:
		typedef std::shared_ptr<KeyWidget> Ptr; //!< Shared widget pointer

		//! @brief Construct a KeyWidget
		//! @param key Name of the Key
		//! @param ptr A pointer to an ImageOperation
		//! @param entry The ImageOperation name
		explicit KeyWidget(std::string &key, std::shared_ptr<std::map<std::string, Keys::KeyCombination>> &ptr, const std::string entry) : _ptr(ptr), _entry(entry) { this->setText(key);}

		//! @brief Create a new CanvasWidget pointer
		//! @param key Name of the Key
		//! @param ptr A pointer to an ImageOperation
		//! @param entry The ImageOperation name
		//! @return CanvasWidget::Ptr
		static KeyWidget::Ptr create(std::string &&key, std::shared_ptr<std::map<std::string, Keys::KeyCombination>> &ptr, const std::string entry)
		{
			return std::make_shared<KeyWidget>(key, ptr, entry);
		}

		//! @brief Detect if the left click is pressed on the KeyWidget.
		//! @param pos The mouse position.
		void leftMousePressed(tgui::Vector2f pos) override;

		//! @brief Detect if a Key is pressed on the KeyWidget and set the text according to it.
		//! @param event The registered event
		void keyPressed(const sf::Event::KeyEvent &event) override;

	private:
		bool _editing = false;
		std::shared_ptr<std::map<std::string, Keys::KeyCombination>> _ptr;
		std::string _entry;
	};

}

#endif //MYGIMP_KEYWIDGET_HPP
