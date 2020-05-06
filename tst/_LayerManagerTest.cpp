//
// Created by jmartin on 4/20/20.
//

#include <gtest/gtest.h>
#include <zconf.h>
#include "../src/Layer/LayerManager.hpp"
#include "../src/Data/Vector2.hpp"

TEST(LayerManager, GetSizeTest)
{
	Mimp::Vector2<unsigned> size{500, 500};
	Mimp::LayerManager lm{size};
	Mimp::Vector2<unsigned> expected{500, 500};
    auto s = lm.getSize();

	ASSERT_EQ(s == expected, 1);
}
