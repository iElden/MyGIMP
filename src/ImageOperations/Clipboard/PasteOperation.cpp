//
// Created by andgel on 23/05/2020
//

#include <clip.h>
#include <iostream>
#include <iomanip>
#include "PasteOperation.hpp"
#include "../../CanvasWidget.hpp"
#include "../../Editor.hpp"

namespace Mimp
{
	template<typename type>
	Color *convertImage(const clip::image &image, const clip::image_spec &specs, unsigned pixelSize = sizeof(type))
	{
		auto *result = new Color[specs.width * specs.height];

		for (unsigned y = 0; y < specs.height; y++) {
			for (unsigned x = 0; x < specs.width; x++) {
				type elem = *reinterpret_cast<const type *>(image.data() + specs.bytes_per_row * y + x * pixelSize);

				result[y * specs.width + x] = {
					static_cast<unsigned char>((elem & specs.red_mask) >> specs.red_shift),
					static_cast<unsigned char>((elem & specs.green_mask) >> specs.green_shift),
					static_cast<unsigned char>((elem & specs.blue_mask) >> specs.blue_shift),
					static_cast<unsigned char>(specs.alpha_mask ? (elem & specs.alpha_mask) >> specs.alpha_shift : 255)
				};
			}
		}
		return result;
	}

	PasteOperation::PasteOperation() :
		ImageOperation({"Edit", "Paste"}, {KEY_V, true, false, false})
	{
	}

	void PasteOperation::click(tgui::Gui &, CanvasWidget::Ptr image, tgui::ChildWindow::Ptr win, Editor &editor) const
	{
		if (!clip::has(clip::image_format()))
			return;

		clip::image img;

		if (!clip::get_image(img))
			return;

		if (!img.is_valid())
			return;

		auto specs = img.spec();
		Color *arr = nullptr;

		switch (specs.bits_per_pixel) {
		case 16:
			arr = convertImage<uint16_t>(img, specs);
			break;
		case 24:
			arr = convertImage<uint32_t>(img, specs, 3);
			break;
		case 32:
			arr = convertImage<uint32_t>(img, specs);
			break;
		case 64:
			arr = convertImage<uint64_t>(img, specs);
			break;
		}
		image->getLayers().addLayer(Layer{{
			static_cast<unsigned int>(specs.width),
			static_cast<unsigned int>(specs.height)
		}, arr});
		delete[] arr;
		editor._makeLayersPanel(win, image);
	}
}