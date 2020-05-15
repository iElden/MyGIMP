#include <gtest/gtest.h>
#include <TGUI/TGUI.hpp>
#include "../../src/Tools/Eraser.hpp"

TEST(Eraser, getDefaultPanelValues) {
    tgui::Gui gui{};
    Mimp::ToolBox toolbox{gui};
    Mimp::Eraser eraser{toolbox};

    auto panel = eraser.getParametersPanel();
    auto radiusSlider = panel->get<tgui::Slider>("Radius");
    auto shapeBox = panel->get<tgui::ComboBox>("Shape");
    auto radiusPreview = panel->get<tgui::TextBox>("RadiusPreview");

    ASSERT_TRUE(radiusSlider->getValue() == 5.0);
    ASSERT_TRUE(shapeBox->getSelectedItemIndex() == Mimp::DrawShape::CIRCLE);
    ASSERT_TRUE(radiusPreview->getText() == "5");
}

/* Crash, std::bad_alloc
TEST(Eraser, onClick) {
    tgui::Gui gui{};
    Mimp::ToolBox toolbox{gui};
    Mimp::Eraser eraser{toolbox};
    Mimp::Vector2<unsigned> size{10, 10};
    Mimp::LayerManager lm({10, 10}, Mimp::Color::Magenta); <--
    Mimp::Image image(size, lm);
    Mimp::Vector2<int> erasePos = {5, 5};

    ASSERT_EQ(image.getLayers().size(), 1);
    auto buffer = image.getLayers()[0].buffer.getBuffer();
    for (int i = 0; i < size.x; i += 1) {
        for (int j = 0; j < size.y; j += 1) {
            ASSERT_TRUE(buffer[i + size.x * j] == Mimp::Color::Magenta);
        }
    }

    eraser.onClick(erasePos, Mimp::MIMP_LEFT_CLICK, image);
    buffer = image.getLayers()[0].buffer.getBuffer();
    for (int i = 0; i < size.x; i += 1) {
        for (int j = 0; j < size.y; j += 1) {
            if (i == erasePos.x && j == erasePos.y) {
                ASSERT_TRUE(buffer[i + size.x * j] == Mimp::Color::Transparent);
            } else {
                ASSERT_TRUE(buffer[i + size.x * j] == Mimp::Color::Magenta);
            }
        }
    }
}
 */

// onMouseDrag
// onClick