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

TEST(Fill, fillBlankImage1) {
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

TEST(Fill, fillBlankImage2) {
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

TEST(Fill, fillBlankImage3) {
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

TEST(Fill, fillBlankImage4) {
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