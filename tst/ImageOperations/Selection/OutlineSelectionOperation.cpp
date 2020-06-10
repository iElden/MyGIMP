#include <gtest/gtest.h>
#include <TGUI/TGUI.hpp>
#include "../../../src/ImageOperations/Selection/OutlineSelectionOperation.hpp"
#include "../../../src/Editor.hpp"

TEST(OutlineSelectionOperation, noSelection) {
    tgui::Gui gui{};
    Mimp::ToolBox toolBox{gui};
    Mimp::Editor e{};
    Mimp::CanvasWidget::Ptr cw = Mimp::CanvasWidget::create(toolBox, Mimp::Vector2<unsigned int>{10, 10});
    Mimp::OutlineSelectionOperation oso;

    ASSERT_TRUE(cw->selectedArea->getPoints().size() == 0);

	oso.click(gui, cw, nullptr, e);

    ASSERT_TRUE(cw->selectedArea->getPoints().size() == 0);
}

TEST(OutlineSelectionOperation, onlyOnePixel) {
    tgui::Gui gui{};
    Mimp::ToolBox toolBox{gui};
    Mimp::Editor e{};
    Mimp::CanvasWidget::Ptr cw = Mimp::CanvasWidget::create(toolBox, Mimp::Vector2<unsigned int>{10, 10});
    Mimp::OutlineSelectionOperation oso;

    cw->selectedArea->add(5, 5);
    ASSERT_TRUE(cw->selectedArea->getPoints().size() == 1);

	oso.click(gui, cw, nullptr, e);

    ASSERT_TRUE(cw->selectedArea->getPoints().size() == 1);
    ASSERT_TRUE(cw->selectedArea->pointInMap(5, 5));
}

TEST(OutlineSelectionOperation, wholeLayer) {
    tgui::Gui gui{};
    Mimp::ToolBox toolBox{gui};
    Mimp::Editor e{};
    Mimp::CanvasWidget::Ptr cw = Mimp::CanvasWidget::create(toolBox, Mimp::Vector2<unsigned int>{10, 10});
    Mimp::OutlineSelectionOperation oso;

    cw->selectedArea->selectAll();
    ASSERT_TRUE(cw->selectedArea->getPoints().size() == 100);

	oso.click(gui, cw, nullptr, e);

    ASSERT_TRUE(cw->selectedArea->getPoints().size() == 36);
    ASSERT_TRUE(cw->selectedArea->pointInMap(0, 0));
    ASSERT_TRUE(cw->selectedArea->pointInMap(0, 9));
    ASSERT_TRUE(cw->selectedArea->pointInMap(9, 6));
    ASSERT_FALSE(cw->selectedArea->pointInMap(6, 4));
}

TEST(OutlineSelectionOperation, wholeLayerWithThicknessOf2) {
    tgui::Gui gui{};
    Mimp::LayerManager lm{{10, 10}, 1, Mimp::Color::Red};
    Mimp::Image i{{10, 10}, lm};
    Mimp::OutlineSelectionOperation oso;

    i.selectedArea->selectAll();
    ASSERT_TRUE(i.selectedArea->getPoints().size() == 100);

    oso._run(i, 2);
    
    ASSERT_EQ(i.selectedArea->getPoints().size(), 64);
    ASSERT_TRUE(i.selectedArea->pointInMap(0, 0));
    ASSERT_TRUE(i.selectedArea->pointInMap(0, 9));
    ASSERT_TRUE(i.selectedArea->pointInMap(9, 8));
    ASSERT_FALSE(i.selectedArea->pointInMap(6, 4));
    ASSERT_FALSE(i.selectedArea->pointInMap(5, 7));
}