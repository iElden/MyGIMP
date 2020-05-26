#include "KeyWidget.hpp"
#include "Keys.hpp"

void Mimp::KeyWidget::keyPressed(const sf::Event::KeyEvent &event)
{
	if (this->_editing) {
		this->setText(Keys::KeyToString(Keys::SFMLKeyToKey(event.code)));
		(*this->_ptr)[this->_entry].key = Keys::SFMLKeyToKey(event.code);
		this->_editing = !this->_editing;
	}
}

void Mimp::KeyWidget::leftMousePressed(tgui::Vector2f)
{
	this->_editing = true;
}