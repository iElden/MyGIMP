#include <gtest/gtest.h>
#include "../src/Keys.hpp"

TEST(Keys, sfmlToKey)
{
	ASSERT_TRUE(Mimp::Keys::SFMLKeyToKey(sf::Keyboard::A) == Mimp::Keys::Key::KEY_A);
	ASSERT_TRUE(Mimp::Keys::SFMLKeyToKey(sf::Keyboard::B) == Mimp::Keys::Key::KEY_B);
	ASSERT_TRUE(Mimp::Keys::SFMLKeyToKey(sf::Keyboard::C) == Mimp::Keys::Key::KEY_C);
	ASSERT_TRUE(Mimp::Keys::SFMLKeyToKey(sf::Keyboard::D) == Mimp::Keys::Key::KEY_D);
	ASSERT_TRUE(Mimp::Keys::SFMLKeyToKey(sf::Keyboard::E) == Mimp::Keys::Key::KEY_E);
	ASSERT_TRUE(Mimp::Keys::SFMLKeyToKey(sf::Keyboard::F) == Mimp::Keys::Key::KEY_F);
	ASSERT_TRUE(Mimp::Keys::SFMLKeyToKey(sf::Keyboard::G) == Mimp::Keys::Key::KEY_G);
	ASSERT_TRUE(Mimp::Keys::SFMLKeyToKey(sf::Keyboard::H) == Mimp::Keys::Key::KEY_H);
	ASSERT_TRUE(Mimp::Keys::SFMLKeyToKey(sf::Keyboard::I) == Mimp::Keys::Key::KEY_I);
	ASSERT_TRUE(Mimp::Keys::SFMLKeyToKey(sf::Keyboard::J) == Mimp::Keys::Key::KEY_J);
	ASSERT_TRUE(Mimp::Keys::SFMLKeyToKey(sf::Keyboard::K) == Mimp::Keys::Key::KEY_K);
	ASSERT_TRUE(Mimp::Keys::SFMLKeyToKey(sf::Keyboard::L) == Mimp::Keys::Key::KEY_L);
	ASSERT_TRUE(Mimp::Keys::SFMLKeyToKey(sf::Keyboard::M) == Mimp::Keys::Key::KEY_M);
	ASSERT_TRUE(Mimp::Keys::SFMLKeyToKey(sf::Keyboard::N) == Mimp::Keys::Key::KEY_N);
	ASSERT_TRUE(Mimp::Keys::SFMLKeyToKey(sf::Keyboard::O) == Mimp::Keys::Key::KEY_O);
	ASSERT_TRUE(Mimp::Keys::SFMLKeyToKey(sf::Keyboard::P) == Mimp::Keys::Key::KEY_P);
	ASSERT_TRUE(Mimp::Keys::SFMLKeyToKey(sf::Keyboard::Q) == Mimp::Keys::Key::KEY_Q);
	ASSERT_TRUE(Mimp::Keys::SFMLKeyToKey(sf::Keyboard::R) == Mimp::Keys::Key::KEY_R);
	ASSERT_TRUE(Mimp::Keys::SFMLKeyToKey(sf::Keyboard::S) == Mimp::Keys::Key::KEY_S);
	ASSERT_TRUE(Mimp::Keys::SFMLKeyToKey(sf::Keyboard::T) == Mimp::Keys::Key::KEY_T);
	ASSERT_TRUE(Mimp::Keys::SFMLKeyToKey(sf::Keyboard::U) == Mimp::Keys::Key::KEY_U);
	ASSERT_TRUE(Mimp::Keys::SFMLKeyToKey(sf::Keyboard::V) == Mimp::Keys::Key::KEY_V);
	ASSERT_TRUE(Mimp::Keys::SFMLKeyToKey(sf::Keyboard::W) == Mimp::Keys::Key::KEY_W);
	ASSERT_TRUE(Mimp::Keys::SFMLKeyToKey(sf::Keyboard::X) == Mimp::Keys::Key::KEY_X);
	ASSERT_TRUE(Mimp::Keys::SFMLKeyToKey(sf::Keyboard::Y) == Mimp::Keys::Key::KEY_Y);
	ASSERT_TRUE(Mimp::Keys::SFMLKeyToKey(sf::Keyboard::Z) == Mimp::Keys::Key::KEY_Z);
	ASSERT_TRUE(Mimp::Keys::SFMLKeyToKey(sf::Keyboard::Delete) == Mimp::Keys::Key::KEY_DEL);
	ASSERT_TRUE(Mimp::Keys::SFMLKeyToKey(sf::Keyboard::Escape) == Mimp::Keys::Key::KEY_ESC);
	ASSERT_TRUE(Mimp::Keys::SFMLKeyToKey(sf::Keyboard::Up) == Mimp::Keys::Key::KEY_UP);
	ASSERT_TRUE(Mimp::Keys::SFMLKeyToKey(sf::Keyboard::Down) == Mimp::Keys::Key::KEY_DOWN);
	ASSERT_TRUE(Mimp::Keys::SFMLKeyToKey(sf::Keyboard::Left) == Mimp::Keys::Key::KEY_LEFT);
	ASSERT_TRUE(Mimp::Keys::SFMLKeyToKey(sf::Keyboard::Right) == Mimp::Keys::Key::KEY_RIGHT);
	ASSERT_TRUE(Mimp::Keys::SFMLKeyToKey(sf::Keyboard::Backspace) == Mimp::Keys::Key::KEY_UNKNOWN);
}

