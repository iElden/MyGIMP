//
// Created by Gegel85 on 07/04/2020.
//

#ifndef MYGIMP_UTILS_HPP
#define MYGIMP_UTILS_HPP


#include <string>
#include <vector>

#ifndef _WIN32
#define MB_ICONERROR 1
#else
#include <windows.h>
#endif


namespace Mimp::Utils
{
	//! @brief Display a Windows dialog box.
	//! @details This functions opens a Windows dialog box and return the button clicked by the user.
	//! @param title The title of the window.
	//! @param content The content of the box.
	//! @param variate A bit combination of the window attributes (see Windows MessageBox function for a list of the enums).
	//! @return The button clicked by the user.
	//! @note On Non-Windows systems, it will simulate the Windows dialog box. Only MB_ICONERROR and MB_OK are simulated on those systems.
	int	dispMsg(const std::string &title, const std::string &content, int variate);

	//! @brief Get the last Exception Name
	//! @details Return the last type of exception name
	//! @return std::string The last exception name
	std::string getLastExceptionName();

	//! @brief Opens a file dialog
	//! @param title Title of the FileDialog
	//! @param basePath The path of the FileDialog
	//! @param patterns The patterns of the FileDialog
	//! @return std::string FileDialog message
	std::string openFileDialog(const std::string &title = "Open file", const std::string &basePath = ".", const std::vector<std::pair<std::string, std::string>> &patterns = {});
    //! @brief Saves a file dialog
    //! @param title Title of the FileDialog
    //! @param basePath The path of the FileDialog
    //! @param patterns The patterns of the FileDialog
    //! @return std::string FileDialog message
	std::string saveFileDialog(const std::string &title = "Save file", const std::string &basePath = ".", const std::vector<std::pair<std::string, std::string>> &patterns = {});
}


#endif //MYGIMP_UTILS_HPP
