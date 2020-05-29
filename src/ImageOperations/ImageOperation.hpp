//
// Created by Gegel85 on 25/04/2020.
//

#ifndef MYGIMP_IMAGEOPERATION_HPP
#define MYGIMP_IMAGEOPERATION_HPP


#include <TGUI/Gui.hpp>
#include "../Image.hpp"
#include "../CanvasWidget.hpp"
#include "../Keys.hpp"

namespace Mimp
{
	class Editor;

	//! @brief Define the ImageOperation base class.
	class ImageOperation : public Action {
	private:
		std::vector<std::string> _hierarchy;
		std::optional<Keys::KeyCombination> _keys;
		std::string _name;

	protected:
		//! @brief Constructor of ImageOperation
		//! @param hierarchy A vector of the hierarchy (ie : Menu title -> operation name)
		//! @param name The name of the ImageOperation.
		ImageOperation(const std::vector<std::string> &&hierarchy, const std::string &&name);

		//! @brief Constructor of ImageOperation
		//! @param hierarchy A vector of the hierarchy (ie : Menu title -> operation name)
		//! @param name The name of the ImageOperation.
		//! @param keys The key combination to invoke the operation.
		ImageOperation(const std::vector<std::string> &&hierarchy, const std::string &&name, const Keys::KeyCombination &keys);

	public:
		//! @brief Handles the click. Must be override.
		virtual void click(tgui::Gui &gui, CanvasWidget::Ptr, tgui::ChildWindow::Ptr window, Editor &editor) const = 0;

		//! @brief Get the hierarchy of a menu item.
		//! @return A vector of all the menu hierarchy.
		const std::vector<std::string> &getMenuHierarchy() const;

		std::string getName()
		{
			return this->_name;
		}
	};
}


#endif //MYGIMP_IMAGEOPERATION_HPP
