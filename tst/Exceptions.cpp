#include <gtest/gtest.h>
#include "../src/Utils.hpp"
#include "../src/Exceptions.hpp"
#include "../src/Network/Exceptions.hpp"

TEST(Utils, noException) {
    std::string lastException = Mimp::Utils::getLastExceptionName();

    ASSERT_EQ(lastException, "No exception");
}

TEST(Utils, corruptedGuiFileException) {
    try {
        throw Mimp::CorruptedGuiFileException("File Corrupted");
    } catch (Mimp::CorruptedGuiFileException &e) {
        std::string lastException = Mimp::Utils::getLastExceptionName();
        ASSERT_EQ(lastException, "Mimp::CorruptedGuiFileException");
    }
}

TEST(Utils, invalidArgumentException) {
    try {
        throw Mimp::InvalidArgumentException("InvalidArgument");
    } catch (Mimp::InvalidArgumentException &e) {
        std::string lastException = Mimp::Utils::getLastExceptionName();
        ASSERT_EQ(lastException, "Mimp::InvalidArgumentException");
    }
}

TEST(Utils, outOfBoundException) {
    try {
        throw Mimp::OutOfBoundException("Out of Bounds");
    } catch (Mimp::OutOfBoundException &e) {
        std::string lastException = Mimp::Utils::getLastExceptionName();
        ASSERT_EQ(lastException, "Mimp::OutOfBoundException");
    }
}

TEST(Utils, invalidImageException) {
    try {
        throw Mimp::InvalidImageException("InvalidImageException");
    } catch (Mimp::InvalidImageException &e) {
        std::string lastException = Mimp::Utils::getLastExceptionName();
        ASSERT_EQ(lastException, "Mimp::InvalidImageException");
    }
}

TEST(Utils, exportErrorException) {
    try {
        throw Mimp::ExportErrorException("ExportErrorException");
    } catch (Mimp::ExportErrorException &e) {
        std::string lastException = Mimp::Utils::getLastExceptionName();
        ASSERT_EQ(lastException, "Mimp::ExportErrorException");
    }
}

TEST(Utils, tooMuchRecursion) {
    try {
        throw Mimp::TooMuchRecursionException("TooMuchRecursionException");
    } catch (Mimp::TooMuchRecursionException &e) {
        std::string lastException = Mimp::Utils::getLastExceptionName();
        ASSERT_EQ(lastException, "Mimp::TooMuchRecursionException");
    }
}


TEST(Utils, tooMuchRecursionTwoLevels) {
    try {
        try {
            throw Mimp::TooMuchRecursionException("TooMuchRecursionException");
        } catch (Mimp::TooMuchRecursionException &e) {
            throw Mimp::TooMuchRecursionException(e, "Level 2");
        }
    } catch (Mimp::TooMuchRecursionException &e) {
        std::string lastException = Mimp::Utils::getLastExceptionName();
        ASSERT_EQ(lastException, "Mimp::TooMuchRecursionException");
        ASSERT_EQ(std::string(e.what()), "Level 2\nTooMuchRecursionException");
    }
}
