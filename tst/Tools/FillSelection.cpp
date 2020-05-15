#include <gtest/gtest.h>
#include <TGUI/TGUI.hpp>
#include "../../src/Tools/FillSelection.hpp"

TEST(FillSelection, getPanel) {
    tgui::Gui gui{};
    Mimp::ToolBox toolbox{gui};
    Mimp::FillSelection fs{toolbox};

    ASSERT_TRUE(fs.getParametersPanel()->getSize().x == 0);
    ASSERT_TRUE(fs.getParametersPanel()->getSize().y == 0);
}

TEST(FillSelection, fillNoSelectedLayer) {
    tgui::Gui gui{};
    Mimp::ToolBox toolbox{gui};
    Mimp::FillSelection fs{toolbox};
    Mimp::LayerManager lm({10, 10}, 1, Mimp::Color::White);
    Mimp::Image image({10, 10}, lm);

    ASSERT_TRUE(image.getLayers().size() == 1);
    auto buffer = image.getLayers()[0].buffer.getBuffer();
    for (int i = 0; i < 100; i += 1) {
        ASSERT_TRUE(buffer[i] == Mimp::Color::White);
    }

    fs.onClick({0, 0}, Mimp::MIMP_LEFT_CLICK, image);
    for (int i = 0; i < 100; i += 1) {
        ASSERT_TRUE(buffer[i] == Mimp::Color::White);
    }
}

TEST(FillSelection, fillDefaultColorWholeLayer) {
    tgui::Gui gui{};
    Mimp::ToolBox toolbox{gui};
    Mimp::FillSelection fs{toolbox};
    Mimp::LayerManager lm({10, 10}, 1, Mimp::Color::White);
    Mimp::Image image({10, 10}, lm);

    image.selectedArea.selectAll();

    ASSERT_TRUE(image.getLayers().size() == 1);
    auto buffer = image.getLayers()[0].buffer.getBuffer();
    for (int i = 0; i < 100; i += 1) {
        ASSERT_TRUE(buffer[i] == Mimp::Color::White);
    }

    fs.onClick({0, 0}, Mimp::MIMP_LEFT_CLICK, image);
    for (int i = 0; i < 100; i += 1) {
        ASSERT_TRUE(buffer[i] == Mimp::Color::Black);
    }
}

TEST(FillSelection, fillDefaultColorPartLayer) {
    tgui::Gui gui{};
    Mimp::ToolBox toolbox{gui};
    Mimp::FillSelection fs{toolbox};
    Mimp::LayerManager lm({10, 10}, 1, Mimp::Color::White);
    Mimp::Image image({10, 10}, lm);

    image.selectedArea.selectAll();

    ASSERT_TRUE(image.getLayers().size() == 1);
    auto buffer = image.getLayers()[0].buffer.getBuffer();
    for (int i = 0; i < 100; i += 1) {
        ASSERT_TRUE(buffer[i] == Mimp::Color::White);
    }

    fs.onClick({0, 0}, Mimp::MIMP_LEFT_CLICK, image);
    for (int i = 0; i < 100; i += 1) {
        ASSERT_TRUE(buffer[i] == Mimp::Color::Black);
    }
}

TEST(FillSelection, fillWithCustomLeftColorWholeLayer) {
    tgui::Gui gui{};
    Mimp::ToolBox toolbox{gui};
    Mimp::FillSelection fs{toolbox};
    Mimp::LayerManager lm({10, 10}, 1, Mimp::Color::White);
    Mimp::Image image({10, 10}, lm);

    image.selectedArea.selectAll();

    ASSERT_TRUE(image.getLayers().size() == 1);
    auto buffer = image.getLayers()[0].buffer.getBuffer();
    for (int i = 0; i < 100; i += 1) {
        ASSERT_TRUE(buffer[i] == Mimp::Color::White);
    }

    toolbox.setSelectedColor(Mimp::MIMP_LEFT_CLICK, Mimp::Color::Magenta);
    fs.onClick({0, 0}, Mimp::MIMP_LEFT_CLICK, image);
    for (int i = 0; i < 100; i += 1) {
        ASSERT_TRUE(buffer[i] == Mimp::Color::Magenta);
    }
}

TEST(FillSelection, fillWhenLayerIsLocked) {
    tgui::Gui gui{};
    Mimp::ToolBox toolbox{gui};
    Mimp::FillSelection fs{toolbox};
    Mimp::LayerManager lm({10, 10}, 1, Mimp::Color::White);
    Mimp::Image image({10, 10}, lm);

    image.selectedArea.selectAll();

    ASSERT_TRUE(image.getLayers().size() == 1);
    image.getLayers()[0].locked = true;
    auto buffer = image.getLayers()[0].buffer.getBuffer();
    for (int i = 0; i < 100; i += 1) {
        ASSERT_TRUE(buffer[i] == Mimp::Color::White);
    }

    fs.onClick({0, 0}, Mimp::MIMP_LEFT_CLICK, image);
    for (int i = 0; i < 100; i += 1) {
        ASSERT_TRUE(buffer[i] == Mimp::Color::White);
    }
}