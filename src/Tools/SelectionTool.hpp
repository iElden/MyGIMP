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
	class SelectionTool : public Tool {
	protected:
		ToolBox &_toolBox;
	public:
		SelectionTool(const std::string &name, ToolBox &);
		void onSelect() override;
		virtual void clear() {};
	};
}


#endif //MYGIMP_SELECTIONTOOL_HPP
