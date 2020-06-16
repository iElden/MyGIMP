#include <filesystem>
#include "Editor.hpp"
#include "Utils.hpp"
#ifdef _WIN32
#include <direct.h>
#else
#include <unistd.h>
#endif

int main(int, char **argv)
{
#ifndef _DEBUG
	try {
#endif

	Mimp::Editor editor;

	chdir(std::filesystem::path(argv[0]).parent_path().string().c_str());
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
