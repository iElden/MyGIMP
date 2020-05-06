//
// Created by jmartin on 4/15/20.
//

#include <gtest/gtest.h>
#include <zconf.h>
#include "../src/Utils.hpp"
#include "../src/Exceptions.hpp"

TEST(Utils, GetLastExceptionTest)
{
	std::string lastException = Mimp::Utils::getLastExceptionName();

	ASSERT_EQ(lastException, "No exception");
}

TEST(Utils, GetLastExceptionTest2)
{
	try {
		throw Mimp::CorruptedGuiFileException("File Corrupted");
	} catch (Mimp::BaseException &e) {
		std::string lastException = Mimp::Utils::getLastExceptionName();
		ASSERT_EQ(lastException, "Mimp::CorruptedGuiFileException");
	}
}

TEST(Utils, GetLastExceptionTest3)
{
	try {
		throw Mimp::InvalidArgumentException("InvalidArgument");
	} catch (Mimp::BaseException &e) {
		std::string lastException = Mimp::Utils::getLastExceptionName();
		ASSERT_EQ(lastException, "Mimp::InvalidArgumentException");
	}
}

TEST(Utils, GetLastExceptionTest4)
{
	try {
		throw Mimp::OutOfBoundException("Out of Bounds");
	} catch (Mimp::BaseException &e) {
		std::string lastException = Mimp::Utils::getLastExceptionName();
		ASSERT_EQ(lastException, "Mimp::OutOfBoundException");
	}
}

TEST(Utils, GetLastExceptionTest5)
{
	try {
		throw Mimp::InvalidImageException("InvalidImageException");
	} catch (Mimp::BaseException &e) {
		std::string lastException = Mimp::Utils::getLastExceptionName();
		ASSERT_EQ(lastException, "Mimp::InvalidImageException");
	}
}

TEST(Utils, GetLastExceptionTest6)
{
	try {
		throw Mimp::ExportErrorException("ExportErrorException");
	} catch (Mimp::BaseException &e) {
		std::string lastException = Mimp::Utils::getLastExceptionName();
		ASSERT_EQ(lastException, "Mimp::ExportErrorException");
	}
}

TEST(Utils, PathToStringTest)
{
	std::filesystem::path p = "/home/jmartin/";

	ASSERT_EQ(Mimp::Utils::pathToString(p), "/home/jmartin/");
}

TEST(Utils, CleanPathTest)
{
	std::filesystem::path p = "../.././jmartin/";

	ASSERT_EQ(Mimp::Utils::cleanPath(Mimp::Utils::pathToString(p)), "jmartin");
}
