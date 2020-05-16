#include <gtest/gtest.h>
#include <TGUI/TGUI.hpp>
#include "../../src/Tools/RectSelectTool.hpp"

TEST(RectSelectTool, getPanel) {
    tgui::Gui gui{};
    Mimp::ToolBox toolbox{gui};
    Mimp::RectSelectTool rst{toolbox};

    ASSERT_TRUE(rst.getParametersPanel()->getSize().x == 0);
    ASSERT_TRUE(rst.getParametersPanel()->getSize().y == 0);
}

TEST(RectSelectTool, selectOnlyAPixel) {
    tgui::Gui gui{};
    Mimp::ToolBox toolbox{gui};
    Mimp::RectSelectTool rst{toolbox};
    Mimp::LayerManager lm({10, 10}, 1, Mimp::Color::Red);
    Mimp::Image image({10, 10}, lm);

    rst.onClick({4, 6}, Mimp::MIMP_LEFT_CLICK, image);

    ASSERT_TRUE(image.selectedArea.pointInMap({4, 6}));
}

TEST(RectSelectTool, selectOnDrag) {
    tgui::Gui gui{};
    Mimp::ToolBox toolbox{gui};
    Mimp::RectSelectTool rst{toolbox};
    Mimp::LayerManager lm({10, 10}, 1, Mimp::Color::Red);
    Mimp::Image image({10, 10}, lm);

    rst.onMouseDrag({0, 0}, {4, 7}, Mimp::MIMP_LEFT_CLICK, image);

    ASSERT_TRUE(image.selectedArea.pointInMap({4, 6}));
    ASSERT_TRUE(image.selectedArea.pointInMap({0, 7}));
    ASSERT_FALSE(image.selectedArea.pointInMap({5, 7}));
    ASSERT_FALSE(image.selectedArea.pointInMap({11, 3}));
}

/*
TEST(RectSelectTool, DUMMY) {
    tgui::Gui gui{};
    Mimp::ToolBox toolbox{gui};
    Mimp::RectSelectTool rst{toolbox};

    rst.clear();
}
*/