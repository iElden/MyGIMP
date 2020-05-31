#include <gtest/gtest.h>
#include "../src/SelectedArea.hpp"

TEST(SelectedArea, addPointInsideArea) {
    Mimp::SelectedArea selectedArea(10, 10);

    selectedArea.add(5, 5);
    selectedArea.add({10, 10});

    ASSERT_EQ(selectedArea.isAnAreaSelected(), true);
}

TEST(SelectedArea, addPointInsideAreaAndClear) {
    Mimp::SelectedArea selectedArea(10, 10);

    selectedArea.add(5, 5);
    selectedArea.add({10, 10});

    selectedArea.clear();

    ASSERT_EQ(selectedArea.isAnAreaSelected(), false);
}

TEST(SelectedArea, getSize) {
    Mimp::Vector2<unsigned > size = {10, 10};
    Mimp::SelectedArea selectedArea(size.x, size.y);

    ASSERT_TRUE(selectedArea.getSize() == size);
}

TEST(SelectedArea, setSize) {
    Mimp::Vector2<unsigned > size = {10, 10};
    Mimp::Vector2<unsigned > newSize1 = {10, 10};
    Mimp::Vector2<unsigned > newSize2 = {100, 70};
    Mimp::SelectedArea selectedArea(size.x, size.y);

    ASSERT_TRUE(selectedArea.getSize() == size);
    selectedArea.setSize(newSize1);
    ASSERT_TRUE(selectedArea.getSize() == size);
    selectedArea.setSize(newSize2);
    ASSERT_FALSE(selectedArea.getSize() == size);
    ASSERT_TRUE(selectedArea.getSize() == newSize2);
}

TEST(SelectArea, selectAll) {
    Mimp::SelectedArea selectedArea(10, 48);

    ASSERT_TRUE(selectedArea.getPoints().size() == 0);
    selectedArea.selectAll();
    ASSERT_TRUE(selectedArea.getPoints().size() == 480);
}

TEST(SelectedArea, createFromExisting) {
    Mimp::SelectedArea selectedArea(10, 10);

    Mimp::SelectedArea other(selectedArea);

    ASSERT_EQ(other.getSize().x, 10);
    ASSERT_EQ(other.getSize().y, 10);
}

TEST(SelectedArea, invertFullSelection) {
    Mimp::SelectedArea selectedArea(10, 10);

    selectedArea.selectAll();
    ASSERT_TRUE(selectedArea.getPoints().size() == 100);
    selectedArea.invert();
    ASSERT_TRUE(selectedArea.getPoints().size() == 0);
}

TEST(SelectedArea, fillWholeSelection) {
    Mimp::SelectedArea selectedArea(10, 10);
    Mimp::Layer l({10, 10});

    selectedArea.selectAll();
    selectedArea.fill(l, Mimp::Color::Green);

    auto pxs = l->buffer.getBuffer();
    for (int i = 0; i < 100; i += 1) {
        ASSERT_EQ(pxs[i], Mimp::Color::Green);
    }
}

TEST(SelectedArea, pointsOutsideSelectedArea) {
    Mimp::SelectedArea selectedArea(10, 10);

    ASSERT_FALSE(selectedArea.pointInMap(11, 10));
    ASSERT_FALSE(selectedArea.pointInMap(10, 11));
}

TEST(SelectedArea, pointsInsideSelectedArea) {
    Mimp::SelectedArea selectedArea(10, 10);

    selectedArea.add(5, 8);
    ASSERT_TRUE(selectedArea.pointInMap(5, 8));
}

TEST(SelectedArea, vectorPointOutsiteSelectedArea) {
    Mimp::SelectedArea selectedArea(10, 10);

    ASSERT_FALSE(selectedArea.pointInMap({11, 10}));
    ASSERT_FALSE(selectedArea.pointInMap({10, 11}));
}

TEST(SelectedArea, vectorPointInsiteSelectedArea) {
    Mimp::SelectedArea selectedArea(10, 10);

    selectedArea.add({5, 8});
    ASSERT_TRUE(selectedArea.pointInMap({5, 8}));
}

TEST(SelectedArea, removePointFromArea) {
    Mimp::SelectedArea selectedArea(10, 10);
    selectedArea.selectAll();

    selectedArea.remove(5, 5);
    selectedArea.remove({7, 7});

    ASSERT_TRUE(selectedArea.getPoints().size() != 100);
    ASSERT_TRUE(selectedArea.pointInMap(5, 4));
    ASSERT_FALSE(selectedArea.pointInMap(5, 5));
    ASSERT_FALSE(selectedArea.pointInMap(7, 7));
}

TEST(SelectedArea, removePointFromOutsideArea) {
    Mimp::SelectedArea selectedArea(10, 10);
    selectedArea.selectAll();

    selectedArea.remove(5, 12);

    ASSERT_TRUE(selectedArea.getPoints().size() == 100);
}