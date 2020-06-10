/*
** EPITECH PROJECT, 2020
** MyGimp
** File description:
** FrameBufferSnapshot.cpp
*/

#include "FrameBufferSnapshot.hpp"
#include "../Editor.hpp"

Mimp::FrameBufferSnapshot::FrameBufferSnapshot(const FrameBuffer &frameBuffer, int layerNb):
	layerNumber(layerNb),
	oldBuffer(std::make_shared<FrameBuffer>(frameBuffer))
{}

void Mimp::FrameBufferSnapshot::undo(Image &image, Editor &)
{
	image.getLayers()[this->layerNumber].buffer.swap(this->oldBuffer);
}

void Mimp::FrameBufferSnapshot::redo(Image &image, Editor &editor)
{
	this->undo(image, editor);
}