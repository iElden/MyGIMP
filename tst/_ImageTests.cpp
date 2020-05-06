//
// Created by jmartin on 4/19/20.
//

#include <gtest/gtest.h>
#include <zconf.h>
#include "../src/Image.hpp"
#include "../src/Data/Vector2.hpp"

TEST(Image, GetSelectedLayerTest)
{
	Mimp::Image image{{400, 400}};
	Mimp::Vector2<unsigned> expected{400, 400};
    auto size = image.getSelectedLayer().getSize();

	ASSERT_EQ(size == expected, 1);
}
