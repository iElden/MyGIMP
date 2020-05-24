#include <gtest/gtest.h>
#include <TGUI/TGUI.hpp>
#include "../../../src/ImageOperations/Selection/ShrinkSelection.hpp"

TEST(ShrinkSelection, noSelection) {
    tgui::Gui gui{};
    Mimp::LayerManager lm{{10, 10}, 1, Mimp::Color::Red};
    Mimp::Image i{{10, 10}, lm};
    Mimp::ShrinkSelection sso;

    ASSERT_TRUE(i.selectedArea.getPoints().size() == 0);

	sso.click(gui, i, nullptr, <#initializer#>);

    ASSERT_TRUE(i.selectedArea.getPoints().size() == 0);
}

TEST(ShrinkSelection, onlyOnePixel) {
    tgui::Gui gui{};
    Mimp::LayerManager lm{{10, 10}, 1, Mimp::Color::Red};
    Mimp::Image i{{10, 10}, lm};
    Mimp::ShrinkSelection sso;

    i.selectedArea.add(5, 5);
    ASSERT_TRUE(i.selectedArea.getPoints().size() == 1);

	sso.click(gui, i, nullptr, <#initializer#>);

    ASSERT_TRUE(i.selectedArea.getPoints().size() == 0);
    ASSERT_FALSE(i.selectedArea.pointInMap(5, 5));
    ASSERT_FALSE(i.selectedArea.pointInMap(5, 6));
}

TEST(ShrinkSelection, wholeLayer) {
    tgui::Gui gui{};
    Mimp::LayerManager lm{{10, 10}, 1, Mimp::Color::Red};
    Mimp::Image i{{10, 10}, lm};
    Mimp::ShrinkSelection sso;

    i.selectedArea.selectAll();
    ASSERT_TRUE(i.selectedArea.getPoints().size() == 100);

	sso.click(gui, i, nullptr, <#initializer#>);

    ASSERT_TRUE(i.selectedArea.getPoints().size() == 64);
}