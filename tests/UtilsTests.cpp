//
// Created by jmartin on 4/15/20.
//

#include <criterion/criterion.h>
#include <criterion/redirect.h>
#include <iostream>
#include <sstream>
#include <zconf.h>
#include "../src/Utils.hpp"

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