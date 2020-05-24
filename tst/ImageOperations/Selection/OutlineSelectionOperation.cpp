#include <gtest/gtest.h>
#include <TGUI/TGUI.hpp>
#include "../../../src/ImageOperations/Selection/OutlineSelectionOperation.hpp"

TEST(OutlineSelectionOperation, noSelection) {
    tgui::Gui gui{};
    Mimp::LayerManager lm{{10, 10}, 1, Mimp::Color::Red};
    Mimp::Image i{{10, 10}, lm};
    Mimp::OutlineSelectionOperation oso;

    ASSERT_TRUE(i.selectedArea.getPoints().size() == 0);

	oso.click(gui, i, nullptr, <#initializer#>);

    ASSERT_TRUE(i.selectedArea.getPoints().size() == 0);
}

TEST(OutlineSelectionOperation, onlyOnePixel) {
    tgui::Gui gui{};
    Mimp::LayerManager lm{{10, 10}, 1, Mimp::Color::Red};
    Mimp::Image i{{10, 10}, lm};
    Mimp::OutlineSelectionOperation oso;

    i.selectedArea.add(5, 5);
    ASSERT_TRUE(i.selectedArea.getPoints().size() == 1);

	oso.click(gui, i, nullptr, <#initializer#>);

    for (int x = 0; x < 10; x += 1) {
        for (int y = 0; y < 10; y += 1)
            std::cout << i.selectedArea.pointInMap(x, y) << "|";
        std::cout << std::endl;
    }

    ASSERT_TRUE(i.selectedArea.getPoints().size() == 9);
    ASSERT_TRUE(0);
    for (int x = -1; x <= 1; x += 1)
        for (int y = -1; y <= 1; y += 1)
            ASSERT_TRUE(i.selectedArea.pointInMap(5 + x, 5 + y));
}

TEST(OutlineSelectionOperation, wholeLayer) {
    tgui::Gui gui{};
    Mimp::LayerManager lm{{10, 10}, 1, Mimp::Color::Red};
    Mimp::Image i{{10, 10}, lm};
    Mimp::OutlineSelectionOperation oso;

    i.selectedArea.selectAll();
    ASSERT_TRUE(i.selectedArea.getPoints().size() == 100);

	oso.click(gui, i, nullptr, <#initializer#>);

    ASSERT_TRUE(i.selectedArea.getPoints().size() == 100);
}