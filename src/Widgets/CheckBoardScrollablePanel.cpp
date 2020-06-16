//
// Created by Gegel85 on 01/06/2020.
//

#include "CheckBoardScrollablePanel.hpp"

namespace Mimp
{
	void CheckBoardScrollablePanel::draw(sf::RenderTarget &target, sf::RenderStates states) const
	{
		sf::RectangleShape rect;
		bool dark;
		sf::Vector2f size = this->getSize();
		sf::Vector2f realSize = {
			std::min(size.x, this->_maxSize.x),
			std::min(size.y, this->_maxSize.y)
		};
		sf::RenderStates oldStates = states;

		states.transform.translate(getPosition());
		rect.setOutlineThickness(0);
		for (unsigned x = 0; x < realSize.x; x += 10) {
			dark = x % 20;
			for (unsigned y = 0; y < realSize.y; y += 10) {
				rect.setFillColor(dark ? sf::Color{0x888888FF} : sf::Color::White);
				rect.setPosition(x, y);
				rect.setSize({
					realSize.x - x > 10 ? 10 : realSize.x - x,
					realSize.y - y > 10 ? 10 : realSize.y - y
				});
				target.draw(rect, states);
				dark = !dark;
			}
		}
		ScrollablePanel::draw(target, oldStates);
	}

	CheckBoardScrollablePanel::CheckBoardScrollablePanel(tgui::Layout2d size, tgui::Vector2f contentSize) :
		tgui::ScrollablePanel(size, contentSize)
	{
	}

	CheckBoardScrollablePanel::Ptr CheckBoardScrollablePanel::create(tgui::Layout2d size, tgui::Vector2f contentSize)
	{
		return std::make_shared<CheckBoardScrollablePanel>(size, contentSize);
	}

	const sf::Vector2f &CheckBoardScrollablePanel::getMaxSize() const
	{
		return this->_maxSize;
	}

	void CheckBoardScrollablePanel::setMaxSize(const sf::Vector2f &maxSize)
	{
		this->_maxSize = maxSize;
	}
}