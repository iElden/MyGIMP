//
// Created by jmartin on 4/20/20.
//

#include <criterion/criterion.h>
#include <criterion/redirect.h>
#include <zconf.h>
#include "../src/Layer/Layer.hpp"
#include "../src/Data/Vector2.hpp"

Test(Layer, GetSizeTest)
{
	Mimp::Vector2<unsigned> size{500, 500};
	Mimp::Layer layer {size, Mimp::Color::Transparent};
	Mimp::Vector2<unsigned> expected{500, 500};

	cr_assert_eq(layer.getSize(), expected);
}

Test(Layer, IsLockedTest)
{
	Mimp::Vector2<unsigned> size{500, 500};
	Mimp::Layer layer {size, Mimp::Color::Transparent};

	cr_assert_eq(layer.isLocked(), false);
}