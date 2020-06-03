#include <gtest/gtest.h>
#include <TGUI/TGUI.hpp>
#include "../src/Widgets/CanvasWidget.hpp"

TEST(CanvasWidget, zoom) {
    tgui::Gui gui{};
    Mimp::ToolBox tb{gui};
    Mimp::CanvasWidget cw{tb, Mimp::Vector2<unsigned int>{10, 10}};

    ASSERT_EQ(cw.getZoomLevel(), 1.f);

    cw.setZoomLevel(2.6f);
    ASSERT_EQ(cw.getZoomLevel(), 2.6f);
}

TEST(CanvasWidget, edition) {
    tgui::Gui gui{};
    Mimp::ToolBox tb{gui};
    Mimp::CanvasWidget cw{tb, Mimp::Vector2<unsigned int>{10, 10}};

    ASSERT_FALSE(cw.isEdited());

    cw.setEdited();
    ASSERT_TRUE(cw.isEdited());

    cw.setEdited(false);
    ASSERT_FALSE(cw.isEdited());
}

TEST(CanvasWidget, mouseMoveNoClick) {
    tgui::Gui gui{};
    Mimp::ToolBox tb{gui};
    Mimp::CanvasWidget cw{tb, Mimp::Vector2<unsigned int>{10, 10}};

    cw.mouseMoved({9, 4});
    ASSERT_FALSE(cw.isEdited());
}

TEST(CanvasWidget, clone) {
    tgui::Gui gui{};
    Mimp::ToolBox tb{gui};
    Mimp::CanvasWidget cw{tb, Mimp::Vector2<unsigned>{10, 10}};

    auto clone = cw.clone();
    ASSERT_TRUE(clone->getSize().x == 10);
    ASSERT_TRUE(clone->getSize().y == 10);
    ASSERT_TRUE(clone->isVisible());
}