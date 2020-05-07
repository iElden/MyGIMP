#include <gtest/gtest.h>
#include "../src/Exceptions.hpp"
#include "../src/Utils.hpp"
#include "../src/Image.hpp"

TEST(ImageManipulation, getSize)
{
    Mimp::Image i({300, 800});

    ASSERT_EQ(i.getImageSize().x, 300);
    ASSERT_EQ(i.getImageSize().y, 800);
}

TEST(ImageManipulation, noLayerAtConstruction)
{
    Mimp::Image i({300, 800});

    ASSERT_EQ(i.getLayers().size(), 1);
}

TEST(ImageManipulation, layerAtConstruction)
{
    Mimp::LayerManager l(Mimp::Vector2<unsigned>{800, 600});
    Mimp::Image i({300, 60}, l);

    ASSERT_EQ(i.getLayers().size(), 1);
    ASSERT_EQ(i.getLayers()[0].getSize().x, 800);
    ASSERT_EQ(i.getLayers()[0].getSize().y, 600);
}

TEST(ImageManipulation, exportNullPath)
{
    Mimp::Image i({300, 60});

    try {
        i.exportImage("");
    } catch (Mimp::ExportErrorException &e) {
        ASSERT_EQ(std::string(e.what()), "Cannot export to file ");
    }
}

TEST(ImageManipulation, exportCurrentFolder)
{
    Mimp::Image i({300, 60});

    try {
        i.exportImage(".");
    } catch (Mimp::ExportErrorException &e) {
        ASSERT_EQ(std::string(e.what()), "Cannot export to file .");
    }
}

TEST(ImageManipulation, exportParentFolder)
{
    Mimp::Image i({300, 60});

    try {
        i.exportImage("..");
    } catch (Mimp::ExportErrorException &e) {
        ASSERT_EQ(std::string(e.what()), "Cannot export to file ..");
    }
}