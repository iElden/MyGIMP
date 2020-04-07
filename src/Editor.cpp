//
// Created by Gegel85 on 06/04/2020.
//

#include "Editor.hpp"

namespace Mimp
{
	Editor::Editor(const std::vector<std::string> &images)
	{

	}

	void Editor::setSelectedImage(const std::shared_ptr<CanvasWidget> &canvas)
	{
		this->_selectedImage = canvas;
	}

	std::shared_ptr<CanvasWidget> Editor::getSelectedImage() const
	{
		return this->_selectedImage;
	}

	int Editor::run()
	{
#ifndef _DEBUG
		//try {
#endif

#ifndef _DEBUG
		/*} catch (std::exception &e) {
			Utils::dispMsg(
				"Fatal Error",
				"An unrecoverable error occurred\n\n" +
				Utils::getLastExceptionName() + ":\n" + e.what() + "\n\n"
				"Click OK to close the application",
				MB_ICONERROR
			);
		}*/
#endif
		return EXIT_SUCCESS;
	}
}