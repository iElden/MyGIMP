#include <gtest/gtest.h>
#include "../../src/Layer/FrameBuffer.hpp"
#include "../../src/Exceptions.hpp"

TEST(FrameBuffer, getBufferTest) {
    Mimp::Vector2<unsigned> size{500, 500};
    Mimp::FrameBuffer fb{size, Mimp::Color::Cyan};

    auto buffer = fb.getBuffer();
    for (unsigned int i = 0; i < size.x * size.y; i++) {
        ASSERT_EQ(buffer[i], Mimp::Color::Cyan);
    }
}

TEST(FrameBuffer, getPixelTest) {
    Mimp::Vector2<unsigned> size{500, 500};
    Mimp::FrameBuffer fb{size, Mimp::Color::Cyan};
    Mimp::Vector2<int> pos{378, 321};

    ASSERT_EQ(fb.getPixel(pos), Mimp::Color::Cyan);
}

TEST(FrameBuffer, getPixelTest2) {
    Mimp::Vector2<unsigned> size{500, 500};
    Mimp::FrameBuffer fb{size, Mimp::Color::Cyan};
    Mimp::Vector2<int> pos{750, 321};

    ASSERT_EQ(fb.getPixel(pos), Mimp::Color::Transparent);
}

TEST(FrameBuffer, getSizeTest) {
    Mimp::Vector2<unsigned> size{500, 500};
    Mimp::FrameBuffer fb{size, Mimp::Color::Cyan};
    Mimp::Vector2<unsigned> expected{500, 500};

    ASSERT_EQ(fb.getSize() == expected, 1);
}

