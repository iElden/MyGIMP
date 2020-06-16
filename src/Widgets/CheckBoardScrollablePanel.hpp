//
// Created by Gegel85 on 01/06/2020.
//

#ifndef MYGIMP_CHECKBOARDSCROLLABLEPANEL_HPP
#define MYGIMP_CHECKBOARDSCROLLABLEPANEL_HPP


#include <TGUI/TGUI.hpp>

namespace Mimp
{
	class CheckBoardScrollablePanel : public tgui::ScrollablePanel {
	private:
		sf::Vector2f _maxSize = {std::numeric_limits<float>::infinity(), std::numeric_limits<float>::infinity()};

	public:
		typedef std::shared_ptr<CheckBoardScrollablePanel> Ptr; //!< Shared widget pointer

		CheckBoardScrollablePanel(tgui::Layout2d size = {"100%", "100%"}, tgui::Vector2f contentSize = {0, 0});

		static CheckBoardScrollablePanel::Ptr create(tgui::Layout2d size = {"100%", "100%"}, tgui::Vector2f contentSize = {0, 0});
		void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

		const sf::Vector2f &getMaxSize() const;

		void setMaxSize(const sf::Vector2f &maxSize);
	};
}


#endif //MYGIMP_CHECKBOARDSCROLLABLEPANEL_HPP