TEST(Keys, stringToKey)
{
	ASSERT_TRUE(Mimp::Keys::StringToKey("A") == Mimp::Keys::Key::KEY_A);
	ASSERT_TRUE(Mimp::Keys::StringToKey("B") == Mimp::Keys::Key::KEY_B);
	ASSERT_TRUE(Mimp::Keys::StringToKey("C") == Mimp::Keys::Key::KEY_C);
	ASSERT_TRUE(Mimp::Keys::StringToKey("D") == Mimp::Keys::Key::KEY_D);
	ASSERT_TRUE(Mimp::Keys::StringToKey("E") == Mimp::Keys::Key::KEY_E);
	ASSERT_TRUE(Mimp::Keys::StringToKey("F") == Mimp::Keys::Key::KEY_F);
	ASSERT_TRUE(Mimp::Keys::StringToKey("G") == Mimp::Keys::Key::KEY_G);
	ASSERT_TRUE(Mimp::Keys::StringToKey("H") == Mimp::Keys::Key::KEY_H);
	ASSERT_TRUE(Mimp::Keys::StringToKey("I") == Mimp::Keys::Key::KEY_I);
	ASSERT_TRUE(Mimp::Keys::StringToKey("J") == Mimp::Keys::Key::KEY_J);
	ASSERT_TRUE(Mimp::Keys::StringToKey("K") == Mimp::Keys::Key::KEY_K);
	ASSERT_TRUE(Mimp::Keys::StringToKey("L") == Mimp::Keys::Key::KEY_L);
	ASSERT_TRUE(Mimp::Keys::StringToKey("M") == Mimp::Keys::Key::KEY_M);
	ASSERT_TRUE(Mimp::Keys::StringToKey("N") == Mimp::Keys::Key::KEY_N);
	ASSERT_TRUE(Mimp::Keys::StringToKey("O") == Mimp::Keys::Key::KEY_O);
	ASSERT_TRUE(Mimp::Keys::StringToKey("P") == Mimp::Keys::Key::KEY_P);
	ASSERT_TRUE(Mimp::Keys::StringToKey("Q") == Mimp::Keys::Key::KEY_Q);
	ASSERT_TRUE(Mimp::Keys::StringToKey("R") == Mimp::Keys::Key::KEY_R);
	ASSERT_TRUE(Mimp::Keys::StringToKey("S") == Mimp::Keys::Key::KEY_S);
	ASSERT_TRUE(Mimp::Keys::StringToKey("T") == Mimp::Keys::Key::KEY_T);
	ASSERT_TRUE(Mimp::Keys::StringToKey("U") == Mimp::Keys::Key::KEY_U);
	ASSERT_TRUE(Mimp::Keys::StringToKey("V") == Mimp::Keys::Key::KEY_V);
	ASSERT_TRUE(Mimp::Keys::StringToKey("W") == Mimp::Keys::Key::KEY_W);
	ASSERT_TRUE(Mimp::Keys::StringToKey("X") == Mimp::Keys::Key::KEY_X);
	ASSERT_TRUE(Mimp::Keys::StringToKey("Y") == Mimp::Keys::Key::KEY_Y);
	ASSERT_TRUE(Mimp::Keys::StringToKey("Z") == Mimp::Keys::Key::KEY_Z);
	ASSERT_TRUE(Mimp::Keys::StringToKey("Del") == Mimp::Keys::Key::KEY_DEL);
	ASSERT_TRUE(Mimp::Keys::StringToKey("Esc") == Mimp::Keys::Key::KEY_ESC);
	ASSERT_TRUE(Mimp::Keys::StringToKey("Up") == Mimp::Keys::Key::KEY_UP);
	ASSERT_TRUE(Mimp::Keys::StringToKey("Down") == Mimp::Keys::Key::KEY_DOWN);
	ASSERT_TRUE(Mimp::Keys::StringToKey("Left") == Mimp::Keys::Key::KEY_LEFT);
	ASSERT_TRUE(Mimp::Keys::StringToKey("Right") == Mimp::Keys::Key::KEY_RIGHT);
	ASSERT_TRUE(Mimp::Keys::StringToKey("Unknown") == Mimp::Keys::Key::KEY_UNKNOWN);
	ASSERT_TRUE(Mimp::Keys::StringToKey(":") == Mimp::Keys::Key::KEY_UNKNOWN);
}

