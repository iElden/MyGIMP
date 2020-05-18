#include <gtest/gtest.h>
#include <TGUI/TGUI.hpp>
#include "../../../src/ImageOperations/Selection/SelectAllOperation.hpp"

TEST(SelectAllOperation, wholeLayer) {
    tgui::Gui gui{};
    Mimp::LayerManager lm{{10, 10}, 1, Mimp::Color::Red};
    Mimp::Image i{{10, 10}, lm};
    Mimp::SelectAllOperation sao;

    ASSERT_TRUE(i.selectedArea.getPoints().size() == 0);

    sao.click(gui, i);
    ASSERT_TRUE(i.selectedArea.getPoints().size() == 100);
}