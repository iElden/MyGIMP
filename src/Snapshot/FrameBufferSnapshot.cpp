/*
** EPITECH PROJECT, 2020
** MyGimp
** File description:
** FrameBufferSnapshot.cpp
*/

#include "FrameBufferSnapshot.hpp"
#include "../Image.hpp"

Mimp::FrameBufferSnapshot::FrameBufferSnapshot(std::shared_ptr<FrameBuffer> frameBuffer, int layerNb):
	layerNumber(layerNb),
	oldBuffer(*frameBuffer)
{}

void Mimp::FrameBufferSnapshot::rollback(Mimp::Image &image)
{
	image.getLayers()[this->layerNumber].buffer = std::make_shared<FrameBuffer>(oldBuffer);
}
