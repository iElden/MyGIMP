#include <gtest/gtest.h>
#include "../../src/Layer/FrameBuffer.hpp"
#include "../../src/Exceptions.hpp"

#define UINT(x) (static_cast<unsigned>(x))

TEST(FrameBuffer, getBuffer) {
    Mimp::Vector2<unsigned> size{500, 500};
    Mimp::FrameBuffer fb{size, Mimp::Color::Cyan};

    auto buffer = fb.getBuffer();
    for (unsigned int i = 0; i < size.x * size.y; i++) {
        ASSERT_EQ(buffer[i], Mimp::Color::Cyan);
    }
}

TEST(FrameBuffer, getPixel) {
    Mimp::Vector2<unsigned> size{500, 500};
    Mimp::FrameBuffer fb{size, Mimp::Color::Cyan};
    Mimp::Vector2<int> pos{378, 321};

    ASSERT_EQ(fb.getPixel(pos), Mimp::Color::Cyan);
}

TEST(FrameBuffer, getPixelOutOfBound) {
    Mimp::Vector2<unsigned> size{500, 500};
    Mimp::FrameBuffer fb{size, Mimp::Color::Cyan};
    Mimp::Vector2<int> pos{750, 321};

    ASSERT_EQ(fb.getPixel(pos), Mimp::Color::Transparent);
}

TEST(FrameBuffer, getSize) {
    Mimp::Vector2<unsigned> size{500, 500};
    Mimp::FrameBuffer fb{size, Mimp::Color::Cyan};
    Mimp::Vector2<unsigned> expected{500, 500};

    ASSERT_EQ(fb.getSize() == expected, 1);
}

TEST(FrameBuffer, posIsOutOfBound) {
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

TEST(FrameBuffer, getRectFromBuffer) {
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
        [[maybe_unused]] auto px = fb[10000];
    } catch (Mimp::OutOfBoundException &e) {
        ASSERT_EQ(std::string(e.what()), "10000 >= 10 * 10");
    }
}

TEST(FrameBuffer, setPixelInsideBounds) {
    Mimp::Vector2<unsigned> size = {10, 5};
    Mimp::FrameBuffer fb(size, Mimp::Color::Green);
    Mimp::Vector2<int> pos = {5, 4};

    fb.drawPixel(pos, Mimp::Color::Yellow, Mimp::SET);

    for (unsigned int i = 0; i < size.y; i += 1) {
        for (unsigned int j = 0; j < size.x; j += 1) {
            if (i == UINT(pos.y) && j == UINT(pos.x)) {
                ASSERT_TRUE(fb[i * size.x + j] == Mimp::Color::Yellow);
            } else {
                ASSERT_TRUE(fb[i * size.x + j] == Mimp::Color::Green);
            }
        }
    }
}

