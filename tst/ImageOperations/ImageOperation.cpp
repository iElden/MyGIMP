#include <gtest/gtest.h>
#include "../../src/ImageOperations/ImageOperation.hpp"

TEST(ImageOperation, checkKeyValues) {
    ASSERT_TRUE(Mimp::KeyToString(Mimp::Key::KEY_A) == "A");
    ASSERT_TRUE(Mimp::KeyToString(Mimp::Key::KEY_B) == "B");
    ASSERT_TRUE(Mimp::KeyToString(Mimp::Key::KEY_C) == "C");
    ASSERT_TRUE(Mimp::KeyToString(Mimp::Key::KEY_D) == "D");
    ASSERT_TRUE(Mimp::KeyToString(Mimp::Key::KEY_E) == "E");
    ASSERT_TRUE(Mimp::KeyToString(Mimp::Key::KEY_F) == "F");
    ASSERT_TRUE(Mimp::KeyToString(Mimp::Key::KEY_G) == "G");
    ASSERT_TRUE(Mimp::KeyToString(Mimp::Key::KEY_H) == "H");
    ASSERT_TRUE(Mimp::KeyToString(Mimp::Key::KEY_I) == "I");
    ASSERT_TRUE(Mimp::KeyToString(Mimp::Key::KEY_J) == "J");
    ASSERT_TRUE(Mimp::KeyToString(Mimp::Key::KEY_K) == "K");
    ASSERT_TRUE(Mimp::KeyToString(Mimp::Key::KEY_L) == "L");
    ASSERT_TRUE(Mimp::KeyToString(Mimp::Key::KEY_M) == "M");
    ASSERT_TRUE(Mimp::KeyToString(Mimp::Key::KEY_N) == "N");
    ASSERT_TRUE(Mimp::KeyToString(Mimp::Key::KEY_O) == "O");
    ASSERT_TRUE(Mimp::KeyToString(Mimp::Key::KEY_P) == "P");
    ASSERT_TRUE(Mimp::KeyToString(Mimp::Key::KEY_Q) == "Q");
    ASSERT_TRUE(Mimp::KeyToString(Mimp::Key::KEY_R) == "R");
    ASSERT_TRUE(Mimp::KeyToString(Mimp::Key::KEY_S) == "S");
    ASSERT_TRUE(Mimp::KeyToString(Mimp::Key::KEY_T) == "T");
    ASSERT_TRUE(Mimp::KeyToString(Mimp::Key::KEY_U) == "U");
    ASSERT_TRUE(Mimp::KeyToString(Mimp::Key::KEY_V) == "V");
    ASSERT_TRUE(Mimp::KeyToString(Mimp::Key::KEY_W) == "W");
    ASSERT_TRUE(Mimp::KeyToString(Mimp::Key::KEY_X) == "X");
    ASSERT_TRUE(Mimp::KeyToString(Mimp::Key::KEY_Y) == "Y");
    ASSERT_TRUE(Mimp::KeyToString(Mimp::Key::KEY_Z) == "Z");
    ASSERT_TRUE(Mimp::KeyToString(Mimp::Key::KEY_DEL) == "Del");
    ASSERT_TRUE(Mimp::KeyToString(Mimp::Key::KEY_ESC) == "Esc");
    ASSERT_TRUE(Mimp::KeyToString(Mimp::Key::KEY_UP) == "Up");
    ASSERT_TRUE(Mimp::KeyToString(Mimp::Key::KEY_DOWN) == "Down");
    ASSERT_TRUE(Mimp::KeyToString(Mimp::Key::KEY_LEFT) == "Left");
    ASSERT_TRUE(Mimp::KeyToString(Mimp::Key::KEY_RIGHT) == "Right");
    ASSERT_TRUE(Mimp::KeyToString(Mimp::Key::NB_OF_KEYS) == "Unknown");
}

TEST(ImageOperation, testKeyCombination) {
    ASSERT_TRUE(Mimp::KeyCombination({Mimp::Key::KEY_R, true, false, false}).toString() == "Ctrl + R");
    ASSERT_TRUE(Mimp::KeyCombination({Mimp::Key::KEY_R, false, true, false}).toString() == "Shift + R");
    ASSERT_TRUE(Mimp::KeyCombination({Mimp::Key::KEY_R, false, false, true}).toString() == "Alt + R");
    ASSERT_TRUE(Mimp::KeyCombination({Mimp::Key::KEY_R, true, false, true}).toString() == "Ctrl + Alt + R");
    ASSERT_TRUE(Mimp::KeyCombination({Mimp::Key::KEY_R, true, true, true}).toString() == "Ctrl + Shift + Alt + R");
    ASSERT_TRUE(Mimp::KeyCombination({Mimp::Key::KEY_R, true, true, false}).toString() == "Ctrl + Shift + R");

}

class IOTest : public Mimp::ImageOperation {
public:
    explicit IOTest(const std::vector<std::string> &&hierarchy) : Mimp::ImageOperation(
            static_cast<const std::vector<std::string> &&>(hierarchy)) {};
    explicit IOTest(const std::vector<std::string> &&hierarchy, const Mimp::KeyCombination &keys) : Mimp::ImageOperation(
            static_cast<const std::vector<std::string> &&>(hierarchy), keys) {};
private:
    void click(tgui::Gui &, Mimp::CanvasWidget::Ptr, tgui::ChildWindow::Ptr, Mimp::Editor &) const override {}
};

TEST(ImageOperation, noKeyStroke) {
    IOTest io({"test1", "test2"});

    ASSERT_FALSE(io.getKeyStroke());
}

TEST(ImageOperation, strokeOnlyA) {
    IOTest io({"test1", "test2"}, {Mimp::Key::KEY_A, false, false, false});

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
    IOTest io1({}, {Mimp::Key::KEY_A, false, false, false});
    IOTest io2({}, {Mimp::Key::NB_OF_KEYS, true, false, false});

    ASSERT_TRUE(io1.getKeyStroke() < io2.getKeyStroke());
}