//
// Created by Gegel85 on 06/04/2020.
//

#ifndef MYGIMP_TOOL_HPP
#define MYGIMP_TOOL_HPP


#include <TGUI/Widgets/ScrollablePanel.hpp>
#include "../Data/MouseClick.hpp"
#include "../Image.hpp"
#include "../Keys.hpp"
#include "../Action.hpp"

namespace Mimp {
	//! @brief Define a Tool
	class Tool : public Action {
	private:
		std::string _name; //!< Name of the Tool

	public:
		//! @brief Construct a Tool
		//! @param name Name of the tool
		explicit Tool(const std::string &name) : _name(name)
		{
			this->setKeyCombination({Keys::KEY_UNKNOWN, false, false, false});
		};

		//! @brief Get the name of the Tool
		//! @return std::string Name of the Tool
		const std::string getName()
		{
			return this->_name;
		};

		//! @brief Handle the selection of the Tool.
		virtual void onSelect()
		{};

		//! @brief Handle the unselection of the Tool.
		virtual void onUnselect()
		{};

		//! @brief Handle the mouse release of the Tool.
		//! @param pos The position of the mouse
		//! @param click Mouse click state
		//! @param image The Image to edit
		virtual void onMouseRelease([[maybe_unused]] Vector2<int> pos, [[maybe_unused]] MouseClick click, [[maybe_unused]] Image &image)
		{};

		//! @brief Handle the mouse dragging of the Tool.
		//! @param oldPos Old position of the mouse
		//! @param newPos New position of the mouse
		//! @param click Mouse click state
		//! @param image The Image to edit
		virtual void onMouseDrag(Vector2<int> oldPos, Vector2<int> newPos, MouseClick click, Image &image) = 0;

		//! @brief Handle the mouse click of the Tool.
		//! @param pos Position of the tool
		//! @param click Mouse click state
		//! @param image The Image to edit
		virtual void onClick(Vector2<int> pos, MouseClick click, Image &image) = 0;

		//! @brief Get the parameters panel for the Tool.
		//! @return tgui::ScrollablePanel::Ptr Pointer containing the parameters panel
		virtual tgui::ScrollablePanel::Ptr getParametersPanel() = 0;

		virtual bool isEditing() { return false; }
	};
}


#endif //MYGIMP_TOOL_HPP
