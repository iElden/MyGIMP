//
// Created by Gegel85 on 06/04/2020.
//

#ifndef MYGIMP_COLOR_HPP
#define MYGIMP_COLOR_HPP


#include <SFML/Graphics/Color.hpp>

namespace Mimp
{
	//! @brief Struct defining a Color
	//! @details Holds the RGB value of the color and handles basic color operations.
	struct Color {
		unsigned char r; /*!< Red value of the color. */
		unsigned char g; /*!< Green value of the color. */
		unsigned char b; /*!< Blue value of the color. */
		unsigned char a; /*!< Alpha value of the color. */

		//! @brief Constructor of the Struct Color
		//! @details Copy construct the color structure from an hexadecimal value.
		//! @param color The hexadecimal value of the color.
		Color(unsigned int color = 0x00000000) noexcept;

		//! @brief Constructor of the Struct Color
		//! @details Copy construct the color structure with rgba values.
		//! @param r Hexadecimal value for red.
		//! @param g Hexadecimal value for green.
		//! @param b Hexadecimal value for blue.
		//! @param a Hexadecimal value for alpha. Default value is 255.
		Color(unsigned char r, unsigned char g, unsigned char b, unsigned char a = 255) noexcept;

		//! @brief Compare two Color's.
		//! @param other The Color to compare with.
		//! @param include_alpha If the alpha values have to be included within the comparison or not.
		//! @return 0 if the colors are the same or more if they are not.
		unsigned diff(const Color &other, bool include_alpha=true) const noexcept;

		//! @brief Implicit cast to unsigned int
		//! @details Converts a color to an unsigned int using assignation (unsigned int = Color).
		operator unsigned int() const noexcept;

		//! @brief Implicit cast to sf::Color (SFML)
		//! @details Converts a Color to sf::Color (SFML) using assignation (sf::Color = Color).
		operator sf::Color() const noexcept;

		//! @brief Operator +
		//! @details Adds two colors together (Color + Color).
		//! @param other Color to add
		Color operator+(const Color &other);

		//! @brief Black Color
		static const Color Black;
		//! @brief LightGray Color
		static const Color LightGray;
		//! @brief DarkGray Color
		static const Color DarkGray;
		//! @brief White Color
		static const Color White;
		//! @brief Red Color
		static const Color Red;
		//! @brief Blue Color
		static const Color Blue;
		//! @brief Green Color
		static const Color Green;
		//! @brief Magenta Color
		static const Color Magenta;
		//! @brief Yellow Color
		static const Color Yellow;
		//! @brief Cyan Color
		static const Color Cyan;
		//! @brief Transparent Color
		static const Color Transparent;
	};
}


#endif //MYGIMP_COLOR_HPP
