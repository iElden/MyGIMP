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

TEST(Eraser, onClick) {
    tgui::Gui gui{};
    Mimp::ToolBox toolbox{gui};
    Mimp::Eraser eraser{toolbox};
    Mimp::Vector2<unsigned> size{10, 10};
    Mimp::LayerManager lm(size, 1, Mimp::Color::Magenta);
    Mimp::Image image(size, lm);
    Mimp::Vector2<int> erasePos = {2, 2};
    float radius = eraser.getParametersPanel()->get<tgui::Slider>("Radius")->getValue();

    ASSERT_EQ(image.getLayers().size(), 1);
    auto buffer = image.getLayers()[0].getFrameBuffer().getBuffer();
    for (int i = 0; i < size.x; i += 1) {
        for (int j = 0; j < size.y; j += 1) {
            ASSERT_TRUE(buffer[i + size.x * j] == Mimp::Color::Magenta);
        }
    }

    eraser.onClick(erasePos, Mimp::MIMP_LEFT_CLICK, image);

    buffer = image.getLayers()[0].getFrameBuffer().getBuffer();
    for (int i = 0; i < size.x; i += 1) {
        for (int j = 0; j < size.y; j += 1) {
            if (i >= erasePos.x - 1 && i < erasePos.x + radius - 2
            && j >= erasePos.y - 1 && j < erasePos.y + radius - 2) {
                ASSERT_TRUE(buffer[i + size.x * j] == Mimp::Color::Transparent);
            } else {
                ASSERT_TRUE(buffer[i + size.x * j] == Mimp::Color::Magenta);
            }
        }
    }
}

TEST(Eraser, onDrag) {
    tgui::Gui gui{};
    Mimp::ToolBox toolbox{gui};
    Mimp::Eraser eraser{toolbox};
    Mimp::Vector2<unsigned> size{10, 10};
    Mimp::LayerManager lm(size, 1, Mimp::Color::Magenta);
    Mimp::Image image(size, lm);
    Mimp::Vector2<int> erasePosStart = {2, 2};
    Mimp::Vector2<int> erasePosEnd = {8, 2};
    float radius = eraser.getParametersPanel()->get<tgui::Slider>("Radius")->getValue();

    ASSERT_EQ(image.getLayers().size(), 1);
    auto buffer = image.getLayers()[0].getFrameBuffer().getBuffer();
    for (int i = 0; i < size.x; i += 1) {
        for (int j = 0; j < size.y; j += 1) {
            ASSERT_TRUE(buffer[i + size.x * j] == Mimp::Color::Magenta);
        }
    }

    eraser.onMouseDrag(erasePosStart, erasePosEnd, Mimp::MIMP_LEFT_CLICK, image);

    buffer = image.getLayers()[0].getFrameBuffer().getBuffer();
    for (int i = 0; i < size.x; i += 1) {
        for (int j = 0; j < size.y; j += 1) {
            if (i >= erasePosStart.x - 1 && i < erasePosEnd.x + radius - 2
                && j >= erasePosStart.y - 1 && j < erasePosEnd.y + radius - 2) {
                ASSERT_TRUE(buffer[i + size.x * j] == Mimp::Color::Transparent);
            } else {
                ASSERT_TRUE(buffer[i + size.x * j] == Mimp::Color::Magenta);
            }
        }
    }
}

TEST(Eraser, onClickWithLockedLayer) {
    tgui::Gui gui{};
    Mimp::ToolBox toolbox{gui};
    Mimp::Eraser eraser{toolbox};
    Mimp::Vector2<unsigned> size{10, 10};
    Mimp::LayerManager lm(size, 1, Mimp::Color::Magenta);
    Mimp::Image image(size, lm);
    Mimp::Vector2<int> erasePos = {2, 2};
    float radius = eraser.getParametersPanel()->get<tgui::Slider>("Radius")->getValue();

    ASSERT_EQ(image.getLayers().size(), 1);
    auto buffer = image.getLayers()[0].getFrameBuffer().getBuffer();
    for (int i = 0; i < size.x; i += 1) {
        for (int j = 0; j < size.y; j += 1) {
            ASSERT_TRUE(buffer[i + size.x * j] == Mimp::Color::Magenta);
        }
    }

    image.getLayers()[0].locked = true;
    eraser.onClick(erasePos, Mimp::MIMP_LEFT_CLICK, image);

    buffer = image.getLayers()[0].getFrameBuffer().getBuffer();
    for (int i = 0; i < size.x; i += 1) {
        for (int j = 0; j < size.y; j += 1) {
            ASSERT_TRUE(buffer[i + size.x * j] == Mimp::Color::Magenta);
        }
    }
}

TEST(Eraser, onDragWithLockedLayer) {
    tgui::Gui gui{};
    Mimp::ToolBox toolbox{gui};
    Mimp::Eraser eraser{toolbox};
    Mimp::Vector2<unsigned> size{10, 10};
    Mimp::LayerManager lm(size, 1, Mimp::Color::Magenta);
    Mimp::Image image(size, lm);
    Mimp::Vector2<int> erasePosStart = {2, 2};
    Mimp::Vector2<int> erasePosEnd = {8, 2};
    float radius = eraser.getParametersPanel()->get<tgui::Slider>("Radius")->getValue();

    ASSERT_EQ(image.getLayers().size(), 1);
    auto buffer = image.getLayers()[0].getFrameBuffer().getBuffer();
    for (int i = 0; i < size.x; i += 1) {
        for (int j = 0; j < size.y; j += 1) {
            ASSERT_TRUE(buffer[i + size.x * j] == Mimp::Color::Magenta);
        }
    }

    image.getLayers()[0].locked = true;
    eraser.onMouseDrag(erasePosStart, erasePosEnd, Mimp::MIMP_LEFT_CLICK, image);

    buffer = image.getLayers()[0].getFrameBuffer().getBuffer();
    for (int i = 0; i < size.x; i += 1) {
        for (int j = 0; j < size.y; j += 1) {
            ASSERT_TRUE(buffer[i + size.x * j] == Mimp::Color::Magenta);
        }
    }
}

