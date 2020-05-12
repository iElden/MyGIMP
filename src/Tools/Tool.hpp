//
// Created by Gegel85 on 06/04/2020.
//

#ifndef MYGIMP_TOOL_HPP
#define MYGIMP_TOOL_HPP


#include <TGUI/Widgets/ScrollablePanel.hpp>
#include "../Data/MouseClick.hpp"
#include "../Image.hpp"

namespace Mimp
{
	//! @brief Class Tool
	class Tool {
	private:
		//! @brief Name of the tool
		std::string _name;

	public:
		//! @brief Constructor of the Tool class
		//! @param name Name of the tool
		explicit Tool(const std::string &name) : _name(name) {};
		//! @brief Get the name of the tool
		//! @return std::string Name of the tool
		std::string getName() const
		{
			return this->_name;
		};
		//! @brief On Select, do the following actions
		virtual void onSelect() {};
		//! @brief On Unselect, do the following actions
		virtual void onUnselect() {};
		virtual void onMouseRelease(Vector2<int>, MouseClick, Image &) {};
		//! @brief When mouse is dragging, apply the tool to the new position
		//! @param oldPos Old Pos
		//! @param newPos New Pos
		//! @param click Mouse click state
		//! @param layer Layer used
		virtual void onMouseDrag(Vector2<int> oldPos, Vector2<int> newPos, MouseClick click, Image &image) = 0;
		//! @brief When mouse is clicked, apply the tool to the position
		//! @param pos Position of the tool
		//! @param click Mouse click state
		//! @param layer Layer used
		virtual void onClick(Vector2<int> pos, MouseClick click, Image &image) = 0;
		//! @brief Get the Parameters Panel Pointer
		//! @return tgui::ScrollablePanel::Ptr Pointer containing the parameters panel
		virtual tgui::ScrollablePanel::Ptr getParametersPanel() = 0;
	};
}


#endif //MYGIMP_TOOL_HPP
