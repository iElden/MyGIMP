#include <gtest/gtest.h>
#include "../src/Data/Vector2.hpp"

TEST(VectorManipulation, addition)
{
    Mimp::Vector2<int> v1 = {1, 1};
    Mimp::Vector2<int> v2 = {2, 6};
    Mimp::Vector2<int> v3 = {3, 7};

    auto v4 = v1 + v2;
    ASSERT_EQ(v4.x, v3.x);
    ASSERT_EQ(v4.y, v3.y);
}

TEST(VectorManipulation, substraction)
{
    Mimp::Vector2<int> v1 = {-1, 1};
    Mimp::Vector2<int> v2 = {2, -6};
    Mimp::Vector2<int> v3 = {-3, 7};

    auto v4 = v1 - v2;
    ASSERT_EQ(v4.x, v3.x);
    ASSERT_EQ(v4.y, v3.y);
}

TEST(VectorManipulation, additionInPlace)
{
    Mimp::Vector2<int> v1 = {-1, 1};
    Mimp::Vector2<int> v2 = {2, -6};
    Mimp::Vector2<int> v3 = {1, -5};

    v1 += v2;
    ASSERT_EQ(v1.x, v3.x);
    ASSERT_EQ(v1.y, v3.y);
}

TEST(VectorManipulation, substractionInPlace)
{
    Mimp::Vector2<int> v1 = {-1, 1};
    Mimp::Vector2<int> v2 = {2, -6};
    Mimp::Vector2<int> v3 = {-3, 7};

    v1 -= v2;
    ASSERT_EQ(v1.x, v3.x);
    ASSERT_EQ(v1.y, v3.y);
}

TEST(VectorManipulation, comparison1)
{
    Mimp::Vector2<int> v1 = {-1, 1};
    Mimp::Vector2<int> v2 = {2, -6};

    ASSERT_EQ(v1 == v2, 0);
}

TEST(VectorManipulation, comparison2)
{
    Mimp::Vector2<int> v1 = {-1, 1};
    Mimp::Vector2<int> v2 = {-1, 1};

    ASSERT_EQ(v1 == v2, 1);
}

TEST(VectorManipulation, multiplication)
{
    Mimp::Vector2<int> v1 = {3, -6};
    Mimp::Vector2<int> v3 = {21, -42};

    ASSERT_TRUE(v1 * 7 == v3);
}