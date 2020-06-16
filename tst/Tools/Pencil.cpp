#include <gtest/gtest.h>
#include <TGUI/TGUI.hpp>
#include "../../src/Tools/Pencil.hpp"

#define INT(x) (static_cast<int>(x))

TEST(Pencil, getDefaultPanelValues) {
    tgui::Gui gui{};
    Mimp::ToolBox toolbox{gui};
    Mimp::Pencil p{toolbox};

    auto panel = p.getParametersPanel();
    auto radiusSlider = panel->get<tgui::Slider>("Radius");
    auto shapeBox = panel->get<tgui::ComboBox>("Shape");
    auto radiusPreview = panel->get<tgui::TextBox>("RadiusPreview");

    ASSERT_TRUE(radiusSlider->getValue() == 5.0);
    ASSERT_TRUE(shapeBox->getSelectedItemIndex() == Mimp::DrawShape::CIRCLE);
    ASSERT_TRUE(radiusPreview->getText() == "5");
}

TEST(Pencil, onClick) {
    tgui::Gui gui{};
    Mimp::ToolBox toolbox{gui};
    Mimp::Pencil pencil{toolbox};
    Mimp::Vector2<unsigned> size{10, 10};
    Mimp::LayerManager lm(size, 1, Mimp::Color::Magenta);
    Mimp::Image image(size, lm);
    Mimp::Vector2<int> erasePos = {2, 2};
    float radius = pencil.getParametersPanel()->get<tgui::Slider>("Radius")->getValue();

    ASSERT_EQ(image.getLayers().size(), 1);
    auto buffer = image.getLayers()[0]->buffer.getBuffer();
    for (int i = 0; i < INT(size.x); i += 1) {
        for (int j = 0; j < INT(size.y); j += 1) {
            ASSERT_TRUE(buffer[i + size.x * j] == Mimp::Color::Magenta);
        }
    }

    pencil.onClick(erasePos, Mimp::MIMP_LEFT_CLICK, image);

    buffer = image.getLayers()[0]->buffer.getBuffer();
    for (int i = 0; i < INT(size.x); i += 1) {
        for (int j = 0; j < INT(size.y); j += 1) {
            if (i >= erasePos.x - 1 && i < erasePos.x + INT(radius) - 2
                && j >= erasePos.y - 1 && j < erasePos.y + INT(radius) - 2) {
                ASSERT_TRUE(buffer[i + size.x * j] == Mimp::Color::Black);
            } else {
                ASSERT_TRUE(buffer[i + size.x * j] == Mimp::Color::Magenta);
            }
        }
    }
}

TEST(Pencil, onDrag) {
    tgui::Gui gui{};
    Mimp::ToolBox toolbox{gui};
    Mimp::Pencil pencil{toolbox};
    Mimp::Vector2<unsigned> size{10, 10};
    Mimp::LayerManager lm(size, 1, Mimp::Color::Magenta);
    Mimp::Image image(size, lm);
    Mimp::Vector2<int> erasePosStart = {2, 2};
    Mimp::Vector2<int> erasePosEnd = {8, 2};
    float radius = pencil.getParametersPanel()->get<tgui::Slider>("Radius")->getValue();

    ASSERT_EQ(image.getLayers().size(), 1);
    auto buffer = image.getLayers()[0]->buffer.getBuffer();
    for (int i = 0; i < INT(size.x); i += 1) {
        for (int j = 0; j < INT(size.y); j += 1) {
            ASSERT_TRUE(buffer[i + size.x * j] == Mimp::Color::Magenta);
        }
    }

    pencil.onMouseDrag(erasePosStart, erasePosEnd, Mimp::MIMP_LEFT_CLICK, image);

    buffer = image.getLayers()[0]->buffer.getBuffer();
    for (int i = 0; i < INT(size.x); i += 1) {
        for (int j = 0; j < INT(size.y); j += 1) {
            if (i >= erasePosStart.x - 1 && i < erasePosEnd.x + INT(radius) - 2
                && j >= erasePosStart.y - 1 && j < erasePosEnd.y + INT(radius) - 2) {
                ASSERT_TRUE(buffer[i + size.x * j] == Mimp::Color::Black);
            } else {
                ASSERT_TRUE(buffer[i + size.x * j] == Mimp::Color::Magenta);
            }
        }
    }
}

TEST(Pencil, onClickWithLockedLayer) {
    tgui::Gui gui{};
    Mimp::ToolBox toolbox{gui};
    Mimp::Pencil pencil{toolbox};
    Mimp::Vector2<unsigned> size{10, 10};
    Mimp::LayerManager lm(size, 1, Mimp::Color::Magenta);
    Mimp::Image image(size, lm);
    Mimp::Vector2<int> erasePos = {2, 2};

    ASSERT_EQ(image.getLayers().size(), 1);
    auto buffer = image.getLayers()[0]->buffer.getBuffer();
    for (int i = 0; i < INT(size.x); i += 1) {
        for (int j = 0; j < INT(size.y); j += 1) {
            ASSERT_TRUE(buffer[i + size.x * j] == Mimp::Color::Magenta);
        }
    }

    image.getLayers()[0].locked = true;
    pencil.onClick(erasePos, Mimp::MIMP_LEFT_CLICK, image);

    buffer = image.getLayers()[0]->buffer.getBuffer();
    for (int i = 0; i < INT(size.x); i += 1) {
        for (int j = 0; j < INT(size.y); j += 1) {
            ASSERT_TRUE(buffer[i + size.x * j] == Mimp::Color::Magenta);
        }
    }
}

TEST(Pencil, onDragWithLockedLayer) {
    tgui::Gui gui{};
    Mimp::ToolBox toolbox{gui};
    Mimp::Pencil pencil{toolbox};
    Mimp::Vector2<unsigned> size{10, 10};
    Mimp::LayerManager lm(size, 1, Mimp::Color::Magenta);
    Mimp::Image image(size, lm);
    Mimp::Vector2<int> erasePosStart = {2, 2};
    Mimp::Vector2<int> erasePosEnd = {8, 2};

    ASSERT_EQ(image.getLayers().size(), 1);
    auto buffer = image.getLayers()[0]->buffer.getBuffer();
    for (int i = 0; i < INT(size.x); i += 1) {
        for (int j = 0; j < INT(size.y); j += 1) {
            ASSERT_TRUE(buffer[i + size.x * j] == Mimp::Color::Magenta);
        }
    }

    image.getLayers()[0].locked = true;
    pencil.onMouseDrag(erasePosStart, erasePosEnd, Mimp::MIMP_LEFT_CLICK, image);

    buffer = image.getLayers()[0]->buffer.getBuffer();
    for (int i = 0; i < INT(size.x); i += 1) {
        for (int j = 0; j < INT(size.y); j += 1) {
            ASSERT_TRUE(buffer[i + size.x * j] == Mimp::Color::Magenta);
        }
    }
}