#include <gtest/gtest.h>
#include "../src/Data/Color.hpp"

TEST(ColorManipulation, basicColors) {
    Mimp::Color black = Mimp::Color::Black;

    ASSERT_EQ(black.r, 0x00);
    ASSERT_EQ(black.g, 0x00);
    ASSERT_EQ(black.b, 0x00);
    ASSERT_EQ(black.a, 0xFF);

    Mimp::Color r = Mimp::Color::Red;

    ASSERT_EQ(r.r, 0xFF);
    ASSERT_EQ(r.g, 0x00);
    ASSERT_EQ(r.b, 0x00);
    ASSERT_EQ(r.a, 0xFF);

    Mimp::Color g = Mimp::Color::Green;

    ASSERT_EQ(g.r, 0x00);
    ASSERT_EQ(g.g, 0xFF);
    ASSERT_EQ(g.b, 0x00);
    ASSERT_EQ(g.a, 0xFF);

    Mimp::Color b = Mimp::Color::Blue;

    ASSERT_EQ(b.r, 0x00);
    ASSERT_EQ(b.g, 0x00);
    ASSERT_EQ(b.b, 0xFF);
    ASSERT_EQ(b.a, 0xFF);
}

TEST(ColorManipulation, addition) {
    Mimp::Color c1 = Mimp::Color::Blue;
    Mimp::Color c2 = Mimp::Color::Green;
    Mimp::Color c3 = Mimp::Color::Yellow;

    auto c4 = c1 + c2;
    ASSERT_EQ(c4.r, c3.r);
    ASSERT_EQ(c4.g, c3.g);
    ASSERT_EQ(c4.b, c3.b);
    ASSERT_EQ(c4.a, c3.a);

}
