//
// Created by jmartin on 4/15/20.
//

#include <criterion/criterion.h>
#include <criterion/redirect.h>
#include <iostream>
#include <sstream>
#include <zconf.h>
#include <TGUI/TGUI.hpp>
#include <SFML/Graphics.hpp>
#include "../src/ToolBox.hpp"
#include "../src/Tools/Tool.hpp"

Test(ToolBox, GetSelectedToolTest)
{
    tgui::Gui gui{};
    Mimp::ToolBox toolbox{gui};

    cr_assert_not_null(toolbox.getSelectedTool());
}

Test(ToolBox, GetWindowTest)
{
    tgui::Gui gui{};
    Mimp::ToolBox toolbox{gui};

    cr_assert_not_null(toolbox.getWindow());
}