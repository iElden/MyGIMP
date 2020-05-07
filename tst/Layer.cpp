#include <gtest/gtest.h>
#include "../src/Layer/Layer.hpp"

TEST(Layer, getSizeTest)
{
    Mimp::Layer layer {{500, 500}, Mimp::Color::Transparent};
    Mimp::Vector2<unsigned> expected{500, 500};

    auto s = layer.getSize();

    ASSERT_EQ(s == expected, 1);
}

TEST(Layer, isLockedTest)
{
    Mimp::Vector2<unsigned> size{500, 500};
    Mimp::Layer layer {size, Mimp::Color::Transparent};

    ASSERT_EQ(layer.isLocked(), false);
}

