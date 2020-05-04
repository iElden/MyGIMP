#include "gtest/gtest.h"
#include "src/Data/Vector2.hpp"

TEST(VectorManipulation, addition1)
{
    Mimp::Vector2<int> v1 = {1, 1};
    Mimp::Vector2<int> v2 = {2, 6};
    Mimp::Vector2<int> v3 = {3, 7};

    ASSERT_EQ((v1 + v2) == v3, 1);
}

TEST(VectorManipulation, addition2)
{
    Mimp::Vector2<int> v1 = {-1, 1};
    Mimp::Vector2<int> v2 = {2, -6};
    Mimp::Vector2<int> v3 = {1, -5};

    ASSERT_EQ((v1 + v2) == v3, 1);
}

TEST(VectorManipulation, substraction1)
{
    Mimp::Vector2<int> v1 = {-1, 1};
    Mimp::Vector2<int> v2 = {2, -6};
    Mimp::Vector2<int> v3 = {-3, 7};

    ASSERT_EQ((v1 - v2) == v3, 1);
}
