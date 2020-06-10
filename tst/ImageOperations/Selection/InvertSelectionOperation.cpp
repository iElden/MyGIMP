#include <gtest/gtest.h>
#include <TGUI/TGUI.hpp>
#include "../../../src/ImageOperations/Selection/InvertSelectionOperation.hpp"

TEST(UnelectOperation, wholeLayer) {
    tgui::Gui gui{};
    Mimp::ToolBox toolBox{gui};
    Mimp::Editor e{};
    Mimp::CanvasWidget::Ptr cw = Mimp::CanvasWidget::create(toolBox, Mimp::Vector2<unsigned int>{10, 10});
    Mimp::InvertSelectionOperation iso;

    cw->selectedArea->selectAll();
    ASSERT_TRUE(cw->selectedArea->getPoints().size() == 100);

	iso.click(gui, cw, nullptr, e);
    ASSERT_TRUE(cw->selectedArea->getPoints().size() == 0);
}