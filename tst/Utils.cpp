#include <gtest/gtest.h>
#include "../src/Utils.hpp"
#include "../src/Exceptions.hpp"
#include "../src/Network/Exceptions.hpp"

TEST(Utils, resolveUrlBadLimit) {
    try {
        Mimp::Utils::resolveUrl("http://", 0);
    } catch (Mimp::TooMuchRecursionException &e) {
        ASSERT_EQ(std::string(e.what()), "http://: Recurse limit is 0");
    }
}

TEST(Utils, resolveUrlBadProtocol) {
    try {
        Mimp::Utils::resolveUrl("blah://test");
    } catch (Mimp::UnsupportedProtocolException &e) {
        ASSERT_EQ(std::string(e.what()), "blah:// is not a supported protocol");
    }
}

TEST(Utils, resolveUrlBadHost1) {
    try {
        Mimp::Utils::resolveUrl("http://www.mygimp.fr");
    } catch (Mimp::HostNotFoundException &e) {
        ASSERT_EQ(std::string(e.what()), "Cannot find host 'www.mygimp.fr'");
    }
}

TEST(Utils, resolveUrlBadHost2) {
    try {
        Mimp::Utils::resolveUrl("https://www.mygimp.fr");
    } catch (Mimp::HostNotFoundException &e) {
        ASSERT_EQ(std::string(e.what()), "Cannot find host 'www.mygimp.fr'");
    }
}

TEST(Utils, resolveUrlBadFile) {
    try {
        Mimp::Utils::resolveUrl("file://MIMP");
    } catch (Mimp::FileNotFoundException &e) {
        ASSERT_EQ(std::string(e.what()), "MIMP: No such file or directory");
    }
}

TEST(Utils, resolveValidUrl) {
    auto body = Mimp::Utils::resolveUrl("https://www.google.com");

    ASSERT_NE(body.size(), 0);
}

TEST(Utils, resolveExistingFile) {
#ifdef _WIN32
    std::string testFilePath = std::filesystem::current_path().string() + "/tst/TestFile";
#else
    std::string testFilePath = std::filesystem::current_path().string() + "/tst/TestFile";
#endif
    auto content = Mimp::Utils::resolveUrl("file://" + testFilePath);

    ASSERT_NE(content.size(), 0);
}

TEST(Utils, drawshapeToString) {
    ASSERT_EQ(Mimp::Utils::DrawShapeToString(Mimp::DrawShape::CIRCLE), "Circle");
    ASSERT_EQ(Mimp::Utils::DrawShapeToString(Mimp::DrawShape::SQUARE), "Square");
    ASSERT_EQ(Mimp::Utils::DrawShapeToString(Mimp::DrawShape::DIAMOND), "Diamond");

    try {
        Mimp::Utils::DrawShapeToString(Mimp::DrawShape::NB_OF_SHAPES);
    } catch (Mimp::InvalidDrawShapeException &e) {
        ASSERT_EQ(std::string(e.what()), "NB_OF_SHAPES is not a DrawShape");
    }
    try {
        Mimp::Utils::DrawShapeToString(static_cast<Mimp::DrawShape>(-1));
    } catch (Mimp::InvalidDrawShapeException &e) {
        ASSERT_EQ(std::string(e.what()), "Invalid DrawShape");
    }
}

TEST(Utils, stringToDrawshape) {
    ASSERT_EQ(Mimp::Utils::DrawShapeFromString("Circle"), Mimp::DrawShape::CIRCLE);
    ASSERT_EQ(Mimp::Utils::DrawShapeFromString("Square"), Mimp::DrawShape::SQUARE);
    ASSERT_EQ(Mimp::Utils::DrawShapeFromString("Diamond"), Mimp::DrawShape::DIAMOND);

    try {
        Mimp::Utils::DrawShapeFromString("Mimp");
    } catch (Mimp::InvalidDrawShapeException &e) {
        ASSERT_EQ(std::string(e.what()), "Mimp is not a valid DrawShape");
    }
    try {
        Mimp::Utils::DrawShapeToString(static_cast<Mimp::DrawShape>(-1));
    } catch (Mimp::InvalidDrawShapeException &e) {
        ASSERT_EQ(std::string(e.what()), "Invalid DrawShape");
    }
}


inline std::string PATH(const std::string &path) {
    std::string newPath;
    for (auto &c : path)
        newPath += c == '/' ? std::filesystem::path::preferred_separator : c;
    return newPath;
}

TEST(Utils, cleanPathParent1) {

    ASSERT_EQ(Mimp::Utils::cleanPath(PATH(".././test1/test2/..")), PATH("/test1"));
}

TEST(Utils, cleanPathParent2) {
    ASSERT_EQ(Mimp::Utils::cleanPath(PATH(".././test1/./test2/..")), PATH("/test1"));
}

TEST(Utils, cleanPathParent3) {
    ASSERT_EQ(Mimp::Utils::cleanPath(PATH("test1/test2/..")), PATH("/test1"));
}

TEST(Utils, cleanPathParent4) {
    ASSERT_EQ(Mimp::Utils::cleanPath(PATH("test1/./test2/..")), PATH("/test1"));
}

TEST(Utils, getLastException1) {
#ifdef __GNUG__
    ASSERT_EQ(Mimp::Utils::getLastExceptionName(), "No exception");
#else
    ASSERT_EQ(Mimp::Utils::getLastExceptionName(), "Unknown exception");
#endif
}

TEST(Utils, getLastException2) {
#ifdef __GNUG__
    try {
        throw Mimp::FileNotFoundException("file");
    } catch (std::exception &e) {
        ASSERT_EQ(Mimp::Utils::getLastExceptionName(), "Mimp::FileNotFoundException");
    }
#else
    ASSERT_EQ(Mimp::Utils::getLastExceptionName(), "Unknown exception");
#endif
}

TEST(Utils, isOutOfBounds) {
    Mimp::Vector2<int> ptXNeg = {-1, 0};
    Mimp::Vector2<int> ptYNeg = {0, -1};
    Mimp::Vector2<int> pt = {2, 9};

    ASSERT_TRUE(Mimp::Utils::isOutOfBound(ptXNeg, {0, 0}));
    ASSERT_TRUE(Mimp::Utils::isOutOfBound(ptYNeg, {0, 0}));

    ASSERT_TRUE(Mimp::Utils::isOutOfBound(pt, {1, 10}));
    ASSERT_TRUE(Mimp::Utils::isOutOfBound(pt, {6, 8}));
}