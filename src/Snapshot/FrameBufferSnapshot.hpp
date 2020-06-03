/*
** EPITECH PROJECT, 2020
** MyGimp
** File description:
** FrameBufferSnapshot.hpp
*/
#ifndef MYGIMP_FRAMEBUFFERSNAPSHOT_HPP
#define MYGIMP_FRAMEBUFFERSNAPSHOT_HPP


#include "Snapshot.hpp"
#include "../Layer/FrameBuffer.hpp"

namespace Mimp {
	class FrameBufferSnapshot : public Snapshot {
		int layerNumber;
		std::shared_ptr<FrameBuffer> oldBuffer;
	public:
		FrameBufferSnapshot(const FrameBuffer &frameBuffer, int layerNb);
		void undo(Image &image) override;
		void redo(Image &image) override;
	};
}


#endif //MYGIMP_FRAMEBUFFERSNAPSHOT_HPP
