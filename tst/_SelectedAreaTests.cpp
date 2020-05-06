//
// Created by jmartin on 4/22/20.
//

#include <gtest/gtest.h>
#include <iostream>
#include <zconf.h>
#include "../src/SelectedArea.hpp"

TEST(ToolBox, AddTest)
{
	Mimp::SelectedArea selectedArea(10, 10);

	selectedArea.add(5, 5);
	selectedArea.add({10, 10});

	ASSERT_EQ(selectedArea.isAnAreaSelected(), true);
}

TEST(ToolBox, clearTest)
{
	Mimp::SelectedArea selectedArea(10, 10);

	selectedArea.add(5, 5);
	selectedArea.add({10, 10});

	selectedArea.clear();

	ASSERT_EQ(selectedArea.isAnAreaSelected(), false);
}
