#include <gtest/gtest.h>
#include <TGUI/TGUI.hpp>
#include "../../src/Tools/SelectionTool.hpp"

/*
class STTest : public Mimp::SelectionTool {
public:
    STTest(Mimp::ToolBox &tb) : Mimp::SelectionTool("sttest", tb) {}

    void onSelect() override {
        Mimp::SelectionTool::onSelect();
    }

    void clear() override {
        Mimp::SelectionTool::clear();
    }

    void onUnselect() override {
        Mimp::Tool::onUnselect();
    }

    void onMouseRelease(Mimp::Vector2<int> vector2, Mimp::MouseClick click, Mimp::Image &image) override {
        Mimp::Tool::onMouseRelease(vector2, click, image);
    }

    void onMouseDrag(Mimp::Vector2<int>, Mimp::Vector2<int>, Mimp::MouseClick,
                     Mimp::Image &) override {}

    void onClick(Mimp::Vector2<int>, Mimp::MouseClick, Mimp::Image &) override {}

    tgui::ScrollablePanel::Ptr getParametersPanel() override { return nullptr; }

};

TEST(SelectionTool, DUMMY) {
    tgui::Gui gui{};
    Mimp::ToolBox toolbox{gui};
    STTest st{toolbox};
    Mimp::Image i({0, 0});

    st.onSelect();
    st.onUnselect();
    st.onMouseRelease({0, 0}, Mimp::MIMP_LEFT_CLICK, i);
    st.clear();
}
*/