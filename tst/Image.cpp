#include <gtest/gtest.h>
#include "../src/Exceptions.hpp"
#include "../src/Utils.hpp"
#include "../src/Image.hpp"

TEST(Image, getSize)
{
    Mimp::Image i({300, 800});

    ASSERT_EQ(i.getImageSize().x, 300);
    ASSERT_EQ(i.getImageSize().y, 800);
}

TEST(Image, noLayerAtConstruction)
{
    Mimp::Image i({300, 800});

    ASSERT_EQ(i.getLayers().size(), 1);
}

TEST(Image, layerAtConstruction)
{
    Mimp::LayerManager l(Mimp::Vector2<unsigned>{800, 600});
    Mimp::Image i({300, 60}, l);

    ASSERT_EQ(i.getLayers().size(), 1);
    ASSERT_EQ(i.getLayers()[0].getSize().x, 800);
    ASSERT_EQ(i.getLayers()[0].getSize().y, 600);
}

TEST(Image, exportNullPath)
{
    Mimp::Image i({300, 60});

    try {
        i.exportImage("");
    } catch (Mimp::ExportErrorException &e) {
        ASSERT_EQ(std::string(e.what()), "Cannot export to file ");
    }
}

TEST(Image, exportCurrentFolder)
{
    Mimp::Image i({300, 60});

    try {
        i.exportImage(".");
    } catch (Mimp::ExportErrorException &e) {
        ASSERT_EQ(std::string(e.what()), "Cannot export to file .");
    }
}

TEST(Image, exportParentFolder)
{
    Mimp::Image i({300, 60});

    try {
        i.exportImage("..");
    } catch (Mimp::ExportErrorException &e) {
        ASSERT_EQ(std::string(e.what()), "Cannot export to file ..");
    }
}

TEST(Image, getLayer) {
    Mimp::Image i({300, 400});

    auto l = i.getSelectedLayer();
    ASSERT_EQ(l.getSize().x, 300);
    ASSERT_EQ(l.getSize().y, 400);
}