#include <gtest/gtest.h>
#include <TGUI/TGUI.hpp>
#include "../../src/Tools/Move.hpp"

TEST(Move, getPanel) {
    Mimp::Move m{};

    ASSERT_TRUE(m.getParametersPanel()->getSize().x == 0);
    ASSERT_TRUE(m.getParametersPanel()->getSize().y == 0);
}

TEST(Move, click) {
    Mimp::LayerManager lm{Mimp::Vector2<unsigned int>{10, 10}};
    Mimp::Image i{{10, 10}, lm};
    Mimp::Move m{};

    ASSERT_EQ(i.getSelectedLayer().pos.x, 0);
    ASSERT_EQ(i.getSelectedLayer().pos.y, 0);

	m.onClick({4, 6}, Mimp::MIMP_LEFT_CLICK, i);

    ASSERT_EQ(i.getSelectedLayer().pos.x, 0);
    ASSERT_EQ(i.getSelectedLayer().pos.y, 0);
}

TEST(Move, dragOnLeft) {
    Mimp::LayerManager lm{Mimp::Vector2<unsigned int>{10, 10}};
    Mimp::Image i{{10, 10}, lm};
    Mimp::Move m{};

    ASSERT_EQ(i.getSelectedLayer().pos.x, 0);
    ASSERT_EQ(i.getSelectedLayer().pos.y, 0);

	m.onMouseDrag({4, 6}, {2, 6}, Mimp::MIMP_LEFT_CLICK, i);

    ASSERT_EQ(i.getSelectedLayer().pos.x, -2);
    ASSERT_EQ(i.getSelectedLayer().pos.y, 0);
}

TEST(Move, dragOnRight) {
    Mimp::LayerManager lm{Mimp::Vector2<unsigned int>{10, 10}};
    Mimp::Image i{{10, 10}, lm};
    Mimp::Move m{};

    ASSERT_EQ(i.getSelectedLayer().pos.x, 0);
    ASSERT_EQ(i.getSelectedLayer().pos.y, 0);

	m.onMouseDrag({4, 6}, {9, 6}, Mimp::MIMP_LEFT_CLICK, i);

    ASSERT_EQ(i.getSelectedLayer().pos.x, 5);
    ASSERT_EQ(i.getSelectedLayer().pos.y, 0);
}


TEST(Move, dragOnUp) {
    Mimp::LayerManager lm{Mimp::Vector2<unsigned int>{10, 10}};
    Mimp::Image i{{10, 10}, lm};
    Mimp::Move m{};

    ASSERT_EQ(i.getSelectedLayer().pos.x, 0);
    ASSERT_EQ(i.getSelectedLayer().pos.y, 0);

	m.onMouseDrag({4, 6}, {4, 1}, Mimp::MIMP_LEFT_CLICK, i);

    ASSERT_EQ(i.getSelectedLayer().pos.x, 0);
    ASSERT_EQ(i.getSelectedLayer().pos.y, -5);
}

TEST(Move, dragOnDown) {
    Mimp::LayerManager lm{Mimp::Vector2<unsigned int>{10, 10}};
    Mimp::Image i{{10, 10}, lm};
    Mimp::Move m{};

    ASSERT_EQ(i.getSelectedLayer().pos.x, 0);
    ASSERT_EQ(i.getSelectedLayer().pos.y, 0);

	m.onMouseDrag({4, 6}, {4, 10}, Mimp::MIMP_LEFT_CLICK, i);

    ASSERT_EQ(i.getSelectedLayer().pos.x, 0);
    ASSERT_EQ(i.getSelectedLayer().pos.y, 4);
}


TEST(Move, dragOnLeftUp) {
    Mimp::LayerManager lm{Mimp::Vector2<unsigned int>{10, 10}};
    Mimp::Image i{{10, 10}, lm};
    Mimp::Move m{};

    ASSERT_EQ(i.getSelectedLayer().pos.x, 0);
    ASSERT_EQ(i.getSelectedLayer().pos.y, 0);

	m.onMouseDrag({4, 6}, {-4, 0}, Mimp::MIMP_LEFT_CLICK, i);

    ASSERT_EQ(i.getSelectedLayer().pos.x, -8);
    ASSERT_EQ(i.getSelectedLayer().pos.y, -6);
}
