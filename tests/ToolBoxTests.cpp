//
// Created by jmartin on 4/15/20.
//

#include <criterion/criterion.h>
#include <criterion/redirect.h>
#include <iostream>
#include <zconf.h>
#include <TGUI/TGUI.hpp>
#include "../src/ToolBox.hpp"

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

Test(ToolBox, GetSelectedColorTest)
{
	tgui::Gui gui{};
	Mimp::ToolBox toolbox{gui};

	cr_assert_eq(toolbox.getSelectedColor(Mimp::MIMP_LEFT_CLICK), Mimp::Color::Black);
	cr_assert_eq(toolbox.getSelectedColor(Mimp::MIMP_RIGHT_CLICK), Mimp::Color::White);
}

Test(ToolBox, SetSelectedColorTest)
{
	tgui::Gui gui{};
	Mimp::ToolBox toolbox{gui};

	toolbox.setSelectedColor(Mimp::MIMP_LEFT_CLICK, Mimp::Color::Red);
	toolbox.setSelectedColor(Mimp::MIMP_RIGHT_CLICK, Mimp::Color::Cyan);

	cr_assert_eq(toolbox.getSelectedColor(Mimp::MIMP_LEFT_CLICK), Mimp::Color::Red);
	cr_assert_eq(toolbox.getSelectedColor(Mimp::MIMP_RIGHT_CLICK), Mimp::Color::Cyan);
}