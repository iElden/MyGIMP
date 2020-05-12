#include <gtest/gtest.h>
#include "../src/SelectedArea.hpp"

TEST(SelectedArea, AddTest) {
    Mimp::SelectedArea selectedArea(10, 10);

    selectedArea.add(5, 5);
    selectedArea.add({10, 10});

    ASSERT_EQ(selectedArea.isAnAreaSelected(), true);
}

TEST(SelectedArea, clearTest) {
    Mimp::SelectedArea selectedArea(10, 10);

    selectedArea.add(5, 5);
    selectedArea.add({10, 10});

    selectedArea.clear();

    ASSERT_EQ(selectedArea.isAnAreaSelected(), false);
}
