#include <gtest/gtest.h>
#include "../../src/ImageOperations/ImageOperationFactory.hpp"

TEST(IOFactory, testBuildsSize) {
    Mimp::ImageOperationFactory factory;

    ASSERT_TRUE(factory.buildAll().size() != 0);
}
