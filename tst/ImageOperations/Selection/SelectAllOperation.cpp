#include <gtest/gtest.h>
#include <TGUI/TGUI.hpp>
#include "../../../src/ImageOperations/Selection/SelectAllOperation.hpp"

TEST(SelectAllOperation, wholeLayer) {
    tgui::Gui gui{};
    Mimp::ToolBox toolBox{gui};
    Mimp::Editor e{};
    Mimp::CanvasWidget::Ptr cw = Mimp::CanvasWidget::create(toolBox, Mimp::Vector2<unsigned int>{10, 10});
    Mimp::SelectAllOperation sao;

    ASSERT_TRUE(cw->selectedArea.getPoints().size() == 0);

	sao.click(gui, cw, nullptr, e);
    ASSERT_TRUE(cw->selectedArea.getPoints().size() == 100);
}