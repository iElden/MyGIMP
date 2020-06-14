#include "Polygon.hpp"

namespace Mimp {

	void Polygon::add(Vector2<int> point)
	{
		this->_min.x = std::min(this->_min.x, point.x);
		this->_min.y = std::min(this->_min.y, point.y);
		this->_max.x = std::max(this->_max.x, point.x);
		this->_max.y = std::max(this->_max.y, point.y);
		this->push_back(point);
	}

	void Polygon::removeLast()
	{
		this->pop_back();
		this->_min = {INT32_MAX, INT32_MAX};
		this->_max = {INT32_MIN, INT32_MIN};
		if (!this->empty()) {
			for (auto &v : *this) {
				this->_min.x = std::min(this->_min.x, v.x);
				this->_min.y = std::min(this->_min.y, v.y);
				this->_max.x = std::max(this->_max.x, v.x);
				this->_max.y = std::max(this->_max.y, v.y);
			}
		}
	}

	void Polygon::update(const std::function<void(Vector2<int>)> &f)
	{
		if (this->empty() || f == nullptr)
			return;
		for (int x = this->_min.x; x < this->_max.x; x += 1) {
			for (int y = this->_min.y; y < this->_max.y; y += 1) {
				if (this->_isInside({x, y}))
					f({x, y});
			}
		}
	}

// http://www.eecs.umich.edu/courses/eecs380/HANDOUTS/PROJ2/InsidePoly.html
	bool Polygon::_isInside(Vector2<int> pt)
	{
		bool isInside = false;
		auto v = *this;

		for (unsigned int i = 0, j = v.size() - 1; i < v.size(); j = i, i++) {
			auto &pt1 = v[i];
			auto &pt2 = v[j];

			if ((((pt1.y <= pt.y) && (pt.y < pt2.y)) || ((pt2.y <= pt.y) && (pt.y < pt1.y))) &&
			    (pt.x < (pt2.x - pt1.x) * (pt.y - pt1.y) / (pt2.y - pt1.y) + pt1.x))
				isInside = !isInside;
		}

		return isInside;
	}

	void Polygon::reset()
	{
		this->_min = {INT32_MAX, INT32_MAX};
		this->_max = {INT32_MIN, INT32_MIN};
		this->clear();
	}

}