#include <gtest/gtest.h>
#include <TGUI/TGUI.hpp>
#include "../../../src/ImageOperations/Selection/FillSelectionOperation.hpp"

#include "../../../src/Utils.hpp"

class FSOTest : public Mimp::FillSelectionOperation {
public:
    FSOTest() : Mimp::FillSelectionOperation() {}

    void fill(Mimp::Image &image, Mimp::Color color) {
        Mimp::FillSelectionOperation::_fill(image.getSelectedLayer(), image.selectedArea, color);
    }
};

TEST(FillSelectionOperation, noSelectedArea) {
    Mimp::LayerManager lm{{10, 10}, 1, Mimp::Color::Red};
    Mimp::Image image{{10, 10}, lm};
    FSOTest fso;

    auto buffer = image.getLayers()[0].buffer.getBuffer();
    for (int i = 0; i < 100; i += 1) {
        ASSERT_TRUE(buffer[i] == Mimp::Color::Red);
    }
    fso.fill(image, Mimp::Color::Yellow);

    buffer = image.getLayers()[0].buffer.getBuffer();
    for (int i = 0; i < 100; i += 1) {
        ASSERT_TRUE(buffer[i] == Mimp::Color::Red);
    }
}

TEST(FillSelectionOperation, selectOnePoint) {
    Mimp::LayerManager lm{{10, 10}, 1, Mimp::Color::Red};
    Mimp::Image image{{10, 10}, lm};
    FSOTest fso;
    Mimp::Vector2<int> pt{2, 8};

    auto buffer = image.getLayers()[0].buffer.getBuffer();
    for (int i = 0; i < 100; i += 1) {
        ASSERT_TRUE(buffer[i] == Mimp::Color::Red);
    }
    image.selectedArea.add(pt);
    fso.fill(image, Mimp::Color::Yellow);

    ASSERT_TRUE(image.selectedArea.pointInMap(pt));
    buffer = image.getLayers()[0].buffer.getBuffer();

    for (int i = 0; i < 10; i += 1) {
        for (int j = 0; j < 10; j += 1) {
            if (i == pt.x && j == pt.y) {
                ASSERT_TRUE(buffer[i + 10 * j] == Mimp::Color::Yellow);
            } else {
                ASSERT_TRUE(buffer[i + 10 * j] == Mimp::Color::Red);
            }
        }
    }
}

TEST(FillSelectionOperation, click) {
    tgui::Gui gui{};
    Mimp::LayerManager lm{{10, 10}, 1, Mimp::Color::Red};
    Mimp::Image image{{10, 10}, lm};
    FSOTest fso;
    Mimp::Vector2<int> pt{2, 8};

    fso.click(gui, image);

    auto edit = gui.get<tgui::EditBox>("Edit");
    ASSERT_TRUE(edit->getText() == "#000000");
}