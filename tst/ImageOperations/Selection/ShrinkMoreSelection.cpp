#include <gtest/gtest.h>
#include <TGUI/TGUI.hpp>
#include "../../../src/ImageOperations/Selection/ShrinkMoreSelection.hpp"
#include "../../../src/Editor.hpp"

TEST(ShrinkMoreSelection, click) {
    tgui::Gui gui{};
    Mimp::ToolBox toolBox{gui};
    Mimp::Editor e{};
    Mimp::CanvasWidget::Ptr cw = Mimp::CanvasWidget::create(toolBox, Mimp::Vector2<unsigned int>{10, 10});
    Mimp::ShrinkMoreSelection sms;

	sms.click(gui, cw, nullptr, e);

    auto slider = gui.get<tgui::Slider>("Slider");
    ASSERT_TRUE(slider->getValue() == 0);
}
