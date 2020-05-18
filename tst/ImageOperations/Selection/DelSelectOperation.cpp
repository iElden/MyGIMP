#include <gtest/gtest.h>
#include <TGUI/TGUI.hpp>
#include "../../../src/ImageOperations/Selection/DelSelectionOperation.hpp"

TEST(DelSelectOperation, wholeLayer) {
    tgui::Gui gui{};
    Mimp::LayerManager lm{{10, 10}, 1, Mimp::Color::Red};
    Mimp::Image i{{10, 10}, lm};
    Mimp::DelSelectionOperation dso;

    auto buffer = i.getSelectedLayer().buffer.getBuffer();
    for (int i = 0; i < 100; i += 1)
        ASSERT_TRUE(buffer[i] == Mimp::Color::Red);

    i.selectedArea.selectAll();
    ASSERT_TRUE(i.selectedArea.getPoints().size() == 100);

    dso.click(gui, i);
    buffer = i.getSelectedLayer().buffer.getBuffer();
    for (int i = 0; i < 100; i += 1)
        ASSERT_TRUE(buffer[i] == Mimp::Color::Transparent);

}