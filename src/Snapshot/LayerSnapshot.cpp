/*
** EPITECH PROJECT, 2020
** MyGimp
** File description:
** LayerSnapshot.cpp
*/

#include "LayerSnapshot.hpp"
#include "../Editor.hpp"

Mimp::LayerSnapshot::LayerSnapshot(const Layer &layer, int layerNb):
		layerNumber(layerNb),
		oldLayer(std::make_shared<Layer>(layer))
{}

void Mimp::LayerSnapshot::undo(Image &image, Editor &editor)
{
	image.getLayers().getLayerPtr(this->layerNumber).swap(this->oldLayer);
	editor.refreshSelectedLayerWidgets();
}

void Mimp::LayerSnapshot::redo(Image &image, Editor &editor)
{
	this->undo(image, editor);
}