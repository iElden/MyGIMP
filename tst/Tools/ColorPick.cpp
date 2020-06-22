#include <gtest/gtest.h>
#include <TGUI/TGUI.hpp>
#include "../../src/Tools/ColorPick.hpp"

TEST(ColorPick, getPanel) {
    tgui::Gui gui{};
    Mimp::ToolBox toolbox{gui};
    Mimp::ColorPick cp{toolbox};

    ASSERT_TRUE(cp.getParametersPanel()->getSize().x == 0);
    ASSERT_TRUE(cp.getParametersPanel()->getSize().y == 0);
}

TEST(ColorPick, pickImageColor) {
    tgui::Gui gui{};
    Mimp::ToolBox toolbox{gui};
    Mimp::ColorPick cp{toolbox};
    Mimp::LayerManager lm({10, 10}, 1, Mimp::Color::Magenta);
    Mimp::Image image({10, 10}, lm);

    ASSERT_TRUE(toolbox.getSelectedColor(Mimp::MIMP_LEFT_CLICK) == Mimp::Color::Black);
	cp.onClick({5, 5}, Mimp::MIMP_LEFT_CLICK, image);
    ASSERT_TRUE(toolbox.getSelectedColor(Mimp::MIMP_LEFT_CLICK) == Mimp::Color::Magenta);
}

TEST(ColorPick, pickColorOnDrag) {
    tgui::Gui gui{};
    Mimp::ToolBox toolbox{gui};
    Mimp::ColorPick cp{toolbox};
    Mimp::LayerManager lm({10, 10}, 1, Mimp::Color::Magenta);
    Mimp::Image image({10, 10}, lm);

    ASSERT_TRUE(toolbox.getSelectedColor(Mimp::MIMP_LEFT_CLICK) == Mimp::Color::Black);
	cp.onMouseDrag({0, 0}, {10, 10}, Mimp::MIMP_LEFT_CLICK, image);
    ASSERT_TRUE(toolbox.getSelectedColor(Mimp::MIMP_LEFT_CLICK) == Mimp::Color::Black);
}