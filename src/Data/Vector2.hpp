//
// Created by Gegel85 on 06/04/2020.
//

#ifndef MYGIMP_VECTOR2_HPP
#define MYGIMP_VECTOR2_HPP


namespace Mimp
{
	template<typename type>
	struct Vector2 {
		type x;
		type y;

		Vector2<type> operator+(const Vector2<type> &other)
		{
			return {
				this->x + other.x,
				this->y + other.y
			};
		}

		Vector2<type> operator-(const Vector2<type> &other)
		{
			return {
				this->x - other.x,
				this->y - other.y
			};
		}

		Vector2<type> &operator+=(const Vector2<type> &other)
		{
			this->x += other.x;
			this->y += other.y;
			return *this;
		}

		Vector2<type> operator-=(const Vector2<type> &other)
		{
			this->x -= other.x;
			this->y -= other.y;
			return *this;
		}

		bool operator==(const Vector2<type> &other)
		{
			return this->x == other.x && this->y == other.y;
		}
	};
}


#endif //MYGIMP_VECTOR2_HPP