TEST(Keys, keyToString)
{
	ASSERT_TRUE(Mimp::Keys::KeyToString(Mimp::Keys::Key::KEY_A) == "A");
	ASSERT_TRUE(Mimp::Keys::KeyToString(Mimp::Keys::Key::KEY_B) == "B");
	ASSERT_TRUE(Mimp::Keys::KeyToString(Mimp::Keys::Key::KEY_C) == "C");
	ASSERT_TRUE(Mimp::Keys::KeyToString(Mimp::Keys::Key::KEY_D) == "D");
	ASSERT_TRUE(Mimp::Keys::KeyToString(Mimp::Keys::Key::KEY_E) == "E");
	ASSERT_TRUE(Mimp::Keys::KeyToString(Mimp::Keys::Key::KEY_F) == "F");
	ASSERT_TRUE(Mimp::Keys::KeyToString(Mimp::Keys::Key::KEY_G) == "G");
	ASSERT_TRUE(Mimp::Keys::KeyToString(Mimp::Keys::Key::KEY_H) == "H");
	ASSERT_TRUE(Mimp::Keys::KeyToString(Mimp::Keys::Key::KEY_I) == "I");
	ASSERT_TRUE(Mimp::Keys::KeyToString(Mimp::Keys::Key::KEY_J) == "J");
	ASSERT_TRUE(Mimp::Keys::KeyToString(Mimp::Keys::Key::KEY_K) == "K");
	ASSERT_TRUE(Mimp::Keys::KeyToString(Mimp::Keys::Key::KEY_L) == "L");
	ASSERT_TRUE(Mimp::Keys::KeyToString(Mimp::Keys::Key::KEY_M) == "M");
	ASSERT_TRUE(Mimp::Keys::KeyToString(Mimp::Keys::Key::KEY_N) == "N");
	ASSERT_TRUE(Mimp::Keys::KeyToString(Mimp::Keys::Key::KEY_O) == "O");
	ASSERT_TRUE(Mimp::Keys::KeyToString(Mimp::Keys::Key::KEY_P) == "P");
	ASSERT_TRUE(Mimp::Keys::KeyToString(Mimp::Keys::Key::KEY_Q) == "Q");
	ASSERT_TRUE(Mimp::Keys::KeyToString(Mimp::Keys::Key::KEY_R) == "R");
	ASSERT_TRUE(Mimp::Keys::KeyToString(Mimp::Keys::Key::KEY_S) == "S");
	ASSERT_TRUE(Mimp::Keys::KeyToString(Mimp::Keys::Key::KEY_T) == "T");
	ASSERT_TRUE(Mimp::Keys::KeyToString(Mimp::Keys::Key::KEY_U) == "U");
	ASSERT_TRUE(Mimp::Keys::KeyToString(Mimp::Keys::Key::KEY_V) == "V");
	ASSERT_TRUE(Mimp::Keys::KeyToString(Mimp::Keys::Key::KEY_W) == "W");
	ASSERT_TRUE(Mimp::Keys::KeyToString(Mimp::Keys::Key::KEY_X) == "X");
	ASSERT_TRUE(Mimp::Keys::KeyToString(Mimp::Keys::Key::KEY_Y) == "Y");
	ASSERT_TRUE(Mimp::Keys::KeyToString(Mimp::Keys::Key::KEY_Z) == "Z");
	ASSERT_TRUE(Mimp::Keys::KeyToString(Mimp::Keys::Key::KEY_DEL) == "Del");
	ASSERT_TRUE(Mimp::Keys::KeyToString(Mimp::Keys::Key::KEY_ESC) == "Esc");
	ASSERT_TRUE(Mimp::Keys::KeyToString(Mimp::Keys::Key::KEY_UP) == "Up");
	ASSERT_TRUE(Mimp::Keys::KeyToString(Mimp::Keys::Key::KEY_DOWN) == "Down");
	ASSERT_TRUE(Mimp::Keys::KeyToString(Mimp::Keys::Key::KEY_LEFT) == "Left");
	ASSERT_TRUE(Mimp::Keys::KeyToString(Mimp::Keys::Key::KEY_RIGHT) == "Right");
	ASSERT_TRUE(Mimp::Keys::KeyToString(Mimp::Keys::Key::KEY_UNKNOWN) == "Unknown");
}