TEST(FrameBuffer, setPixelOutOfBounds) {
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

TEST(FrameBuffer, clearFrameBuffer) {
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

TEST(FrameBuffer, drawSquareRadius4) {
    Mimp::Vector2<unsigned> size = {10, 10};
    Mimp::FrameBuffer fb(size, Mimp::Color::Green);

    Mimp::Vector2<int> pos = {5, 4};
    unsigned short radius = 4;

    fb.drawAt(pos, Mimp::Color::Yellow, radius, Mimp::SQUARE);

    auto buffer = fb.getBuffer();
    std::stringstream output;
    std::string correct =
            "0000000000"
            "0000000000"
            "0001111000"
            "0001111000"
            "0001111000"
            "0001111000"
            "0000000000"
            "0000000000"
            "0000000000"
            "0000000000";

    for (int i = 0; i < 100; i += 1) {
        output << (buffer[i] == Mimp::Color::Yellow);
    }

    ASSERT_EQ(output.str(), correct);
}

TEST(FrameBuffer, drawCircleRadisu9) {
    Mimp::Vector2<unsigned> size = {10, 10};
    Mimp::FrameBuffer fb(size, Mimp::Color::Green);

    Mimp::Vector2<int> pos = {5, 5};
    unsigned short radius = 9;

    fb.drawAt(pos, Mimp::Color::Yellow, radius, Mimp::CIRCLE);

    auto buffer = fb.getBuffer();
    std::stringstream output;
    std::string correct =
            "0000000000"
            "0000000000"
            "0001111110"
            "0011111111"
            "0011111111"
            "0011111111"
            "0011111111"
            "0011111111"
            "0011111111"
            "0001111110";

    for (int i = 0; i < 100; i += 1) {
        output << (buffer[i] == Mimp::Color::Yellow);
    }

    ASSERT_EQ(output.str(), correct);
}

TEST(FrameBuffer, drawCircleRadius1) {
    Mimp::Vector2<unsigned> size = {10, 10};
    Mimp::FrameBuffer fb(size, Mimp::Color::Green);

    Mimp::Vector2<int> pos = {5, 5};
    unsigned short radius = 1;

    fb.drawAt(pos, Mimp::Color::Yellow, radius, Mimp::CIRCLE);

    auto buffer = fb.getBuffer();
    std::stringstream output;
    std::string correct =
            "0000000000"
            "0000000000"
            "0000000000"
            "0000000000"
            "0000000000"
            "0000010000"
            "0000000000"
            "0000000000"
            "0000000000"
            "0000000000";

    for (int i = 0; i < 100; i += 1) {
        output << (buffer[i] == Mimp::Color::Yellow);
    }

    ASSERT_EQ(output.str(), correct);
}

TEST(FrameBuffer, drawDiamondRadius9) {
    Mimp::Vector2<unsigned> size = {10, 10};
    Mimp::FrameBuffer fb(size, Mimp::Color::Green);

    Mimp::Vector2<int> pos = {5, 5};
    unsigned short radius = 9;

    fb.drawAt(pos, Mimp::Color::Yellow, radius, Mimp::DIAMOND);

    auto buffer = fb.getBuffer();
    std::stringstream output;
    std::string correct =
            "0000000000"
            "0000000000"
            "0000010000"
            "0000111000"
            "0001111100"
            "0011111110"
            "0001111100"
            "0000111000"
            "0000010000"
            "0000000000";

    for (int i = 0; i < 100; i += 1) {
        output << (buffer[i] == Mimp::Color::Yellow);
    }

    ASSERT_EQ(output.str(), correct);
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

TEST(FrameBuffer, drawVerticalLine) {
    Mimp::FrameBuffer fb{{10, 10}, Mimp::Color::Red};

    fb.drawLine({2, 3}, {2, 10}, Mimp::Color::Green, 1);

    auto buffer = fb.getBuffer();
    std::stringstream output;
    std::string correct =
            "0000000000"
            "0000000000"
            "0000000000"
            "0010000000"
            "0010000000"
            "0010000000"
            "0010000000"
            "0010000000"
            "0010000000"
            "0010000000";

    for (int i = 0; i < 100; i += 1) {
        output << (buffer[i] == Mimp::Color::Green);
    }

    ASSERT_EQ(output.str(), correct);
}

TEST(FrameBuffer, drawHorizontalLine) {
    Mimp::FrameBuffer fb{{10, 10}, Mimp::Color::Red};

    fb.drawLine({2, 3}, {8, 3}, Mimp::Color::Green, 1);

    auto buffer = fb.getBuffer();
    std::stringstream output;
    std::string correct =
            "0000000000"
            "0000000000"
            "0000000000"
            "0011111110"
            "0000000000"
            "0000000000"
            "0000000000"
            "0000000000"
            "0000000000"
            "0000000000";

    for (int i = 0; i < 100; i += 1) {
        output << (buffer[i] == Mimp::Color::Green);
    }

    ASSERT_EQ(output.str(), correct);
}

TEST(FrameBuffer, line1) {
    Mimp::FrameBuffer fb{{10, 10}, Mimp::Color::Red};

    fb.drawLine({3, 8}, {8, 2}, Mimp::Color::Green, 1);

    auto buffer = fb.getBuffer();
    std::stringstream output;
    std::string correct =
            "0000000000"
            "0000000000"
            "0000000010"
            "0000000100"
            "0000001000"
            "0000010000"
            "0000010000"
            "0000100000"
            "0001000000"
            "0000000000";

    for (int i = 0; i < 100; i += 1) {
        output << (buffer[i] == Mimp::Color::Green);
    }

    ASSERT_EQ(output.str(), correct);
}

TEST(FrameBuffer, line2) {
    Mimp::FrameBuffer fb{{10, 10}, Mimp::Color::Red};

    fb.drawLine({1, 2}, {7, 8}, Mimp::Color::Green, 1);

    auto buffer = fb.getBuffer();
    std::stringstream output;
    std::string correct =
            "0000000000"
            "0000000000"
            "0100000000"
            "0010000000"
            "0001000000"
            "0000100000"
            "0000010000"
            "0000001000"
            "0000000100"
            "0000000000";

    for (int i = 0; i < 100; i += 1) {
        output << (buffer[i] == Mimp::Color::Green);
    }

    ASSERT_EQ(output.str(), correct);
}

TEST(FrameBuffer, line3) {
    Mimp::FrameBuffer fb{{10, 10}, Mimp::Color::Red};

    fb.drawLine({1, 2}, {3, 8}, Mimp::Color::Green, 1);

    auto buffer = fb.getBuffer();
    std::stringstream output;
    std::string correct =
            "0000000000"
            "0000000000"
            "0100000000"
            "0100000000"
            "0010000000"
            "0010000000"
            "0010000000"
            "0001000000"
            "0001000000"
            "0000000000";

    for (int i = 0; i < 100; i += 1) {
        output << (buffer[i] == Mimp::Color::Green);
    }

    ASSERT_EQ(output.str(), correct);
}

TEST(FrameBuffer, line4) {
    Mimp::FrameBuffer fb{{10, 10}, Mimp::Color::Red};

    fb.drawLine({1, 8}, {9, 2}, Mimp::Color::Green, 1);

    auto buffer = fb.getBuffer();
    std::stringstream output;
    std::string correct =
            "0000000000"
            "0000000000"
            "0000000001"
            "0000000010"
            "0000001100"
            "0000010000"
            "0000100000"
            "0011000000"
            "0100000000"
            "0000000000";

    for (int i = 0; i < 100; i += 1) {
        output << (buffer[i] == Mimp::Color::Green);
    }

    ASSERT_EQ(output.str(), correct);
}

TEST(FrameBuffer, line5) {
    Mimp::FrameBuffer fb{{10, 10}, Mimp::Color::Red};

    fb.drawLine({9, 2}, {1, 8}, Mimp::Color::Green, 1);

    auto buffer = fb.getBuffer();
    std::stringstream output;
    std::string correct =
            "0000000000"
            "0000000000"
            "0000000001"
            "0000000010"
            "0000001100"
            "0000010000"
            "0000100000"
            "0011000000"
            "0100000000"
            "0000000000";

    for (int i = 0; i < 100; i += 1) {
        output << (buffer[i] == Mimp::Color::Green);
    }

    ASSERT_EQ(output.str(), correct);
}

TEST(FrameBuffer, line6) {
    Mimp::FrameBuffer fb{{10, 10}, Mimp::Color::Red};

    fb.drawLine({9, 8}, {1, 2}, Mimp::Color::Green, 1);

    auto buffer = fb.getBuffer();
    std::stringstream output;
    std::string correct =
            "0000000000"
            "0000000000"
            "0100000000"
            "0011000000"
            "0000100000"
            "0000010000"
            "0000001100"
            "0000000010"
            "0000000001"
            "0000000000";

    for (int i = 0; i < 100; i += 1) {
        output << (buffer[i] == Mimp::Color::Green);
    }

    ASSERT_EQ(output.str(), correct);
}

TEST(FrameBuffer, line7) {
    Mimp::FrameBuffer fb{{10, 10}, Mimp::Color::Red};

    fb.drawLine({6, 2}, {1, 8}, Mimp::Color::Green, 1);

    auto buffer = fb.getBuffer();
    std::stringstream output;
    std::string correct =
            "0000000000"
            "0000000000"
            "0000001000"
            "0000010000"
            "0000100000"
            "0001000000"
            "0001000000"
            "0010000000"
            "0100000000"
            "0000000000";

    for (int i = 0; i < 100; i += 1) {
        output << (buffer[i] == Mimp::Color::Green);
    }

    ASSERT_EQ(output.str(), correct);
}

TEST(FrameBuffer, line8) {
    Mimp::FrameBuffer fb{{10, 10}, Mimp::Color::Red};

    fb.drawLine({6, 8}, {1, 1}, Mimp::Color::Green, 1);

    auto buffer = fb.getBuffer();
    std::stringstream output;
    std::string correct =
            "0000000000"
            "0100000000"
            "0010000000"
            "0010000000"
            "0001000000"
            "0000100000"
            "0000010000"
            "0000010000"
            "0000001000"
            "0000000000";

    for (int i = 0; i < 100; i += 1) {
        output << (buffer[i] == Mimp::Color::Green);
    }

    ASSERT_EQ(output.str(), correct);
}

TEST(FrameBuffer, line9) {
    Mimp::FrameBuffer fb{{10, 10}, Mimp::Color::Red};

    fb.drawLine({6, 5}, {1, 5}, Mimp::Color::Green, 1);

    auto buffer = fb.getBuffer();
    std::stringstream output;
    std::string correct =
            "0000000000"
            "0000000000"
            "0000000000"
            "0000000000"
            "0000000000"
            "0111111000"
            "0000000000"
            "0000000000"
            "0000000000"
            "0000000000";

    for (int i = 0; i < 100; i += 1) {
        output << (buffer[i] == Mimp::Color::Green);
    }

    ASSERT_EQ(output.str(), correct);
}

TEST(FrameBuffer, line10) {
    Mimp::FrameBuffer fb{{10, 10}, Mimp::Color::Red};

    fb.drawLine({6, 5}, {6, -1}, Mimp::Color::Green, 1);

    auto buffer = fb.getBuffer();
    std::stringstream output;
    std::string correct =
            "0000001000"
            "0000001000"
            "0000001000"
            "0000001000"
            "0000001000"
            "0000001000"
            "0000001000"
            "0000000000"
            "0000000000"
            "0000000000";

    for (int i = 0; i < 100; i += 1) {
        output << (buffer[i] == Mimp::Color::Green);
    }

    ASSERT_EQ(output.str(), correct);
}