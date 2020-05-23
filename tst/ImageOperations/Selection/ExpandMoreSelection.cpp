#include <gtest/gtest.h>
#include <TGUI/TGUI.hpp>
#include "../../../src/ImageOperations/Selection/ExpandMoreSelection.hpp"

TEST(ExpandMoreSelection, click) {
    tgui::Gui gui{};
    Mimp::LayerManager lm{{10, 10}, 1, Mimp::Color::Red};
    Mimp::Image i{{10, 10}, lm};
    Mimp::ExpandMoreSelection ems;

    ems.click(gui, i);

    auto slider = gui.get<tgui::Slider>("Slider");
    ASSERT_TRUE(slider->getValue() == 0);
}