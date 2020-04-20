//
// Created by Gegel85 on 06/04/2020.
//

#ifndef MYGIMP_VECTOR2_HPP
#define MYGIMP_VECTOR2_HPP


namespace Mimp
{
	//! @brief Templated Vector2
	//! @details Struct containing a type x and a type y
	template<typename type>
	struct Vector2 {
		type x;
		type y;

		Vector2(type x_, type y_): x(x_), y(y_) {};
		Vector2<type>() = default;
		//! @brief Operator +
		//! @details Adds two Vector2 and returns the result in a Vector2
		//! @param other The other Vector2 to add
		//! @return Vector2<type>
		Vector2<type> operator+(const Vector2<type> &other)
		{
			return {
				this->x + other.x,
				this->y + other.y
			};
		}

		//! @brief Operator -
		//! @details Subtracts two Vector2 and returns the result in a Vector2
		//! @param other The other Vector2 to sub
		//! @return Vector2<type>
		Vector2<type> operator-(const Vector2<type> &other)
		{
			return {
				this->x - other.x,
				this->y - other.y
			};
		}

		//! @brief Operator +=
		//! @details Add the Vector2 in parameter to the first Vector2
		//! @param other The Vector2 to add
		//! @return Vector2<type>
		Vector2<type> &operator+=(const Vector2<type> &other)
		{
			this->x += other.x;
			this->y += other.y;
			return *this;
		}

		//! @brief Operator -=
		//! @details Subtracts the Vector2 in parameter to the first Vector2
		//! @param other The other Vector2 to sub
		//! @return Vector2<type>
		Vector2<type> operator-=(const Vector2<type> &other)
		{
			this->x -= other.x;
			this->y -= other.y;
			return *this;
		}

		//! @brief Operator ==
		//! @details Is the Vector2 in parameter equal to the first Vector2
		//! @param other The other Vector2 to sub
		//! @return bool
		bool operator==(const Vector2<type> &other)
		{
			return this->x == other.x && this->y == other.y;
		}
	};
}


#endif //MYGIMP_VECTOR2_HPP
