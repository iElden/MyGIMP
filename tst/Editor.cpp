#include <gtest/gtest.h>
#include "../src/Editor.hpp"

TEST(Editor, sfmlKeysConversion) {
    ASSERT_TRUE(Mimp::Editor::SFMLKeyToKey(sf::Keyboard::A) == Mimp::Key::KEY_A);
    ASSERT_TRUE(Mimp::Editor::SFMLKeyToKey(sf::Keyboard::B) == Mimp::Key::KEY_B);
    ASSERT_TRUE(Mimp::Editor::SFMLKeyToKey(sf::Keyboard::C) == Mimp::Key::KEY_C);
    ASSERT_TRUE(Mimp::Editor::SFMLKeyToKey(sf::Keyboard::D) == Mimp::Key::KEY_D);
    ASSERT_TRUE(Mimp::Editor::SFMLKeyToKey(sf::Keyboard::E) == Mimp::Key::KEY_E);
    ASSERT_TRUE(Mimp::Editor::SFMLKeyToKey(sf::Keyboard::F) == Mimp::Key::KEY_F);
    ASSERT_TRUE(Mimp::Editor::SFMLKeyToKey(sf::Keyboard::G) == Mimp::Key::KEY_G);
    ASSERT_TRUE(Mimp::Editor::SFMLKeyToKey(sf::Keyboard::H) == Mimp::Key::KEY_H);
    ASSERT_TRUE(Mimp::Editor::SFMLKeyToKey(sf::Keyboard::I) == Mimp::Key::KEY_I);
    ASSERT_TRUE(Mimp::Editor::SFMLKeyToKey(sf::Keyboard::J) == Mimp::Key::KEY_J);
    ASSERT_TRUE(Mimp::Editor::SFMLKeyToKey(sf::Keyboard::K) == Mimp::Key::KEY_K);
    ASSERT_TRUE(Mimp::Editor::SFMLKeyToKey(sf::Keyboard::L) == Mimp::Key::KEY_L);
    ASSERT_TRUE(Mimp::Editor::SFMLKeyToKey(sf::Keyboard::M) == Mimp::Key::KEY_M);
    ASSERT_TRUE(Mimp::Editor::SFMLKeyToKey(sf::Keyboard::N) == Mimp::Key::KEY_N);
    ASSERT_TRUE(Mimp::Editor::SFMLKeyToKey(sf::Keyboard::O) == Mimp::Key::KEY_O);
    ASSERT_TRUE(Mimp::Editor::SFMLKeyToKey(sf::Keyboard::P) == Mimp::Key::KEY_P);
    ASSERT_TRUE(Mimp::Editor::SFMLKeyToKey(sf::Keyboard::Q) == Mimp::Key::KEY_Q);
    ASSERT_TRUE(Mimp::Editor::SFMLKeyToKey(sf::Keyboard::R) == Mimp::Key::KEY_R);
    ASSERT_TRUE(Mimp::Editor::SFMLKeyToKey(sf::Keyboard::S) == Mimp::Key::KEY_S);
    ASSERT_TRUE(Mimp::Editor::SFMLKeyToKey(sf::Keyboard::T) == Mimp::Key::KEY_T);
    ASSERT_TRUE(Mimp::Editor::SFMLKeyToKey(sf::Keyboard::U) == Mimp::Key::KEY_U);
    ASSERT_TRUE(Mimp::Editor::SFMLKeyToKey(sf::Keyboard::V) == Mimp::Key::KEY_V);
    ASSERT_TRUE(Mimp::Editor::SFMLKeyToKey(sf::Keyboard::W) == Mimp::Key::KEY_W);
    ASSERT_TRUE(Mimp::Editor::SFMLKeyToKey(sf::Keyboard::X) == Mimp::Key::KEY_X);
    ASSERT_TRUE(Mimp::Editor::SFMLKeyToKey(sf::Keyboard::Y) == Mimp::Key::KEY_Y);
    ASSERT_TRUE(Mimp::Editor::SFMLKeyToKey(sf::Keyboard::Z) == Mimp::Key::KEY_Z);
    ASSERT_TRUE(Mimp::Editor::SFMLKeyToKey(sf::Keyboard::Delete) == Mimp::Key::KEY_DEL);
    ASSERT_TRUE(Mimp::Editor::SFMLKeyToKey(sf::Keyboard::Escape) == Mimp::Key::KEY_ESC);
    ASSERT_TRUE(Mimp::Editor::SFMLKeyToKey(sf::Keyboard::Up) == Mimp::Key::KEY_UP);
    ASSERT_TRUE(Mimp::Editor::SFMLKeyToKey(sf::Keyboard::Down) == Mimp::Key::KEY_DOWN);
    ASSERT_TRUE(Mimp::Editor::SFMLKeyToKey(sf::Keyboard::Left) == Mimp::Key::KEY_LEFT);
    ASSERT_TRUE(Mimp::Editor::SFMLKeyToKey(sf::Keyboard::Right) == Mimp::Key::KEY_RIGHT);
    ASSERT_TRUE(Mimp::Editor::SFMLKeyToKey(sf::Keyboard::Backspace) == Mimp::Key::KEY_UNKNOWN);
}