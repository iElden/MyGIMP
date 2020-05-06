//
// Created by jmartin on 4/20/20.
//

#include "gtest/gtest.h"
#include <zconf.h>
#include "src/Layer/Layer.hpp"
#include "src/Data/Vector2.hpp"

TEST(Layer, GetSizeTest)
{
	Mimp::Vector2<unsigned> size{500, 500};
	Mimp::Layer layer {size, Mimp::Color::Transparent};
	Mimp::Vector2<unsigned> expected{500, 500};

    auto s = layer.getSize();

	ASSERT_EQ(s == expected, 1);
}

TEST(Layer, IsLockedTest)
{
	Mimp::Vector2<unsigned> size{500, 500};
	Mimp::Layer layer {size, Mimp::Color::Transparent};

	ASSERT_EQ(layer.isLocked(), false);
}
