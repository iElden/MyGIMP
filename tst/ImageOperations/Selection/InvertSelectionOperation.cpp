#include <gtest/gtest.h>
#include <TGUI/TGUI.hpp>
#include "../../../src/ImageOperations/Selection/InvertSelectionOperation.hpp"

TEST(UnelectOperation, wholeLayer) {
    tgui::Gui gui{};
    Mimp::LayerManager lm{{10, 10}, 1, Mimp::Color::Red};
    Mimp::Image i{{10, 10}, lm};
    Mimp::InvertSelectionOperation iso;

    i.selectedArea.selectAll();
    ASSERT_TRUE(i.selectedArea.getPoints().size() == 100);

	iso.click(gui, i, nullptr, <#initializer#>);
    ASSERT_TRUE(i.selectedArea.getPoints().size() == 0);
}