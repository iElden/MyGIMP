//
// Created by Gegel85 on 07/04/2020.
//

#ifndef MYGIMP_UTILS_HPP
#define MYGIMP_UTILS_HPP


#include <string>
#include <vector>
#include <filesystem>
#include <TGUI/TGUI.hpp>
#include "Data/Color.hpp"
#include "Data/Vector2.hpp"
#include "Enum.hpp"
#include "Network/Socket.hpp"

#ifndef _WIN32
#define MB_ICONERROR 1
#else
#include <windows.h>
#endif


namespace Mimp::Utils
{
	struct HSLColor {
		unsigned char h;
		unsigned char s;
		unsigned char l;
	};

	//! @brief Display a Windows dialog box.
	//! @details This functions opens a Windows dialog box and return the button clicked by the user.
	//! @param title The title of the window.
	//! @param content The content of the box.
	//! @param variate A bit combination of the window attributes (see Windows MessageBox function for a list of the enums).
	//! @return The button clicked by the user.
	//! @note On Non-Windows systems, it will simulate the Windows dialog box. Only MB_ICONERROR and MB_OK are simulated on those systems.
	int	dispMsg(const std::string &title, const std::string &content, int variate);

	//! @brief Get the last Exception Name
	//! @details Return the last type of Exception name
	//! @return std::string The last Exception name
	std::string getLastExceptionName();

	//! @brief Opens a FileDialog
	//! @param title Title of the FileDialog
	//! @param basePath The path of the FileDialog
	//! @param patterns The patterns of the FileDialog
	//! @return std::string FileDialog message
	std::string openFileDialog(const std::string &title = "Open file", const std::string &basePath = ".", const std::vector<std::pair<std::string, std::string>> &patterns = {}, bool overWriteWarning = false, bool mustExist = true);

	//! @brief Saves a file dialog
	//! @param title Title of the FileDialog
	//! @param basePath The path of the FileDialog
	//! @param patterns The patterns of the FileDialog
	//! @return std::string FileDialog message
	std::string saveFileDialog(const std::string &title = "Save file", const std::string &basePath = ".", const std::vector<std::pair<std::string, std::string>> &patterns = {});

	//! @brief Convert a wstring into an UTF-8 string
	//! @param str String to convert in UTF-8
	//! @return std::string Converted String
	std::string wstringToUtf8(const std::wstring &str);

	//! @brief Convert a UTF-8 into a wstring
	//! @param str String to convert in wstring
	//! @return std::wstring Converted String
	std::wstring utf8ToWstring(const std::string &str);

	//! @brief Convert a std::filesystem::path to string UTF-8
	//! @param path filesystem path to convert
	//! @return std::string Converted Path in String
	std::string pathToString(const std::filesystem::path &path);

	//! @brief clean the . and .. in relative paths
	//! @param path filesystem path to clean
	//! @return std::string Converted Path in String
	std::string cleanPath(const std::string &path);

	//! @brief Display a focused window.
	//! @param gui The gui handling the window.
	//! @param width The width of the window.
	//! @param height The height of the window.
	//! @return A pointer to the window
	tgui::ChildWindow::Ptr openWindowWithFocus(tgui::Gui &gui, tgui::Layout width, tgui::Layout height);

	//! @brief Display a window with a slider.
	//! @param gui The gui handling the window.
	//! @param onFinish Function to call when exiting the window.
	//! @return A pointer to the window
	tgui::ChildWindow::Ptr makeSliderWindow(tgui::Gui &gui, const std::function<void(float value)> &onFinish, float defaultValue = 1, float min = 0, float max = 20, float step = 1);

	//! @brief Display a window with a Color picker.
	//! @param gui The gui handling the window.
	//! @param onFinish Function to call when exiting the window.
	//! @param startColor The color to initialize the picker.
	//! @return A pointer to the window
	tgui::ChildWindow::Ptr makeColorPickWindow(tgui::Gui &gui, const std::function<void(Color color)> &onFinish, Color startColor);

	//! @brief Convert a DrawShape to the string equivalent.
	//! @param shape The DrawShape to convert.
	//! @return std::string
	std::string DrawShapeToString(DrawShape shape);

	//! @brief Convert a string to the DrawShape equivalent.
	//! @param str The string to convert.
	//! @return DrawShape
	DrawShape DrawShapeFromString(const std::string &str);

	//! @brief Test if the given position fits the given size.
	//! @param pt The position of the point to test.
	//! @param size The limit to test the point position.
	//! @return bool
	bool isOutOfBound(Mimp::Vector2<int> pt, Mimp::Vector2<unsigned> size);

	//! @brief Try to get the body of the given URL.
	//! @param url The URL to fetch.
	//! @param recurseLimit The redirection limit.
	//! @return The body of the url, if resolved.
	std::string resolveUrl(const std::string &url, unsigned recurseLimit = 10);

	HSLColor RGBtoHSL(const Color &color);
	Color HSLtoRGB(const HSLColor &color);
	bool point_in_ellipse(int x, int y, int rx, int ry);
}


#endif //MYGIMP_UTILS_HPP
