#include <gtest/gtest.h>
#include "../src/Layer/FrameBuffer.hpp"

TEST(FrameBuffer, getBufferTest)
{
    Mimp::Vector2<unsigned> size{500, 500};
    Mimp::FrameBuffer fb{size, Mimp::Color::Cyan};

    auto buffer = fb.getBuffer();
    for (int i = 0; i < size.x * size.y; i++) {
        ASSERT_EQ(buffer[i], Mimp::Color::Cyan);
    }
}

TEST(FrameBuffer, getPixelTest)
{
    Mimp::Vector2<unsigned> size{500, 500};
    Mimp::FrameBuffer fb{size, Mimp::Color::Cyan};
    Mimp::Vector2<int> pos{378, 321};

    ASSERT_EQ(fb.getPixel(pos), Mimp::Color::Cyan);
}

TEST(FrameBuffer, getPixelTest2)
{
    Mimp::Vector2<unsigned> size{500, 500};
    Mimp::FrameBuffer fb{size, Mimp::Color::Cyan};
    Mimp::Vector2<int> pos{750, 321};

    ASSERT_EQ(fb.getPixel(pos), Mimp::Color::Transparent);
}

TEST(FrameBuffer, getSizeTest)
{
    Mimp::Vector2<unsigned> size{500, 500};
    Mimp::FrameBuffer fb{size, Mimp::Color::Cyan};
    Mimp::Vector2<unsigned> expected{500, 500};

    ASSERT_EQ(fb.getSize() == expected, 1);
}

TEST(FrameBuffer, posIsOutOfBoundTest)
{
    Mimp::Vector2<unsigned> size{500, 500};
    Mimp::FrameBuffer fb{size, Mimp::Color::Cyan};
    Mimp::Vector2<int> out{500, 500};
    Mimp::Vector2<int> out2{-1, 0};
    Mimp::Vector2<int> out3{0, -1};
    Mimp::Vector2<int> in{25, 356};

    ASSERT_EQ(fb.posIsOutOfBound(out), true);
    ASSERT_EQ(fb.posIsOutOfBound(out2), true);
    ASSERT_EQ(fb.posIsOutOfBound(out3), true);
    ASSERT_EQ(fb.posIsOutOfBound(in), false);
}

TEST(FrameBuffer, getRectFromBufferTest)
{
    Mimp::Vector2<unsigned> size{500, 500};
    Mimp::FrameBuffer fb{size, Mimp::Color::Cyan};
    Mimp::Vector2<int> pos {-1, 10};
    Mimp::Vector2<unsigned> sizeTested {30, 30};

    Mimp::FrameBuffer testedFb = fb.getRectFromBuffer(pos, sizeTested);
    auto buf = testedFb.getBuffer();
    for (int i = 0; i < sizeTested.x * sizeTested.y; i++) {
        if (i % 30 == 0) {
            ASSERT_EQ(buf[i], Mimp::Color::Transparent);
        } else {
            ASSERT_EQ(buf[i], Mimp::Color::Cyan);
        }
    }
}

TEST(FrameBuffer, framebufferFromOther)
{
    Mimp::Vector2<unsigned> size{500, 500};
    Mimp::FrameBuffer fb{size, Mimp::Color::Cyan};

    Mimp::FrameBuffer buffer(fb);
    for (int i = 0; i < size.x * size.y; i++) {
        ASSERT_EQ(buffer[i], Mimp::Color::Cyan);
    }
}

