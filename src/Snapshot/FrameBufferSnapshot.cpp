/*
** EPITECH PROJECT, 2020
** MyGimp
** File description:
** FrameBufferSnapshot.cpp
*/

#include "FrameBufferSnapshot.hpp"
#include "../Image.hpp"

Mimp::FrameBufferSnapshot::FrameBufferSnapshot(const FrameBuffer &frameBuffer, int layerNb):
	layerNumber(layerNb),
	oldBuffer(std::make_shared<FrameBuffer>(frameBuffer))
{}

void Mimp::FrameBufferSnapshot::undo(Mimp::Image &image)
{
	image.getLayers()[this->layerNumber].buffer.swap(oldBuffer);
}

void Mimp::FrameBufferSnapshot::redo(Mimp::Image &image)
{
	this->undo(image);
}