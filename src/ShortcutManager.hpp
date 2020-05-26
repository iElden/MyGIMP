#ifndef MYGIMP_SHORTCUTMANAGER_HPP
#define MYGIMP_SHORTCUTMANAGER_HPP

#include "Keys.hpp"
#include "ToolBox.hpp"
#include "ImageOperations/ImageOperationFactory.hpp"

namespace Mimp {
	class ShortcutManager {
	public:
		ShortcutManager(ToolBox &tb, std::unordered_map<std::string, std::shared_ptr<ImageOperation>> io);

		~ShortcutManager();

		std::unordered_map<std::string, std::shared_ptr<ImageOperation>> getShortcuts() const
		{ return _io; };

	private:
		std::unordered_map<std::string, std::shared_ptr<ImageOperation>> _io;
	};
}


#endif //MYGIMP_SHORTCUTMANAGER_HPP
