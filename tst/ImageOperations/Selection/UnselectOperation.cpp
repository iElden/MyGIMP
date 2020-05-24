#include <gtest/gtest.h>
#include <TGUI/TGUI.hpp>
#include "../../../src/ImageOperations/Selection/UnselectOperation.hpp"
#include "../../../src/Editor.hpp"

TEST(UnselectOperation, wholeLayer) {
    tgui::Gui gui{};
    Mimp::ToolBox toolBox{gui};
    Mimp::Editor e{};
    Mimp::CanvasWidget::Ptr cw = Mimp::CanvasWidget::create(toolBox, Mimp::Vector2<unsigned int>{10, 10});
    Mimp::UnselectOperation uo;


    cw->selectedArea.selectAll();
    ASSERT_TRUE(cw->selectedArea.getPoints().size() == 100);

	uo.click(gui, cw, nullptr, e);
    ASSERT_TRUE(cw->selectedArea.getPoints().size() == 0);
}