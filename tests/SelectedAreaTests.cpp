//
// Created by jmartin on 4/22/20.
//

#include <criterion/criterion.h>
#include <criterion/redirect.h>
#include <iostream>
#include <zconf.h>
#include "../src/SelectedArea.hpp"

Test(ToolBox, AddTest)
{
	Mimp::SelectedArea selectedArea;

	selectedArea.add(5, 5);
	selectedArea.add({10, 10});

	cr_assert_eq(selectedArea.isAnAreaSelected(), true);
}

Test(ToolBox, clearTest)
{
	Mimp::SelectedArea selectedArea;

	selectedArea.add(5, 5);
	selectedArea.add({10, 10});

	selectedArea.clear();

	cr_assert_eq(selectedArea.isAnAreaSelected(), false);
}