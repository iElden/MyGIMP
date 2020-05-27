#include <gtest/gtest.h>
#include <TGUI/TGUI.hpp>
#include "../src/ToolBox.hpp"

TEST(ToolBox, GetSelectedToolTest)
{
    tgui::Gui gui{};
    Mimp::ToolBox toolbox{gui};

    EXPECT_TRUE(toolbox.getSelectedTool() != nullptr);
}

TEST(ToolBox, GetWindowTest)
{
    tgui::Gui gui{};
    Mimp::ToolBox toolbox{gui};

    EXPECT_TRUE(toolbox.getWindow() != nullptr);
}

TEST(ToolBox, GetSelectedColorTest)
{
    tgui::Gui gui{};
    Mimp::ToolBox toolbox{gui};

    ASSERT_EQ(toolbox.getSelectedColor(Mimp::MIMP_LEFT_CLICK), Mimp::Color::Black);
    ASSERT_EQ(toolbox.getSelectedColor(Mimp::MIMP_RIGHT_CLICK), Mimp::Color::White);
}

TEST(ToolBox, SetSelectedColorTest)
{
    tgui::Gui gui{};
    Mimp::ToolBox toolbox{gui};

    toolbox.setSelectedColor(Mimp::MIMP_LEFT_CLICK, Mimp::Color::Red);
    toolbox.setSelectedColor(Mimp::MIMP_RIGHT_CLICK, Mimp::Color::Cyan);

    ASSERT_EQ(toolbox.getSelectedColor(Mimp::MIMP_LEFT_CLICK), Mimp::Color::Red);
    ASSERT_EQ(toolbox.getSelectedColor(Mimp::MIMP_RIGHT_CLICK), Mimp::Color::Cyan);
}

TEST(ToolBox, getTools)
{
	tgui::Gui gui{};
	Mimp::ToolBox toolbox{gui};

	ASSERT_TRUE(toolbox.getTools().size() != 0);
}
