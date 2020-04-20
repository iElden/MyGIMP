//
// Created by jmartin on 4/19/20.
//

#include <criterion/criterion.h>
#include <criterion/redirect.h>
#include <zconf.h>
#include "../src/Image.hpp"
#include "../src/Data/Vector2.hpp"

Test(Image, GetSelectedLayerTest)
{
	Mimp::Image image{{400, 400}};
	Mimp::Vector2<unsigned> expected{400, 400};

	cr_assert_eq(image.getSelectedLayer().getSize(), expected);
}
