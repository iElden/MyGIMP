//
// Created by Gegel85 on 06/04/2020.
//

#ifndef MYGIMP_COLOR_HPP
#define MYGIMP_COLOR_HPP


#include <SFML/Graphics/Color.hpp>

namespace Mimp
{
	struct Color {
		unsigned char r;
		unsigned char g;
		unsigned char b;
		unsigned char a;

		Color(unsigned int color) noexcept;
		Color(unsigned char r, unsigned char g, unsigned char b, unsigned char a = 255) noexcept;
		operator unsigned int() const noexcept;
		operator sf::Color() const noexcept;
		Color operator+(const Color &other);

		static const Color Black      ;
		static const Color LightGray  ;
		static const Color DarkGray   ;
		static const Color White      ;
		static const Color Red        ;
		static const Color Blue       ;
		static const Color Green      ;
		static const Color Magenta    ;
		static const Color Yellow     ;
		static const Color Cyan       ;
		static const Color Transparent;
	};
}


#endif //MYGIMP_COLOR_HPP
