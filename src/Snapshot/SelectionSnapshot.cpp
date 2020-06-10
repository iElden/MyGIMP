/*
** EPITECH PROJECT, 2020
** MyGimp
** File description:
** SelectionSnapshot.cpp
*/

#include "SelectionSnapshot.hpp"
#include "../Image.hpp"

Mimp::SelectionSnapshot::SelectionSnapshot(const Mimp::SelectedArea &oldSelection):
	_oldSelection(std::make_shared<SelectedArea>(oldSelection))
{

}

void Mimp::SelectionSnapshot::undo(Mimp::Image &image)
{
	image.selectedArea->printDebug();
	_oldSelection->printDebug();
	image.selectedArea.swap(this->_oldSelection);
}

void Mimp::SelectionSnapshot::redo(Mimp::Image &image)
{
	this->undo(image);
}
