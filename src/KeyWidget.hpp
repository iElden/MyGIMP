#ifndef MYGIMP_KEYWIDGET_HPP
#define MYGIMP_KEYWIDGET_HPP

#include <TGUI/TGUI.hpp>

namespace Mimp {
	class KeyWidget : public tgui::Button {
	public:
		typedef std::shared_ptr<KeyWidget> Ptr;

		explicit KeyWidget(std::string &key) { this->setText(key);}

		static KeyWidget::Ptr create(std::string &&key) {
			return std::make_shared<KeyWidget>(key);
		}

		void leftMousePressed(tgui::Vector2f pos) override;

		void keyPressed(const sf::Event::KeyEvent &event) override;

	private:
		bool editing = false;
	};

}

#endif //MYGIMP_KEYWIDGET_HPP
