//
// Created by jmartin on 4/15/20.
//

#include <criterion/criterion.h>
#include <criterion/redirect.h>
#include <iostream>
#include <sstream>
#include <zconf.h>
#include "../src/Utils.hpp"
#include "../src/Exceptions.hpp"

Test(Utils, OpenAndSaveFileDialogTest)
{
	std::string openRes = Mimp::Utils::openFileDialog();
	std::string saveRes = Mimp::Utils::saveFileDialog();

	cr_assert_eq(openRes, "");
	cr_assert_eq(saveRes, "");
}

Test(Utils, GetLastExceptionTest)
{
	std::string lastException = Mimp::Utils::getLastExceptionName();

	cr_assert_eq(lastException, "No exception");
}

Test(Utils, GetLastExceptionTest2)
{
	try {
		throw Mimp::CorruptedGuiFileException("File Corrupted");
	} catch (Mimp::BaseException &e) {
		std::string lastException = Mimp::Utils::getLastExceptionName();
		cr_assert_eq(lastException, "Mimp::CorruptedGuiFileException");
	}
}

Test(Utils, GetLastExceptionTest3)
{
	try {
		throw Mimp::InvalidArgumentException("InvalidArgument");
	} catch (Mimp::BaseException &e) {
		std::string lastException = Mimp::Utils::getLastExceptionName();
		cr_assert_eq(lastException, "Mimp::InvalidArgumentException");
	}
}

Test(Utils, GetLastExceptionTest4)
{
	try {
		throw Mimp::OutOfBoundException("Out of Bounds");
	} catch (Mimp::BaseException &e) {
		std::string lastException = Mimp::Utils::getLastExceptionName();
		cr_assert_eq(lastException, "Mimp::OutOfBoundException");
	}
}

Test(Utils, GetLastExceptionTest5)
{
	try {
		throw Mimp::InvalidImageException("InvalidImageException");
	} catch (Mimp::BaseException &e) {
		std::string lastException = Mimp::Utils::getLastExceptionName();
		cr_assert_eq(lastException, "Mimp::InvalidImageException");
	}
}

Test(Utils, GetLastExceptionTest6)
{
	try {
		throw Mimp::ExportErrorException("ExportErrorException");
	} catch (Mimp::BaseException &e) {
		std::string lastException = Mimp::Utils::getLastExceptionName();
		cr_assert_eq(lastException, "Mimp::ExportErrorException");
	}
}

Test(Utils, PathToStringTest)
{
	std::filesystem::path p = "/home/jmartin/";

	cr_assert_eq(Mimp::Utils::pathToString(p), "/home/jmartin/");
}

Test(Utils, CleanPathTest)
{
	std::filesystem::path p = "../.././jmartin/";

	cr_assert_eq(Mimp::Utils::cleanPath(Mimp::Utils::pathToString(p)), "jmartin");
}