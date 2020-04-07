#include "Editor.hpp"
#include "Utils.hpp"

int main()
{
#ifndef _DEBUG
	try {
#endif

	Mimp::Editor editor;

	return editor.run();

#ifndef _DEBUG
	} catch (std::exception &e) {
		Mimp::Utils::dispMsg(
			"Fatal Error",
			"An unrecoverable error occurred\n\n" +
				Mimp::Utils::getLastExceptionName() + ":\n" + e.what() + "\n\n"
			"Click OK to close the application",
			MB_ICONERROR
		);
		return EXIT_FAILURE;
	}
#endif
}
