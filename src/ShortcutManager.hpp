#ifndef MYGIMP_SHORTCUTMANAGER_HPP
#define MYGIMP_SHORTCUTMANAGER_HPP

#include "Keys.hpp"
#include "ToolBox.hpp"
#include "ImageOperations/ImageOperationFactory.hpp"

namespace Mimp {
	//! @brief Define a ShortcutManager
	class ShortcutManager {
	public:
		//! @brief Construct a ShortcutManager
		//! @param tb The Toolbox to edit.
		//! @param io The ImageOperations to edit.
		ShortcutManager(ToolBox &tb, std::map<std::string, std::shared_ptr<ImageOperation>> io);

		//! @brief ShortcutManager Destructor
		~ShortcutManager();

		//! @brief Return all the shortcuts.
		std::map<std::string, std::shared_ptr<ImageOperation>> getShortcuts() const
		{ return _io; };

	private:
		std::map<std::string, std::shared_ptr<ImageOperation>> _io;
	};
}


#endif //MYGIMP_SHORTCUTMANAGER_HPP
