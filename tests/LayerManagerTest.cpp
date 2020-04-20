//
// Created by jmartin on 4/20/20.
//

#include <criterion/criterion.h>
#include <criterion/redirect.h>
#include <zconf.h>
#include "../src/Layer/LayerManager.hpp"
#include "../src/Data/Vector2.hpp"

Test(LayerManager, GetSizeTest)
{
	Mimp::Vector2<unsigned> size{500, 500};
	Mimp::LayerManager lm{size};
	Mimp::Vector2<unsigned> expected{500, 500};

	cr_assert_eq(lm.getSize(), expected);
}
