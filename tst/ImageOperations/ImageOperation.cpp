#include <gtest/gtest.h>
#include "../../src/ImageOperations/ImageOperation.hpp"

class IOTest : public Mimp::ImageOperation {
public:
    explicit IOTest(const std::vector<std::string> &&hierarchy) : Mimp::ImageOperation(
	    static_cast<const std::vector<std::string> &&>(hierarchy))
    {};
    explicit IOTest(const std::vector<std::string> &&hierarchy, const Mimp::Keys::KeyCombination &keys) : Mimp::ImageOperation(
	    static_cast<const std::vector<std::string> &&>(hierarchy), keys)
    {};
private:
    void click(tgui::Gui &, Mimp::CanvasWidget::Ptr, tgui::ChildWindow::Ptr, Mimp::Editor &) const override {}
};

TEST(ImageOperation, noKeyStroke) {
    IOTest io({"test1", "test2"});

    ASSERT_FALSE(io.getKeyStroke());
}

TEST(ImageOperation, strokeOnlyA) {
    IOTest io({"test1", "test2"}, {Mimp::Keys::Key::KEY_A, false, false, false});

    ASSERT_TRUE(io.getKeyStroke());
    ASSERT_TRUE(io.getKeyStroke()->toString() == "A");
}

TEST(ImageOperation, noHierarchy) {
    IOTest io({});

    ASSERT_TRUE(io.getMenuHierarchy().size() == 0);
}

TEST(ImageOperation, hasHierarchy) {
    IOTest io({"test1", "test2"});

    ASSERT_TRUE(io.getMenuHierarchy().size() == 2);
}

TEST(ImageOperation, keyComparison) {
    IOTest io1({}, {Mimp::Keys::Key::KEY_A, false, false, false});
    IOTest io2({}, {Mimp::Keys::Key::NB_OF_KEYS, true, false, false});

    ASSERT_TRUE(io1.getKeyStroke() < io2.getKeyStroke());
}