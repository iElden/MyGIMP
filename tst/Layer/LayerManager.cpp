#include <gtest/gtest.h>
#include "../../src/Data/Vector2.hpp"
#include "../../src/Layer/LayerManager.hpp"
#include "../../src/Exceptions.hpp"

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

TEST(LayerManager, selectInvalidLayerOneLayer) {
    Mimp::LayerManager lm(Mimp::Vector2<unsigned>{800, 600});

    ASSERT_EQ(lm.size(), 1);
    try {
        lm.selectLayer(6);
    } catch (Mimp::InvalidArgumentException &e) {
        ASSERT_EQ(std::string(e.what()), "Cannot select layer 6 because there are only 1 layers.");
    }
}

TEST(LayerManager, selectInvalidLayerIndexTooHigh) {
    Mimp::LayerManager lm(Mimp::Vector2<unsigned>{800, 600});

    lm.addLayer({700, 4});
    ASSERT_EQ(lm.size(), 2);
    try {
        lm.selectLayer(3);
    } catch (Mimp::InvalidArgumentException &e) {
        ASSERT_EQ(std::string(e.what()), "Cannot select layer 3 because there are only 2 layers.");
    }
}

TEST(LayerManager, selectValidLayerIndex) {
    Mimp::LayerManager lm(Mimp::Vector2<unsigned>{800, 600});

    lm.addLayer({700, 4});
    lm.addLayer({700, 4});
    lm.addLayer({700, 4});
    ASSERT_EQ(lm.size(), 4);
    lm.selectLayer(2);
    ASSERT_TRUE(lm.getSelectedLayerIndex() != 0);
    ASSERT_TRUE(lm.getSelectedLayerIndex() == 2);
}

TEST(LayerManager, selectLayer) {
    Mimp::LayerManager lm(Mimp::Vector2<unsigned>{800, 600});

    lm.addLayer({700, 4});
    ASSERT_EQ(lm.size(), 2);
    auto l1 = lm.selectLayer(1);
    auto l2 = lm.getSelectedLayer();

    ASSERT_EQ(l1.getSize().x, l2.getSize().x);
    ASSERT_EQ(l1.getSize().y, l2.getSize().y);

    for (int i = 0; i < l1.getSize().x * l1.getSize().y; i += 1)
        ASSERT_EQ(l1.getFrameBuffer()[i], l2.getFrameBuffer()[i]);
}

TEST(LayerManager, deleteLayerOneLayer) {
    Mimp::LayerManager lm(Mimp::Vector2<unsigned>{800, 600});

    ASSERT_NE(lm.size(), 5);
    try {
        lm.deleteLayer(5);
    } catch (Mimp::OutOfBoundException &e) {
        ASSERT_EQ(std::string(e.what()), "Cannot delete layer 5 because there are only 1 layers.");
    }
}

TEST(LayerManager, deleteLayerIndexTooHigh) {
    Mimp::LayerManager lm(Mimp::Vector2<unsigned>{800, 600});

    lm.addLayer({700, 4});
    ASSERT_NE(lm.size(), 5);
    try {
        lm.deleteLayer(5);
    } catch (Mimp::OutOfBoundException &e) {
        ASSERT_EQ(std::string(e.what()), "Cannot delete layer 5 because there are only 2 layers.");
    }
}

TEST(LayerManager, deleteRootLayerOneLayer) {
    Mimp::LayerManager lm(Mimp::Vector2<unsigned>{800, 600});

    ASSERT_EQ(lm.size(), 1);
    try {
        lm.deleteLayer(0);
    } catch (Mimp::InvalidArgumentException &e) {
        ASSERT_EQ(std::string(e.what()), "Cannot delete layer because there are only a single layer.");
    }
}

