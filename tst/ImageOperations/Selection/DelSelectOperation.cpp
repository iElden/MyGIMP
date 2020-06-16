#include <gtest/gtest.h>
#include <TGUI/TGUI.hpp>
#include "../../../src/ImageOperations/Selection/DelSelectionOperation.hpp"

TEST(DelSelectOperation, wholeLayer) {
    tgui::Gui gui{};
    Mimp::ToolBox toolBox{gui};
    Mimp::Editor e{};
    Mimp::CanvasWidget::Ptr cw = Mimp::CanvasWidget::create(toolBox, Mimp::Vector2<unsigned int>{10, 10});
    Mimp::DelSelectionOperation dso;


    cw->getSelectedLayer()->buffer.clear(Mimp::Color::Red);
    auto buffer = cw->getSelectedLayer()->buffer.getBuffer();
    for (int i = 0; i < 100; i += 1)
        ASSERT_TRUE(buffer[i] == Mimp::Color::Red);

    cw->selectedArea->selectAll();
    ASSERT_TRUE(cw->selectedArea->getPoints().size() == 100);

	dso.click(gui, cw, nullptr, e);
    buffer = cw->getSelectedLayer()->buffer.getBuffer();
    for (int i = 0; i < 100; i += 1)
        ASSERT_TRUE(buffer[i] == Mimp::Color::Transparent);

}