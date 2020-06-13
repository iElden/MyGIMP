//
// Created by Gegel85 on 06/04/2020.
//

#ifndef MYGIMP_VECTOR2_HPP
#define MYGIMP_VECTOR2_HPP


#include <cmath>

namespace Mimp
{
	//! @brief Templated Vector2
	//! @details Struct containing a type x and a type y.
	template<typename type>
	struct Vector2 {
		type x; //!< The x value of the Vector2.
		type y; //!< The y value of the Vector2.

		//! @brief Constructor of a templated Vector2
		//! @param x_ The x value of the vector
		//! @param y_ The y value of the vector
		Vector2(type x_, type y_): x(x_), y(y_) {};

		//! \brief Default Vector2 constructor
		Vector2<type>() = default;

		//! @brief Rotate the Vector2 around a center
		//! @param angle Angle of rotation in degree
		//! @param center Center of rotation
		template <typename T>
		Vector2<double> rotate(float angle, Vector2<T> center)
		{
			angle = std::fmod(angle * M_PI / 180, 2 * M_PI);

			if (angle == 0.f)
				return {
					static_cast<float>(this->x),
					static_cast<float>(this->y)
				};

			float c = cos(angle);
			float s = sin(angle);

			Vector2<double> result{
				c * (static_cast<float>(x) - center.x) - s * (static_cast<float>(y) - center.y) + center.x,
				s * (static_cast<float>(x) - center.x) + c * (static_cast<float>(y) - center.y) + center.y
			};

			return result;
		}

		template <typename T>
		Vector2<T> to()
		{
			return {
				static_cast<T>(this->x),
				static_cast<T>(this->y)
			};
		}

		//! @brief Operator +
		//! @details Adds two Vector2 and returns the result in a Vector2 (Vector2 = Vector2 + Vector2).
		//! @param other The other Vector2 to add.
		//! @return Vector2<type>
		template <typename type2>
		auto operator+(const Vector2<type2> &other)
		{
			return Vector2<decltype(this->x + other.x)>{
				this->x + other.x,
				this->y + other.y
			};
		}

		//! @brief Operator -
		//! @details Subtracts two Vector2 and returns the result in a Vector2 (Vector2 = Vector2 - Vector2).
		//! @param other The other Vector2 to sub
		//! @return Vector2<type>
		template <typename type2>
		auto operator-(const Vector2<type2> &other)
		{
			return Vector2<decltype(this->x - other.x)>{
				this->x - other.x,
				this->y - other.y
			};
		}

		//! @brief Operator +=
		//! @details Add the Vector2 in parameter to the first Vector2 (Vector2 += Vector2).
		//! @param other The Vector2 to add.
		//! @return Vector2<type>
		template <typename type2>
		Vector2<type> &operator+=(const Vector2<type2> &other)
		{
			this->x += other.x;
			this->y += other.y;
			return *this;
		}

		//! @brief Operator -=
		//! @details Subtracts the Vector2 in parameter to the first Vector2 (Vector2 -= Vector2).
		//! @param other The other Vector2 to subtract.
		//! @return Vector2<type>
		template <typename type2>
		Vector2<type> operator-=(const Vector2<type2> &other)
		{
			this->x -= other.x;
			this->y -= other.y;
			return *this;
		}

		//! @brief Multiply a Vector2 by a factor.
		//! \tparam type2 The type of factor of the multiplication (int, float, unsigned, etc.).
		//! \param other The factor of the multiplication.
		//! \return A Vector2 of the better storage type between type and type2 and containing the result of the multiplication.
		template <typename type2>
		auto operator*(type2 other)
		{
			return Vector2<decltype(this->x * other)>{
				this->x * other,
				this->y * other
			};
		}

		//! @brief Divide a Vector2 by a factor.
		//! \tparam type2 The type of factor of the division (int, float, unsigned, etc.).
		//! \param other The factor of the division.
		//! \return A Vector2 of the better storage type between type and type2 and containing the result of the multiplication.
		template <typename type2>
		auto operator/(type2 other)
		{
			return Vector2<decltype(this->x * other)>{
				this->x / other,
				this->y / other
			};
		}

		//! @brief Operator ==
		//! @details Is the Vector2 in parameter equal to the first Vector2 ?
		//! @param other The other Vector2 to sub
		//! @return bool
		bool operator==(const Vector2<type> &other)
		{
			return this->x == other.x && this->y == other.y;
		}
	};
}


#endif //MYGIMP_VECTOR2_HPP
