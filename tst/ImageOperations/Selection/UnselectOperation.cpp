#include <gtest/gtest.h>
#include <TGUI/TGUI.hpp>
#include "../../../src/ImageOperations/Selection/UnselectOperation.hpp"

TEST(InvertSelectionOperation, wholeLayer) {
    tgui::Gui gui{};
    Mimp::LayerManager lm{{10, 10}, 1, Mimp::Color::Red};
    Mimp::Image i{{10, 10}, lm};
    Mimp::UnselectOperation uo;

    i.selectedArea.selectAll();
    ASSERT_TRUE(i.selectedArea.getPoints().size() == 100);

    uo.click(gui, i);
    ASSERT_TRUE(i.selectedArea.getPoints().size() == 0);
}