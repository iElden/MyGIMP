#include <gtest/gtest.h>
#include <TGUI/TGUI.hpp>
#include "../../../src/ImageOperations/Selection/ExpandSelection.hpp"
#include "../../../src/Editor.hpp"

TEST(ExpandSelection, noSelectedArea) {
    tgui::Gui gui{};
    Mimp::ToolBox toolBox{gui};
    Mimp::Editor e{};
    Mimp::CanvasWidget::Ptr cw = Mimp::CanvasWidget::create(toolBox, Mimp::Vector2<unsigned int>{10, 10});
    Mimp::ExpandSelection es;

    ASSERT_TRUE(cw->selectedArea.getPoints().size() == 0);
	es.click(gui, cw, nullptr, e);
    ASSERT_TRUE(cw->selectedArea.getPoints().size() == 0);
}

TEST(ExpandSelection, selectFromWholeArea) {
    tgui::Gui gui{};
    Mimp::ToolBox toolBox{gui};
    Mimp::Editor e{};
    Mimp::CanvasWidget::Ptr cw = Mimp::CanvasWidget::create(toolBox, Mimp::Vector2<unsigned int>{10, 10});
    Mimp::ExpandSelection es;

    cw->selectedArea.selectAll();
    ASSERT_TRUE(cw->selectedArea.getPoints().size() == 100);
	es.click(gui, cw, nullptr, e);
    ASSERT_TRUE(cw->selectedArea.getPoints().size() == 100);
}

TEST(ExpandSelection, selectFromSinglePoint) {
    tgui::Gui gui{};
    Mimp::ToolBox toolBox{gui};
    Mimp::Editor e{};
    Mimp::CanvasWidget::Ptr cw = Mimp::CanvasWidget::create(toolBox, Mimp::Vector2<unsigned int>{10, 10});
    Mimp::ExpandSelection es;

    cw->selectedArea.add(5, 5);
    ASSERT_TRUE(cw->selectedArea.getPoints().size() == 1);
	es.click(gui, cw, nullptr, e);
    ASSERT_TRUE(cw->selectedArea.getPoints().size() == 9);
    ASSERT_TRUE(cw->selectedArea.pointInMap(5, 5));
    ASSERT_TRUE(cw->selectedArea.pointInMap(5, 4));
    ASSERT_FALSE(cw->selectedArea.pointInMap(5, 3));
}