TEST(Keys, testKeyCombination)
{
	ASSERT_TRUE(Mimp::Keys::KeyCombination({Mimp::Keys::Key::KEY_R, true, false, false}).toString() == "Ctrl + R");
	ASSERT_TRUE(Mimp::Keys::KeyCombination({Mimp::Keys::Key::KEY_R, false, true, false}).toString() == "Shift + R");
	ASSERT_TRUE(Mimp::Keys::KeyCombination({Mimp::Keys::Key::KEY_R, false, false, true}).toString() == "Alt + R");
	ASSERT_TRUE(Mimp::Keys::KeyCombination({Mimp::Keys::Key::KEY_R, true, false, true}).toString() == "Ctrl + Alt + R");
	ASSERT_TRUE(Mimp::Keys::KeyCombination({Mimp::Keys::Key::KEY_R, true, true, true}).toString() == "Ctrl + Shift + Alt + R");
	ASSERT_TRUE(Mimp::Keys::KeyCombination({Mimp::Keys::Key::KEY_R, true, true, false}).toString() == "Ctrl + Shift + R");
}

TEST(Keys, getKeyName)
{
	ASSERT_TRUE(Mimp::Keys::KeyCombination({Mimp::Keys::Key::KEY_R, true, false, false}).getKeyName() == "R");
	ASSERT_TRUE(Mimp::Keys::KeyCombination({Mimp::Keys::Key::KEY_B, false, true, false}).getKeyName() == "B");
	ASSERT_TRUE(Mimp::Keys::KeyCombination({Mimp::Keys::Key::KEY_E, false, false, true}).getKeyName() == "E");
	ASSERT_TRUE(Mimp::Keys::KeyCombination({Mimp::Keys::Key::KEY_F, true, false, true}).getKeyName() == "F");
	ASSERT_TRUE(Mimp::Keys::KeyCombination({Mimp::Keys::Key::KEY_P, true, true, true}).getKeyName() == "P");
	ASSERT_TRUE(Mimp::Keys::KeyCombination({Mimp::Keys::Key::KEY_UNKNOWN, true, true, false}).getKeyName() == "Unknown");
}

TEST(Keys, keyCombinationFromString)
{
	auto kc1 = Mimp::Keys::KeyCombination({Mimp::Keys::Key::KEY_R, true, false, false});
	ASSERT_TRUE(kc1.toString() == "Ctrl + R");
	kc1.fromString("Ctrl + U");
	ASSERT_TRUE(kc1.toString() == "Ctrl + U");
	ASSERT_TRUE(kc1.key == Mimp::Keys::KEY_U);
	ASSERT_TRUE(kc1.control);
	ASSERT_FALSE(kc1.alt);
	ASSERT_FALSE(kc1.shift);

	auto kc2 = Mimp::Keys::KeyCombination({Mimp::Keys::Key::KEY_UNKNOWN, false, true, true});
	ASSERT_EQ(kc2.toString(), "Shift + Alt + Unknown");
	kc2.fromString("Shift + Z");
	ASSERT_TRUE(kc2.toString() == "Shift + Z");
	ASSERT_TRUE(kc2.key == Mimp::Keys::KEY_Z);
	ASSERT_FALSE(kc2.control);
	ASSERT_FALSE(kc2.alt);
	ASSERT_TRUE(kc2.shift);

	auto kc3 = Mimp::Keys::KeyCombination({Mimp::Keys::Key::KEY_P, true, true, false});
	ASSERT_TRUE(kc3.toString() == "Ctrl + Shift + P");
	kc3.fromString("Ctrl + Shift + Alt + :");
	ASSERT_TRUE(kc3.toString() == "Ctrl + Shift + Alt + Unknown");
	ASSERT_TRUE(kc3.key == Mimp::Keys::KEY_UNKNOWN);
	ASSERT_TRUE(kc3.control);
	ASSERT_TRUE(kc3.alt);
	ASSERT_TRUE(kc3.shift);
}
