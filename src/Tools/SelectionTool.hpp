/*
** EPITECH PROJECT, 2020
** MyGimp
** File description:
** SelectionTools.hpp
*/
#ifndef MYGIMP_SELECTIONTOOL_HPP
#define MYGIMP_SELECTIONTOOL_HPP

#include "../Image.hpp"
#include "Tool.hpp"
#include "../ToolBox.hpp"

namespace Mimp {
	//! @brief Define a SelectionTool
	class SelectionTool : public Tool {
	protected:
		ToolBox &_toolBox; //!< Define the ToolBox containing the Tool.
	public:
		//! @brief Construct a Selection Tool.
		//! @param name Name of the Tool
		//! @param tb ToolBox containing the SelectionTool
		SelectionTool(const std::string &name, ToolBox &tb);

		//! @brief Clear the selection.
		void onSelect() override;

		//! @brief Does nothing.
		virtual void clear() {};
	};
}


#endif //MYGIMP_SELECTIONTOOL_HPP
