#ifndef MYGIMP_POLYGON_HPP
#define MYGIMP_POLYGON_HPP

#include <vector>
#include <cstdint>
#include <any>
#include <functional>
#include "../Data/Vector2.hpp"

namespace Mimp {
	class Polygon : public std::vector<Vector2<int>> {
	public:

		void add(Vector2<int> point);

		void removeLast();

		void update(const std::function<void(Vector2<int>)> &f);

		void reset();

	private:
		bool _isInside(Vector2<int> pt);

	private:
		Vector2<int> _min = {INT32_MAX, INT32_MAX};
		Vector2<int> _max = {INT32_MIN, INT32_MIN};
	};
}


#endif //MYGIMP_POLYGON_HPP
