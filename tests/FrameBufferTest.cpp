//
// Created by jmartin on 4/20/20.
//

#include <criterion/criterion.h>
#include <criterion/redirect.h>
#include <zconf.h>
#include "../src/Layer/FrameBuffer.hpp"

Test(FrameBuffer, GetBufferTest)
{
	Mimp::Vector2<unsigned> size{500, 500};
	Mimp::FrameBuffer fb{size, Mimp::Color::Cyan};

	const unsigned int *buffer = fb.getBuffer();
	for (int i = 0; i < size.x * size.y; i++)
	{
		cr_assert_eq(buffer[i], Mimp::Color::Cyan);
	}
}

Test(FrameBuffer, GetPixelTest)
{
	Mimp::Vector2<unsigned> size{500, 500};
	Mimp::FrameBuffer fb{size, Mimp::Color::Cyan};
	Mimp::Vector2<int> pos{378, 321};

	cr_assert_eq(fb.getPixel(pos), Mimp::Color::Cyan);
}

Test(FrameBuffer, GetPixelTest2)
{
	Mimp::Vector2<unsigned> size{500, 500};
	Mimp::FrameBuffer fb{size, Mimp::Color::Cyan};
	Mimp::Vector2<int> pos{750, 321};

	cr_assert_eq(fb.getPixel(pos), Mimp::Color::Transparent);
}

Test(FrameBuffer, GetSizeTest)
{
	Mimp::Vector2<unsigned> size{500, 500};
	Mimp::FrameBuffer fb{size, Mimp::Color::Cyan};
	Mimp::Vector2<unsigned> expected{500, 500};

	cr_assert_eq(fb.getSize(), expected);
}

Test(FrameBuffer, PosIsOutOfBoundTest)
{
	Mimp::Vector2<unsigned> size{500, 500};
	Mimp::FrameBuffer fb{size, Mimp::Color::Cyan};
	Mimp::Vector2<int> out{500, 500};
	Mimp::Vector2<int> out2{-1, 0};
	Mimp::Vector2<int> out3{0, -1};
	Mimp::Vector2<int> in{25, 356};

	cr_assert_eq(fb.posIsOutOfBound(out), true);
	cr_assert_eq(fb.posIsOutOfBound(out2), true);
	cr_assert_eq(fb.posIsOutOfBound(out3), true);
	cr_assert_eq(fb.posIsOutOfBound(in), false);
}

Test(FrameBuffer, getRectFromBufferTest)
{
	Mimp::Vector2<unsigned> size{500, 500};
	Mimp::FrameBuffer fb{size, Mimp::Color::Cyan};
	Mimp::Vector2<int> pos {-1, 10};
	Mimp::Vector2<unsigned> sizeTested {30, 30};

	Mimp::FrameBuffer testedFb = fb.getRectFromBuffer(pos, sizeTested);
	const unsigned *buf = testedFb.getBuffer();
	for (int i = 0; i < sizeTested.x * sizeTested.y; i++) {
		if (i % 30 == 0) {
			cr_assert_eq(buf[i], Mimp::Color::Transparent);
		} else {
			cr_assert_eq(buf[i], Mimp::Color::Cyan);
		}
	}
}