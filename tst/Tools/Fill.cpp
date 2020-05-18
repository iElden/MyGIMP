#include <gtest/gtest.h>
#include <TGUI/TGUI.hpp>
#include "../../src/Tools/Fill.hpp"

TEST(Fill, getDefaultPanelValues) {
    tgui::Gui gui{};
    Mimp::ToolBox toolbox{gui};
    Mimp::Fill fill{toolbox};

    auto panel = fill.getParametersPanel();
    auto toleranceSlider = panel->get<tgui::Slider>("Tolerance");
    auto alpha = panel->get<tgui::CheckBox>("Alpha");
    auto tolerancePreview = panel->get<tgui::TextBox>("TolerancePreview");

    ASSERT_TRUE(toleranceSlider->getValue() == 0.0);
    ASSERT_TRUE(alpha);
    ASSERT_TRUE(tolerancePreview->getText() == "0");
}

TEST(Fill, fillBlankImageClick) {
    tgui::Gui gui{};
    Mimp::ToolBox toolbox{gui};
    Mimp::Fill fill{toolbox};
    Mimp::LayerManager lm({10, 10}, 1, Mimp::Color::White);
    Mimp::Image image({10, 10}, lm);

    ASSERT_EQ(image.getLayers().size(), 1);
    auto buffer = image.getLayers()[0].buffer.getBuffer();
    for (int i = 0; i < 100; i += 1) {
        ASSERT_TRUE(buffer[i] == Mimp::Color::White);
    }

    fill.onClick({3, 3}, Mimp::MIMP_LEFT_CLICK, image);
    buffer = image.getLayers()[0].buffer.getBuffer();
    for (int i = 0; i < 100; i += 1) {
        ASSERT_TRUE(buffer[i] == Mimp::Color::Black);
    }
}

TEST(Fill, fillBlankImageClickOutOfBound) {
    tgui::Gui gui{};
    Mimp::ToolBox toolbox{gui};
    Mimp::Fill fill{toolbox};
    Mimp::LayerManager lm({10, 10}, 1, Mimp::Color::White);
    Mimp::Image image({10, 10}, lm);

    ASSERT_EQ(image.getLayers().size(), 1);
    auto buffer = image.getLayers()[0].buffer.getBuffer();
    for (int i = 0; i < 100; i += 1) {
        ASSERT_TRUE(buffer[i] == Mimp::Color::White);
    }

    fill.onClick({35, 3}, Mimp::MIMP_LEFT_CLICK, image);
    buffer = image.getLayers()[0].buffer.getBuffer();
    for (int i = 0; i < 100; i += 1) {
        ASSERT_TRUE(buffer[i] == Mimp::Color::White);
    }
}

TEST(Fill, fillBlankImageClickSameColor) {
    tgui::Gui gui{};
    Mimp::ToolBox toolbox{gui};
    Mimp::Fill fill{toolbox};
    Mimp::LayerManager lm({10, 10}, 1, Mimp::Color::White);
    Mimp::Image image({10, 10}, lm);

    ASSERT_EQ(image.getLayers().size(), 1);
    auto buffer = image.getLayers()[0].buffer.getBuffer();
    for (int i = 0; i < 100; i += 1) {
        ASSERT_TRUE(buffer[i] == Mimp::Color::White);
    }

    fill.onClick({3, 3}, Mimp::MIMP_RIGHT_CLICK, image);
    buffer = image.getLayers()[0].buffer.getBuffer();
    for (int i = 0; i < 100; i += 1) {
        ASSERT_TRUE(buffer[i] == Mimp::Color::White);
    }
}

TEST(Fill, fillBlankImageDrag) {
    tgui::Gui gui{};
    Mimp::ToolBox toolbox{gui};
    Mimp::Fill fill{toolbox};
    Mimp::LayerManager lm({10, 10}, 1, Mimp::Color::White);
    Mimp::Image image({10, 10}, lm);

    ASSERT_EQ(image.getLayers().size(), 1);
    auto buffer = image.getLayers()[0].buffer.getBuffer();
    for (int i = 0; i < 100; i += 1) {
        ASSERT_TRUE(buffer[i] == Mimp::Color::White);
    }

    fill.onMouseDrag({0, 0}, {3, 3}, Mimp::MIMP_RIGHT_CLICK, image);
    buffer = image.getLayers()[0].buffer.getBuffer();
    for (int i = 0; i < 100; i += 1) {
        ASSERT_TRUE(buffer[i] == Mimp::Color::White);
    }
}

TEST(Fill, fillWithTransparentColor) {
    tgui::Gui gui{};
    Mimp::ToolBox toolbox{gui};
    Mimp::Fill fill{toolbox};
    Mimp::LayerManager lm({10, 10}, 1, Mimp::Color::Red);
    Mimp::Image image({10, 10}, lm);
    Mimp::Color c(0x11223300);

    ASSERT_EQ(image.getLayers().size(), 1);
    auto buffer = image.getLayers()[0].buffer.getBuffer();
    for (int i = 0; i < 100; i += 1) {
        ASSERT_TRUE(buffer[i] == Mimp::Color::Red);
    }

    toolbox.setSelectedColor(Mimp::MIMP_RIGHT_CLICK, c);
    fill.onClick({3, 3}, Mimp::MIMP_RIGHT_CLICK, image);
    buffer = image.getLayers()[0].buffer.getBuffer();
    for (int i = 0; i < 100; i += 1) {
        ASSERT_TRUE(buffer[i] == c);
    }
}

TEST(Fill, fillWhenLayerIsLocked) {
    tgui::Gui gui{};
    Mimp::ToolBox toolbox{gui};
    Mimp::Fill fill{toolbox};
    Mimp::LayerManager lm({10, 10}, 1, Mimp::Color::Red);
    Mimp::Image image({10, 10}, lm);

    ASSERT_EQ(image.getLayers().size(), 1);
    image.getLayers()[0].locked = true;
    auto buffer = image.getLayers()[0].buffer.getBuffer();
    for (int i = 0; i < 100; i += 1) {
        ASSERT_TRUE(buffer[i] == Mimp::Color::Red);
    }

    fill.onClick({3, 3}, Mimp::MIMP_LEFT_CLICK, image);
    buffer = image.getLayers()[0].buffer.getBuffer();
    for (int i = 0; i < 100; i += 1) {
        ASSERT_TRUE(buffer[i] == Mimp::Color::Red);
    }
}