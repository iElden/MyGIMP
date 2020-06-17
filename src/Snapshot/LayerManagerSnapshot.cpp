/*
** EPITECH PROJECT, 2020
** MyGimp
** File description:
** LayerManagerSnapshot.cpp
*/

#include "LayerManagerSnapshot.hpp"
#include "../Image.hpp"

Mimp::LayerManagerSnapshot::LayerManagerSnapshot(const Mimp::LayerManager &layerManager):
		oldLayerManager(std::make_shared<LayerManager>(layerManager))
{
}

void Mimp::LayerManagerSnapshot::undo(Mimp::Image &image, Mimp::Editor &)
{
	image.getLayerManagerPtr().swap(oldLayerManager);
}

void Mimp::LayerManagerSnapshot::redo(Mimp::Image &image, Mimp::Editor &editor)
{
	this->undo(image, editor);
}
