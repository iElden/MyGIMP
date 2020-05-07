#include <gtest/gtest.h>
#include "../src/Data/Vector2.hpp"
#include "../src/Layer/LayerManager.hpp"

TEST(LayerManager, createBasicLayerManager) {
    Mimp::LayerManager lm(Mimp::Vector2<unsigned>{800, 600});

    ASSERT_EQ(lm.getSize().x, 800);
}

TEST(LayerManager, testLayerSelectionByIndex) {
    Mimp::LayerManager lm(Mimp::Vector2<unsigned>{800, 600});

    lm.addLayer({700, 4});
    lm.addLayer({730, 4});
    ASSERT_EQ(lm.selectLayer(2).getSize().x, 730);

}
