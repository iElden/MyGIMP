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
		ShortcutManager(std::map<std::string, std::shared_ptr<Tool>> tb, std::map<std::string, std::shared_ptr<ImageOperation>> io);

		//! @brief ShortcutManager Destructor
		~ShortcutManager();

		//! @brief Return all the shortcuts.
		std::map<std::string, std::shared_ptr<ImageOperation>> getIoShortcuts() const
		{ return _io; };

		std::map<std::string, std::shared_ptr<Tool>> getToolShortcuts() const
		{ return _tb; };

		std::map<std::string , std::shared_ptr<Action>> getShortcuts() const {
			return _shortcuts;
		};

		bool isBusy() { return this->_isBusy; }

		void setBusy(bool b = true) { this->_isBusy = b; }

	private:
		std::map<std::string, std::shared_ptr<ImageOperation>> _io;
		std::map<std::string, std::shared_ptr<Tool>> _tb;

		std::map<std::string, std::shared_ptr<Action>> _shortcuts;

		bool _isBusy = false;
	};
}


#endif //MYGIMP_SHORTCUTMANAGER_HPP
