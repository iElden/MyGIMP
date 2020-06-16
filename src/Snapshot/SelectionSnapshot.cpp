/*
** EPITECH PROJECT, 2020
** MyGimp
** File description:
** SelectionSnapshot.cpp
*/

#include "SelectionSnapshot.hpp"
#include "../Editor.hpp"

Mimp::SelectionSnapshot::SelectionSnapshot(const Mimp::SelectedArea &oldSelection):
	_oldSelection(std::make_shared<SelectedArea>(oldSelection))
{

}

void Mimp::SelectionSnapshot::undo(Image &image, Editor &)
{
	image.selectedArea.swap(this->_oldSelection);
}

void Mimp::SelectionSnapshot::redo(Image &image, Editor &editor)
{
	this->undo(image, editor);
}
