#include <gtest/gtest.h>
#include "../src/Widgets/KeyWidget.hpp"

TEST(KeyWidget, constructor)
{
	auto ptr = std::make_shared<std::map<std::string, Mimp::Keys::KeyCombination>>();
	std::string s = "A";
	Mimp::KeyWidget kw{s, ptr, ""};

	ASSERT_TRUE(kw.getText() == "A");
}

TEST(KeyWidget, create)
{
	auto ptr = std::make_shared<std::map<std::string, Mimp::Keys::KeyCombination>>();
	auto kw = Mimp::KeyWidget::create("A", ptr, "");

	ASSERT_TRUE(kw->getText() == "A");
}

TEST(KeyWidget, buttonClickNotFocus)
{
	auto ptr = std::make_shared<std::map<std::string, Mimp::Keys::KeyCombination>>();
	auto kw = Mimp::KeyWidget::create("A", ptr, "");

	sf::Event::KeyEvent k{};

	k.code = sf::Keyboard::R;

	kw->keyPressed(k);

	ASSERT_TRUE(kw->getText() == "A");
}


TEST(KeyWidget, buttonClickWithFocus)
{
	auto ptr = std::make_shared<std::map<std::string, Mimp::Keys::KeyCombination>>();
	(*ptr)["A"] = {Mimp::Keys::KEY_U, false, false, true};
	(*ptr)["R"] = {Mimp::Keys::KEY_O, true, false, true};
	auto kw = Mimp::KeyWidget::create("A", ptr, "R");

	sf::Event::KeyEvent k{};

	k.code = sf::Keyboard::R;

	ASSERT_TRUE((*ptr)["R"].getKeyName() == "O");
	kw->leftMousePressed({});
	kw->keyPressed(k);

	ASSERT_TRUE(kw->getText() == "R");
	ASSERT_TRUE((*ptr)["R"].getKeyName() == "R");
}