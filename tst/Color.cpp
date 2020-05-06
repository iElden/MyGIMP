#include <gtest/gtest.h>
#include "../src/Data/Color.hpp"

TEST(ColorManipulation, addition1)
{
    Mimp::Color c = Mimp::Color::Black;

    ASSERT_EQ(c.r, 0);
    ASSERT_EQ(c.g, 0);
    ASSERT_EQ(c.b, 0);
}
