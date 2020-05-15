#include <gtest/gtest.h>
#include <TGUI/TGUI.hpp>
#include "../../src/Tools/Pencil.hpp"

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

// onMouseDrag
// onClick