TEST(LayerManager, deleteRootLayerMultipleLayer) {
    Mimp::LayerManager lm(Mimp::Vector2<unsigned>{800, 600});

    lm.addLayer({700, 4});
    lm.addLayer({700, 4});

    ASSERT_EQ(lm.size(), 3);
    lm.deleteLayer(0);
    ASSERT_EQ(lm.size(), 2);
}

TEST(LayerManager, moveLayerNewIndexTooHigh) {
    Mimp::LayerManager lm(Mimp::Vector2<unsigned>{800, 600});

    lm.addLayer({700, 4});
    lm.addLayer({700, 4});
    ASSERT_EQ(lm.size(), 3);

    try {
        lm.setLayerIndex(0, 6);
    } catch (Mimp::OutOfBoundException &e) {
        ASSERT_EQ(std::string(e.what()), "Cannot move layer 0 to location 6 because there are only 3 layers");
    }
}

TEST(LayerManager, moveLayerOldIndexTooHigh) {
    Mimp::LayerManager lm(Mimp::Vector2<unsigned>{800, 600});

    lm.addLayer({700, 4});
    lm.addLayer({700, 4});
    ASSERT_EQ(lm.size(), 3);

    try {
        lm.setLayerIndex(8, 6);
    } catch (Mimp::OutOfBoundException &e) {
        ASSERT_EQ(std::string(e.what()), "Cannot move layer 8 to location 6 because there are only 3 layers");
    }
}


TEST(LayerManager, moveLayerCorrectIndexes) {
    Mimp::LayerManager lm(Mimp::Vector2<unsigned>{800, 600});

    lm.addLayer({700, 4});
    lm.addLayer({700, 4});
    lm.addLayer({700, 4});
    lm.addLayer({700, 4});

    ASSERT_EQ(lm.size(), 5);
    lm.setLayerIndex(2, 4);
    ASSERT_EQ(lm.size(), 5);
}

TEST(LayerManager, setSize) {
    Mimp::Vector2<unsigned> oldSize = {800, 600};
    Mimp::Vector2<unsigned> newSize = {45, 345};
    Mimp::LayerManager lm(oldSize);


    ASSERT_TRUE(lm.getSize() == oldSize);
    lm.setSize(newSize);
    ASSERT_TRUE(lm.getSize() == newSize);
}

TEST(LayerManager, iterators) {
    Mimp::Vector2<unsigned> s1 = {800, 600};
    Mimp::LayerManager lm(s1);

    lm.addLayer({123, 456});
    lm.addLayer({456, 13});

    ASSERT_TRUE(lm.begin()->get()->getSize() == s1);
    ASSERT_TRUE(lm.size() == 3);

    int test = 0;
    for (auto i = lm.begin(); i != lm.end(); i += 1) {
        test += 1;
    }
    ASSERT_TRUE(test == 3);
}

TEST(LayerManager, noLayer) {
    try {
        Mimp::LayerManager lm({123, 456}, 0);
    } catch (Mimp::InvalidArgumentException &e) {
        ASSERT_EQ(std::string(e.what()), "Must add at least a single layer");
    }
}

TEST(LayerManager, addLayer) {
    Mimp::LayerManager lm(Mimp::Vector2<unsigned>{123, 456});
    Mimp::Layer l({456, 123});

    ASSERT_EQ(lm.size(), 1);
    lm.addLayer(l);
    ASSERT_EQ(lm.size(), 2);
}

TEST(LayerManager, fromInvalidPath) {
    try {
        Mimp::LayerManager lm("../invalidfile");
    } catch (Mimp::InvalidImageException &e) {
        ASSERT_EQ(std::string(e.what()), "Cannot open file ../invalidfile: No such file or directory");
    }
}

TEST(LayerManager, fromMemory) {
    Mimp::LayerManager lm{Mimp::Vector2<unsigned>{10, 10}};

    try {
        lm.importImageFromMemory("invalid");
    } catch (Mimp::InvalidImageException &e) {
        ASSERT_EQ(std::string(e.what()), "Failed to load image from memory");
    }
}