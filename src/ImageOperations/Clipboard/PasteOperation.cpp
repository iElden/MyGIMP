//
// Created by andgel on 23/05/2020
//

#include <clip.h>
#include <iostream>
#include <iomanip>
#include "PasteOperation.hpp"

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

	template<typename T>
	static void print_channel(const clip::image& img,
				  const clip::image_spec& spec,
				  const std::string& channel_name,
				  const int channel_mask,
				  const int channel_shift,
				  const int channel_fill_width,
				  const int pixel_size) {
		std::cout << channel_name << ":\n";
		for (unsigned long y=0; y<spec.height; ++y) {
			const char* p = (img.data()+spec.bytes_per_row*y);
			std::cout << "  ";
			for (unsigned long x=0; x<spec.width; ++x, p += pixel_size) {
				std::cout << std::right
					  << std::hex
					  << std::setw(channel_fill_width)
					  << (((*((T*)p)) & channel_mask) >> channel_shift) << " ";
			}
			std::cout << "\n";
		}
	}

	template<typename T>
	static void print_channels(const clip::image& img,
				   const clip::image_spec& spec,
				   const int channel_fill_width,
				   int pixel_size = sizeof(T)) {
		print_channel<T>(img, spec, "Red",   spec.red_mask,   spec.red_shift,   channel_fill_width, pixel_size);
		print_channel<T>(img, spec, "Green", spec.green_mask, spec.green_shift, channel_fill_width, pixel_size);
		print_channel<T>(img, spec, "Blue",  spec.blue_mask,  spec.blue_shift,  channel_fill_width, pixel_size);
		if (spec.alpha_mask)
			print_channel<T>(img, spec, "Alpha", spec.alpha_mask, spec.alpha_shift, channel_fill_width, pixel_size);
	}

	/*void PasteOperation::click(tgui::Gui &, Mimp::Image &image) const
	{
		if (!clip::has(clip::image_format())) {
			std::cout << "Clipboard doesn't contain an image\n";
			return;
		}

		clip::image img;
		if (!clip::get_image(img)) {
			std::cout << "Error getting image from clipboard\n";
			return;
		}

		clip::image_spec spec = img.spec();

		std::cout << "Image in clipboard "
			  << spec.width << "x" << spec.height
			  << " (" << spec.bits_per_pixel << "bpp)\n"
			  << "Format:" << "\n"
			  << std::hex
			  << "  Red   mask: " << spec.red_mask << "\n"
			  << "  Green mask: " << spec.green_mask << "\n"
			  << "  Blue  mask: " << spec.blue_mask << "\n"
			  << "  Alpha mask: " << spec.alpha_mask << "\n"
			  << std::dec
			  << "  Red   shift: " << spec.red_shift << "\n"
			  << "  Green shift: " << spec.green_shift << "\n"
			  << "  Blue  shift: " << spec.blue_shift << "\n"
			  << "  Alpha shift: " << spec.alpha_shift << "\n";

		switch (spec.bits_per_pixel) {
			case 16:
				print_channels<uint16_t>(img, spec, 2);
				break;
			case 24:
				print_channels<uint32_t>(img, spec, 2, 3);
				break;
			case 32:
				print_channels<uint32_t>(img, spec, 2);
				break;
			case 64:
				print_channels<uint64_t>(img, spec, 4);
				break;
		}
	}*/

	void PasteOperation::click(tgui::Gui &, Mimp::Image &image) const
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
		image.getLayers().addLayer(Layer{{
			static_cast<unsigned int>(specs.width),
			static_cast<unsigned int>(specs.height)
		}, arr});
		delete[] arr;
	}
}