/*
** EPITECH PROJECT, 2020
** MyGimp
** File description:
** LayerSnapshot.cpp
*/

#include "LayerSnapshot.hpp"
#include "../Image.hpp"

Mimp::LayerSnapshot::LayerSnapshot(const Layer &layer, int layerNb):
		layerNumber(layerNb),
		oldLayer(std::make_shared<Layer>(layer))
{}

void Mimp::LayerSnapshot::undo(Mimp::Image &image)
{
	image.getLayers().getLayerPtr(this->layerNumber).swap(this->oldLayer);
}

void Mimp::LayerSnapshot::redo(Mimp::Image &image)
{
	this->undo(image);
}