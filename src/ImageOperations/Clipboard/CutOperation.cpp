//
// Created by Gegel85 on 24/05/2020.
//

#include "CutOperation.hpp"
#include "clip.h"
#include "../../Utils.hpp"

namespace Mimp
{
	CutOperation::CutOperation() :
		ImageOperation({"Edit", "Cut"}, {Keys::KEY_X, true, false, false})
	{

	}

	void CutOperation::click(tgui::Gui &, CanvasWidget::Ptr image, tgui::ChildWindow::Ptr, Editor &) const
	{
		image->takeFrameBufferSnapshot();

		Vector2<int> topLeft = {INT32_MAX, INT32_MAX};
		Vector2<int> bottomRight = {INT32_MIN, INT32_MIN};
		unsigned *pxBuffer;

		for (auto &pt : image->selectedArea->getPoints()) {
			topLeft.x = std::min(topLeft.x, pt.x);
			topLeft.y = std::min(topLeft.y, pt.y);
			bottomRight.x = std::max(bottomRight.x, pt.x);
			bottomRight.y = std::max(bottomRight.y, pt.y);
		}

		Vector2<unsigned> size(bottomRight.x - topLeft.x + 1, bottomRight.y - topLeft.y + 1);
		clip::image_spec spec;
		auto &layer = image->getSelectedLayer();

		pxBuffer = new unsigned[size.x * size.y];
		std::memset(pxBuffer, 0, size.x * size.y * sizeof(*pxBuffer));
		for (auto &pt : image->selectedArea->getPoints()){
			auto coord = (pt - topLeft);

			pxBuffer[coord.x + coord.y * size.x] = layer.buffer->getPixel(pt - layer.pos);
			layer.buffer->setPixel(pt - layer.pos, Color::Transparent);
		}

		spec.width = size.x;
		spec.height = size.y;
		spec.bits_per_pixel = 32;
		spec.bytes_per_row = spec.width * 4;
		spec.red_mask   = 0xff000000;
		spec.green_mask = 0x00ff0000;
		spec.blue_mask  = 0x0000ff00;
		spec.alpha_mask = 0x000000ff;
		spec.red_shift = 24;
		spec.green_shift = 16;
		spec.blue_shift = 8;
		spec.alpha_shift = 0;

		clip::image img(pxBuffer, spec);

		clip::set_image(img);
		delete[] pxBuffer;
	}
}