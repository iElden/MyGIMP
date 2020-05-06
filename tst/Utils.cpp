#include "gtest/gtest.h"
#include "src/Utils.hpp"

TEST(PathManipulation, trimCurrentPath1)
{
    std::string pathTest = "test/path/.";
    std::string path = "test/path";

    ASSERT_EQ(Mimp::Utils::cleanPath(pathTest), path);
}

TEST(PathManipulation, trimCurrentPath2)
{
    std::string pathTest = "test/path/././";
    std::string path = "test/path";

    ASSERT_EQ(Mimp::Utils::cleanPath(pathTest), path);
}

TEST(PathManipulation, trimParentPath1)
{
    std::string pathTest = "test/path/../";
    std::string path = "test";

    ASSERT_EQ(Mimp::Utils::cleanPath(pathTest), path);
}

TEST(PathManipulation, trimParentPath2)
{
    std::string pathTest = "test/path/./.././";
    std::string path = "test";

    ASSERT_EQ(Mimp::Utils::cleanPath(pathTest), path);
}
