/*
** EPITECH PROJECT, 2020
** MyGimp
** File description:
** SelectionTools.cpp
*/
#include "SelectionTool.hpp"

Mimp::SelectionTool::SelectionTool(const std::string &name, ToolBox &toolBox):
	Tool(name),
	_toolBox(toolBox)
{}

void Mimp::SelectionTool::onSelect()
{
	this->clear();
}
