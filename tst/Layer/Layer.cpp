#include <gtest/gtest.h>
#include "../../src/Layer/Layer.hpp"

TEST(Layer, getSizeTest) {
    Mimp::Layer layer{{500, 500}, Mimp::Color::Transparent};
    Mimp::Vector2<unsigned> expected{500, 500};

    auto s = layer.getSize();

    ASSERT_EQ(s == expected, 1);
}

TEST(Layer, isLockedTest) {
    Mimp::Vector2<unsigned> size{500, 500};
    Mimp::Layer layer{size, Mimp::Color::Transparent};

    ASSERT_EQ(layer.isLocked(), false);
}

TEST(Layer, layerWithBuffer) {
    const Mimp::Color buffer[100] = {Mimp::Color::Green};
    Mimp::Layer layer({10, 10}, buffer);

    ASSERT_EQ(layer.buffer->getBuffer()[0], buffer[0]);
}