TEST(FrameBuffer, posIsOutOfBoundTest) {
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

TEST(FrameBuffer, getRectFromBufferTest) {
    Mimp::Vector2<unsigned> size{500, 500};
    Mimp::FrameBuffer fb{size, Mimp::Color::Cyan};
    Mimp::Vector2<int> pos{-1, 10};
    Mimp::Vector2<unsigned> sizeTested{30, 30};

    Mimp::FrameBuffer testedFb = fb.getRectFromBuffer(pos, sizeTested);
    auto buf = testedFb.getBuffer();
    for (unsigned int i = 0; i < sizeTested.x * sizeTested.y; i++) {
        if (i % 30 == 0) {
            ASSERT_EQ(buf[i], Mimp::Color::Transparent);
        } else {
            ASSERT_EQ(buf[i], Mimp::Color::Cyan);
        }
    }
}

TEST(FrameBuffer, framebufferFromOther) {
    Mimp::Vector2<unsigned> size{500, 500};
    Mimp::FrameBuffer fb{size, Mimp::Color::Cyan};

    Mimp::FrameBuffer buffer(fb);
    for (unsigned int i = 0; i < size.x * size.y; i++) {
        ASSERT_EQ(buffer[i], Mimp::Color::Cyan);
    }

}

TEST(FrameBuffer, createFbWithVector) {
    Mimp::Vector2<unsigned> size{10, 10};
    const std::vector<Mimp::Color> c(size.x * size.y, Mimp::Color::Green);
    Mimp::FrameBuffer fb(size, c);
    Mimp::FrameBuffer fb2(size, Mimp::Color::Green);

    for (unsigned int i = 0; i < size.x * size.y; i += 1) {
        ASSERT_EQ(fb[i], Mimp::Color::Green);
    }
}

TEST(FrameBuffer, createFromExisting) {
    Mimp::Vector2<unsigned> size{500, 500};
    const Mimp::FrameBuffer fb{size, Mimp::Color::Cyan};
    Mimp::FrameBuffer fb2{{7, 8}, Mimp::Color::Red};

    fb2 = fb;

    for (unsigned int i = 0; i < size.x * size.y; i += 1) {
        ASSERT_EQ(fb[i], fb2[i]);
    }
}

TEST(FrameBuffer, outOfBoundException) {
    Mimp::Vector2<unsigned> size = {10, 10};
    Mimp::FrameBuffer fb(size, Mimp::Color::Green);

    try {
        auto px = fb[10000];
    } catch (Mimp::OutOfBoundException &e) {
        ASSERT_EQ(std::string(e.what()), "10000 >= 10 * 10");
    }
}

TEST(FrameBuffer, setPixel1) {
    Mimp::Vector2<unsigned> size = {10, 5};
    Mimp::FrameBuffer fb(size, Mimp::Color::Green);
    Mimp::Vector2<int> pos = {5, 4};

    fb.drawPixel(pos, Mimp::Color::Yellow, Mimp::SET);

    for (unsigned int i = 0; i < size.x; i += 1) {
        for (unsigned int j = 0; j < size.y; j += 1) {
            if (i == pos.x && j == pos.y) {
                ASSERT_TRUE(fb[i + size.y * j] == Mimp::Color::Yellow);
            } else {
                ASSERT_TRUE(fb[i + size.y * j] == Mimp::Color::Green);
            }
        }
    }
}

TEST(FrameBuffer, setPixel2) {
    Mimp::Vector2<unsigned> size = {10, 10};
    Mimp::FrameBuffer fb(size, Mimp::Color::Green);
    Mimp::Vector2<int> pos = {13, 5};

    fb.setPixel(pos, Mimp::Color::Yellow);

    for (unsigned int i = 0; i < size.x * size.y; i += 1) {
        ASSERT_EQ(fb[i], Mimp::Color::Green);
    }
}

TEST(FrameBuffer, OutOfBoundPixel) {
    Mimp::Vector2<unsigned> size = {10, 10};
    Mimp::FrameBuffer fb(size, Mimp::Color::Green);
    Mimp::Vector2<int> pos1 = {-2, 6};
    Mimp::Vector2<int> pos2 = {4, -8};

    ASSERT_TRUE(fb.posIsOutOfBound(pos1));
    ASSERT_TRUE(fb.posIsOutOfBound(pos2));
}

TEST(FrameBuffer, clearFb) {
    Mimp::Vector2<unsigned> size = {10, 10};
    Mimp::FrameBuffer fb(size, Mimp::Color::Green);

    for (unsigned int i = 0; i < size.x * size.y; i += 1) {
        ASSERT_EQ(fb[i], Mimp::Color::Green);
    }
    fb.clear(Mimp::Color::Yellow);
    for (unsigned int i = 0; i < size.x * size.y; i += 1) {
        ASSERT_EQ(fb[i], Mimp::Color::Yellow);
    }
}

TEST(FrameBuffer, drawSquare) {
    Mimp::Vector2<unsigned> size = {10, 10};
    Mimp::FrameBuffer fb(size, Mimp::Color::Green);

    Mimp::Vector2<int> pos = {5, 5};
    unsigned short radius = 4;

    fb.drawAt(pos, Mimp::Color::Yellow, radius, Mimp::SQUARE);

    unsigned int xmin = pos.x - (radius / 2);
    unsigned int xmax = pos.x + (radius / 2);
    unsigned int ymin = pos.y - (radius / 2);
    unsigned int ymax = pos.y + (radius / 2);

    for (unsigned int i = 0; i < size.x; i += 1) {
        for (unsigned int j = 0; j < size.y; j += 1) {
            if (i >= xmin && i < xmax &&
                j >= ymin && j < ymax) {
                ASSERT_TRUE(fb[i + size.x * j] == Mimp::Color::Yellow);
            } else {
                ASSERT_TRUE(fb[i + size.x * j] == Mimp::Color::Green);
            }
        }
    }
}

TEST(FrameBuffer, drawCircle) {
    Mimp::Vector2<unsigned> size = {10, 10};
    Mimp::FrameBuffer fb(size, Mimp::Color::Green);

    Mimp::Vector2<int> pos = {5, 5};
    unsigned short radius = 4;

    ASSERT_TRUE(0);
    fb.drawAt(pos, Mimp::Color::Yellow, radius, Mimp::CIRCLE);

}

TEST(FrameBuffer, drawDiamond) {
    Mimp::Vector2<unsigned> size = {10, 10};
    Mimp::FrameBuffer fb(size, Mimp::Color::Green);

    Mimp::Vector2<int> pos = {5, 5};
    unsigned short radius = 4;

    ASSERT_TRUE(0);
    fb.drawAt(pos, Mimp::Color::Yellow, radius, Mimp::DIAMOND);

}

TEST(FrameBuffer, drawNoShape) {
    Mimp::Vector2<unsigned> size = {10, 10};
    Mimp::FrameBuffer fb(size, Mimp::Color::Green);

    Mimp::Vector2<int> pos = {5, 5};
    unsigned short radius = 4;

    fb.drawAt(pos, Mimp::Color::Yellow, radius, Mimp::NB_OF_SHAPES);

    for (unsigned int i = 0; i < size.x * size.y; i += 1) {
        ASSERT_EQ(fb[i], Mimp::Color::Green);
    }
}

TEST(FrameBuffer, getDrawBuffer) {
    Mimp::FrameBuffer fb{{10, 10}, Mimp::Color::Red};
    auto buffer = fb.getDrawBuffer();

    for (int i = 0; i < 400; i += 4) {
        ASSERT_EQ(buffer[i + 0], 0xFF);
        ASSERT_EQ(buffer[i + 1], 0x00);
        ASSERT_EQ(buffer[i + 2], 0x00);
        ASSERT_EQ(buffer[i + 3], 0xFF);
    }
}