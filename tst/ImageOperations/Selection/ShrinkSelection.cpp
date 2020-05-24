#include <gtest/gtest.h>
#include <TGUI/TGUI.hpp>
#include "../../../src/ImageOperations/Selection/ShrinkSelection.hpp"
#include "../../../src/Editor.hpp"

TEST(ShrinkSelection, noSelection) {
    tgui::Gui gui{};
    Mimp::ToolBox toolBox{gui};
    Mimp::Editor e{};
    Mimp::CanvasWidget::Ptr cw = Mimp::CanvasWidget::create(toolBox, Mimp::Vector2<unsigned int>{10, 10});
    Mimp::ShrinkSelection sso;

    ASSERT_TRUE(cw->selectedArea.getPoints().size() == 0);

	sso.click(gui, cw, nullptr, e);

    ASSERT_TRUE(cw->selectedArea.getPoints().size() == 0);
}

TEST(ShrinkSelection, onlyOnePixel) {
    tgui::Gui gui{};
    Mimp::ToolBox toolBox{gui};
    Mimp::Editor e{};
    Mimp::CanvasWidget::Ptr cw = Mimp::CanvasWidget::create(toolBox, Mimp::Vector2<unsigned int>{10, 10});
    Mimp::ShrinkSelection sso;

    cw->selectedArea.add(5, 5);
    ASSERT_TRUE(cw->selectedArea.getPoints().size() == 1);

	sso.click(gui, cw, nullptr, e);

    ASSERT_TRUE(cw->selectedArea.getPoints().size() == 0);
    ASSERT_FALSE(cw->selectedArea.pointInMap(5, 5));
    ASSERT_FALSE(cw->selectedArea.pointInMap(5, 6));
}

TEST(ShrinkSelection, wholeLayer) {
    tgui::Gui gui{};
    Mimp::ToolBox toolBox{gui};
    Mimp::Editor e{};
    Mimp::CanvasWidget::Ptr cw = Mimp::CanvasWidget::create(toolBox, Mimp::Vector2<unsigned int>{10, 10});
    Mimp::ShrinkSelection sso;

    cw->selectedArea.selectAll();
    ASSERT_TRUE(cw->selectedArea.getPoints().size() == 100);

	sso.click(gui, cw, nullptr, e);

    ASSERT_TRUE(cw->selectedArea.getPoints().size() == 64);
}