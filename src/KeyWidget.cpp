#include "KeyWidget.hpp"
#include "Keys.hpp"

void Mimp::KeyWidget::keyPressed(const sf::Event::KeyEvent &event)
{
	if (this->editing) {
		this->setText(Keys::KeyToString(Keys::SFMLKeyToKey(event.code)));

		this->editing = !this->editing;
	}
}

void Mimp::KeyWidget::leftMousePressed(tgui::Vector2f pos)
{
	this->editing = true;
}