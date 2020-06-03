#include <gtest/gtest.h>
#include "../src/Widgets/LayerWidget.hpp"

TEST(LayerWidget, basicConstruction) {
    Mimp::Layer l{{10, 10}};
    Mimp::LayerWidget lw{l, {10, 10}};

    ASSERT_TRUE(lw.getSize().x == 10);
    ASSERT_TRUE(lw.getSize().y == 10);
}

TEST(LayerWidget, create) {
    Mimp::Layer l{{10, 10}};
    auto lw = Mimp::LayerWidget::create(l, {10, 10});

    ASSERT_TRUE(lw->getSize().x == 10);
    ASSERT_TRUE(lw->getSize().y == 10);
}

TEST(LayerWidget, clone) {
    Mimp::Layer l{{10, 10}};
    Mimp::LayerWidget lw{l, {10, 10}};

    auto clone = lw.clone();

    ASSERT_TRUE(clone->getSize().x == 10);
    ASSERT_TRUE(clone->getSize().y == 10);
}