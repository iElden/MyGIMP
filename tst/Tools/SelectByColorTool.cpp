#include <gtest/gtest.h>
#include <TGUI/TGUI.hpp>
#include "../../src/Tools/SelectByColorTool.hpp"

TEST(SelectByColorTool, getPanel) {
    tgui::Gui gui{};
    Mimp::ToolBox toolbox{gui};
    Mimp::SelectByColorTool sbct{toolbox};

    ASSERT_TRUE(sbct.getParametersPanel()->getSize().x == 0);
    ASSERT_TRUE(sbct.getParametersPanel()->getSize().y == 0);
}

TEST(SelectByColorTool, selectOnDrag) {
    tgui::Gui gui{};
    Mimp::ToolBox toolbox{gui};
    Mimp::SelectByColorTool sbct{toolbox};
    Mimp::LayerManager lm({10, 10}, 1, Mimp::Color::Magenta);
    Mimp::Image image({10, 10}, lm);

    ASSERT_TRUE(image.selectedArea.getPoints().size() == 0);
    sbct.onMouseDrag({0, 0}, {10, 9}, Mimp::MIMP_LEFT_CLICK, image);
    ASSERT_TRUE(image.selectedArea.getPoints().size() == 0);
}

TEST(SelectByColorTool, selectLayerWithDefaultColor) {
    tgui::Gui gui{};
    Mimp::ToolBox toolbox{gui};
    Mimp::SelectByColorTool sbct{toolbox};
    Mimp::LayerManager lm({10, 10}, 1, Mimp::Color::Magenta);
    Mimp::Image image({10, 10}, lm);

    ASSERT_TRUE(image.selectedArea.getPoints().size() == 0);
    sbct.onMouseDrag({0, 0}, {10, 9}, Mimp::MIMP_LEFT_CLICK, image);
    ASSERT_TRUE(image.selectedArea.getPoints().size() == 0);
}

TEST(SelectByColorTool, selectLayerWithColor) {
    tgui::Gui gui{};
    Mimp::ToolBox toolbox{gui};
    Mimp::SelectByColorTool sbct{toolbox};
    Mimp::LayerManager lm({10, 10}, 1, Mimp::Color::Black);
    Mimp::Image image({10, 10}, lm);

    ASSERT_TRUE(image.selectedArea.getPoints().size() == 0);
    sbct.onClick({0, 0}, Mimp::MIMP_LEFT_CLICK, image);
    ASSERT_TRUE(image.selectedArea.getPoints().size() == 100);
}

TEST(SelectByColorTool, selectLayerWithColorWithoutAPixel) {
    tgui::Gui gui{};
    Mimp::ToolBox toolbox{gui};
    Mimp::SelectByColorTool sbct{toolbox};
    Mimp::LayerManager lm({10, 10}, 1, Mimp::Color::Black);
    Mimp::Image image({10, 10}, lm);

    image.getLayers()[0]->buffer.drawPixel({3, 8}, Mimp::Color::Magenta);
    ASSERT_TRUE(image.selectedArea.getPoints().size() == 0);
    sbct.onClick({0, 0}, Mimp::MIMP_LEFT_CLICK, image);
    ASSERT_TRUE(image.selectedArea.getPoints().size() == 99);
    ASSERT_FALSE(image.selectedArea.pointInMap(3, 8));
    ASSERT_TRUE(image.selectedArea.pointInMap(2, 8));
}

TEST(SelectByColorTool, selectLayerByAPixelOnly) {
    tgui::Gui gui{};
    Mimp::ToolBox toolbox{gui};
    Mimp::SelectByColorTool sbct{toolbox};
    Mimp::LayerManager lm({10, 10}, 1, Mimp::Color::Black);
    Mimp::Image image({10, 10}, lm);

    image.getLayers()[0]->buffer.drawPixel({3, 8}, Mimp::Color::Magenta);
    ASSERT_TRUE(image.selectedArea.getPoints().size() == 0);
    sbct.onClick({3, 8}, Mimp::MIMP_LEFT_CLICK, image);
    ASSERT_TRUE(image.selectedArea.getPoints().size() == 1);
    ASSERT_TRUE(image.selectedArea.pointInMap(3, 8));
    ASSERT_FALSE(image.selectedArea.pointInMap(2, 8));
}

/*
TEST(ColorPick, pickImageColor) {
    tgui::Gui gui{};
    Mimp::ToolBox toolbox{gui};
    Mimp::ColorPick cp{toolbox};
    Mimp::LayerManager lm({10, 10}, 1, Mimp::Color::Magenta);
    Mimp::Image image({10, 10}, lm);

    ASSERT_TRUE(toolbox.getSelectedColor(Mimp::MIMP_LEFT_CLICK) == Mimp::Color::Black);
    cp.onClick({5, 5}, Mimp::MIMP_LEFT_CLICK, image);
    ASSERT_TRUE(toolbox.getSelectedColor(Mimp::MIMP_LEFT_CLICK) == Mimp::Color::Magenta);
}

TEST(ColorPick, pickColorOnDrag) {
    tgui::Gui gui{};
    Mimp::ToolBox toolbox{gui};
    Mimp::ColorPick cp{toolbox};
    Mimp::LayerManager lm({10, 10}, 1, Mimp::Color::Magenta);
    Mimp::Image image({10, 10}, lm);

    ASSERT_TRUE(toolbox.getSelectedColor(Mimp::MIMP_LEFT_CLICK) == Mimp::Color::Black);
    cp.onMouseDrag({0, 0}, {10, 10}, Mimp::MIMP_LEFT_CLICK, image);
    ASSERT_TRUE(toolbox.getSelectedColor(Mimp::MIMP_LEFT_CLICK) == Mimp::Color::Black);
}*/