/*
** EPITECH PROJECT, 2020
** MyGimp
** File description:
** FrameBufferSnapshot.cpp
*/

#include "FrameBufferSnapshot.hpp"

Mimp::FrameBufferSnapshot::FrameBufferSnapshot(const FrameBuffer &frameBuffer, int layerNb):
	layerNumber(layerNb),
	oldBuffer(frameBuffer)
{}

void Mimp::FrameBufferSnapshot::rollback(Mimp::Image &image)
{
	image.getLayers()[this->layerNumber].buffer = oldBuffer;
}
