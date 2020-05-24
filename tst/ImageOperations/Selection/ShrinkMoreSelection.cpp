#include <gtest/gtest.h>
#include <TGUI/TGUI.hpp>
#include "../../../src/ImageOperations/Selection/ShrinkMoreSelection.hpp"

TEST(ShrinkMoreSelection, click) {
    tgui::Gui gui{};
    Mimp::LayerManager lm{{10, 10}, 1, Mimp::Color::Red};
    Mimp::Image i{{10, 10}, lm};
    Mimp::ShrinkMoreSelection sms;

	sms.click(gui, i, nullptr, <#initializer#>);

    auto slider = gui.get<tgui::Slider>("Slider");
    ASSERT_TRUE(slider->getValue() == 0);
}
