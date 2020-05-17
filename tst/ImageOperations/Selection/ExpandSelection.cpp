#include <gtest/gtest.h>
#include <TGUI/TGUI.hpp>
#include "../../../src/ImageOperations/Selection/ExpandSelection.hpp"

TEST(ExpandSelection, noSelectedArea) {
    tgui::Gui gui{};
    Mimp::LayerManager lm{{10, 10}, 1, Mimp::Color::Red};
    Mimp::Image i{{10, 10}, lm};
    Mimp::ExpandSelection es;

    ASSERT_TRUE(i.selectedArea.getPoints().size() == 0);
    es.click(gui, i);
    ASSERT_TRUE(i.selectedArea.getPoints().size() == 0);
}

TEST(ExpandSelection, selectFromWholeArea) {
    tgui::Gui gui{};
    Mimp::LayerManager lm{{10, 10}, 1, Mimp::Color::Red};
    Mimp::Image i{{10, 10}, lm};
    Mimp::ExpandSelection es;

    i.selectedArea.selectAll();
    ASSERT_TRUE(i.selectedArea.getPoints().size() == 100);
    es.click(gui, i);
    ASSERT_TRUE(i.selectedArea.getPoints().size() == 100);
}

TEST(ExpandSelection, selectFromSinglePoint) {
    tgui::Gui gui{};
    Mimp::LayerManager lm{{10, 10}, 1, Mimp::Color::Red};
    Mimp::Image i{{10, 10}, lm};
    Mimp::ExpandSelection es;

    i.selectedArea.add(5, 5);
    ASSERT_TRUE(i.selectedArea.getPoints().size() == 1);
    es.click(gui, i);
    ASSERT_TRUE(i.selectedArea.getPoints().size() == 9);
    ASSERT_TRUE(i.selectedArea.pointInMap(5, 5));
    ASSERT_TRUE(i.selectedArea.pointInMap(5, 4));
    ASSERT_FALSE(i.selectedArea.pointInMap(5, 3));
}
