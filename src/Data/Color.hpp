//
// Created by Gegel85 on 06/04/2020.
//

#ifndef MYGIMP_COLOR_HPP
#define MYGIMP_COLOR_HPP


#include <SFML/Graphics/Color.hpp>

namespace Mimp
{
    //! @brief Struct containing the color values.
    //! @details This structure contains red, green, blue, and alpha value for a color.
	struct Color {
		unsigned char r;
		unsigned char g;
		unsigned char b;
		unsigned char a;

        //! @brief Constructor of the Struct Color
        //! @details Copy construct the color structure with a color in hexadecimal.
        //! @param color The color to be copy in hexadecimal.
		Color(unsigned int color) noexcept;
        //! @brief Constructor of the Struct Color
        //! @details Copy construct the color structure with rgba values.
        //! @param r Hexadecimal value for red.
        //! @param g Hexadecimal value for green.
        //! @param b Hexadecimal value for blue.
        //! @param a Hexadecimal value for alpha. Default value is 255.
		Color(unsigned char r, unsigned char g, unsigned char b, unsigned char a = 255) noexcept;
		//! @brief Implicit Operator cast in unsigned int
		//! @details Converts a color to unsigned int using assignation (unsigned int = Color)
		operator unsigned int() const noexcept;
        //! @brief Implicit Operator cast in sf::Color (SFML)
        //! @details Converts a color to sf::Color (SFML) using assignation (sf::Color = Color)
		operator sf::Color() const noexcept;
        //! @brief Operator + for colors
        //! @details color + color / Adds two colors together
        //! @param other Color to add
		Color operator+(const Color &other);

		//! @brief Color Black
		static const Color Black      ;
        //! @brief Color LightGray
		static const Color LightGray  ;
        //! @brief Color DarkGray
		static const Color DarkGray   ;
        //! @brief Color White
		static const Color White      ;
        //! @brief Color Red
		static const Color Red        ;
        //! @brief Color Blue
		static const Color Blue       ;
        //! @brief Color Green
		static const Color Green      ;
        //! @brief Color Magenta
		static const Color Magenta    ;
        //! @brief Color Yellow
		static const Color Yellow     ;
        //! @brief Color Cyan
		static const Color Cyan       ;
        //! @brief Color Transparent
		static const Color Transparent;
	};
}


#endif //MYGIMP_COLOR_HPP
