/*
** EPITECH PROJECT, 2020
** MyGimp
** File description:
** SelectedArea.cpp
*/

#include <cstring>
#include <thread>
#include <iostream>
#include "SelectedArea.hpp"
#include "Utils.hpp"

namespace Mimp
{
	SelectedArea::SelectedArea(unsigned width, unsigned height) :
		SelectedArea(Vector2<unsigned>{width, height})
	{
	}

	SelectedArea::SelectedArea(Vector2<unsigned> size, const bool *map) :
		_size(size),
		_map(new bool[size.x * size.y])
	{
		this->clear();
		if (map) {
			std::memcpy(this->_map, map, size.x * size.y);
			for (unsigned i = 0; i < size.x * size.y; i++)
				this->_nbPoints += this->_map[i];
		}
	}

	SelectedArea::SelectedArea(const SelectedArea &other) :
		SelectedArea(other.getSize(), other._map)
	{
	}

	SelectedArea::~SelectedArea()
	{
		delete[] this->_map;
	}

	void SelectedArea::clear() noexcept
	{
		std::memset(this->_map, false, this->_size.x * this->_size.y);
		this->_nbPoints = 0;
	}

	void SelectedArea::selectAll() noexcept
	{
		std::memset(this->_map, true, this->_size.x * this->_size.y);
		this->_nbPoints = this->_size.x * this->_size.y;
	}

	bool SelectedArea::isAnAreaSelected() const noexcept
	{
		return this->_nbPoints;
	}

	void SelectedArea::add(Vector2<int> point)
	{
		this->add(point.x, point.y);
	}

	void SelectedArea::add(int x, int y)
	{
		if (Utils::isOutOfBound({x, y}, this->_size))
			return;

		auto &val = this->_map[x + y * this->_size.x];

		this->_nbPoints += !val;
		val = true;
	}

	void SelectedArea::remove(Vector2<int> point)
	{
		this->remove(point.x, point.y);
	}

	void SelectedArea::remove(int x, int y)
	{
		if (Utils::isOutOfBound({x, y}, this->_size))
			return;

		auto &val = this->_map[x + y * this->_size.x];

		this->_nbPoints -= val;
		val = false;
	}

	std::vector<Vector2<int>> SelectedArea::getPoints() const noexcept
	{
		int index = 0;
		std::vector<Vector2<int>> selectedPoints;

		selectedPoints.reserve(this->_nbPoints);
		for (unsigned y = 0; y < this->_size.y; y++)
			for (unsigned x = 0; x < this->_size.x; x++)
				if (this->_map[index++])
					selectedPoints.emplace_back(x, y);
		return selectedPoints;
	}

	void SelectedArea::invert() noexcept
	{
		int index = 0;

		this->_nbPoints = this->_size.x * this->_size.y - this->_nbPoints;
		for (unsigned y = 0; y < this->_size.y; y++)
			for (unsigned x = 0; x < this->_size.x; x++) {
				this->_map[index] = !this->_map[index];
				index++;
			}
	}

	void SelectedArea::fill(Layer &layer, const Color &color) const noexcept
	{
		if (this->isAnAreaSelected())
			for (const auto &pt : this->getPoints()) {
				auto newPt = (pt - layer.pos).rotate(-layer.rotation, layer.getSize() / 2);

				layer.buffer->setPixel(Vector2<int>(std::floor(newPt.x), std::floor(newPt.y)), color);
				layer.buffer->setPixel(Vector2<int>(std::ceil(newPt.x),  std::floor(newPt.y)), color);
				layer.buffer->setPixel(Vector2<int>(std::floor(newPt.x), std::ceil(newPt.y)),  color);
				layer.buffer->setPixel(Vector2<int>(std::ceil(newPt.x),  std::ceil(newPt.y)),  color);
			}
	}

	void SelectedArea::addLine(Vector2<int> pt1, Vector2<int> pt2) noexcept
	{
		int dx = pt2.x - pt1.x;
		int dy = pt2.y - pt1.y;

		this->add(pt2);
		if (dx > 0) {
			if (dy > 0) {
				// vecteur oblique dans le 1er quadran

				if (dx >= dy) {
					// vecteur diagonal ou oblique proche de l’horizontale, dans le 1er octant
					int e = dx;
					dx *= 2;
					dy *= 2 ;  // e est positif
					while (true) { // déplacements horizontaux
						this->add(pt1);
						pt1.x++;
						if (pt1.x == pt2.x)
							break;
						e -= dy;
						if (e < 0) {
							pt1.y++;  // déplacement diagonal
							e += dx ;
						}
					}
				} else {
					// vecteur oblique proche de la verticale, dans le 2d octant
					int e = dy;
					dy *= 2;
					dx *= 2;  // e est positif
					while (true) {  // déplacements verticaux
						this->add(pt1);
						pt1.y++;
						if (pt1.y == pt2.y)
							break;
						e -= dx;
						if (e < 0) {
							pt1.x++;  // déplacement diagonal
							e += dy;
						}
					}
				}

			} else if (dy) {  // dy < 0 (et dx > 0)
				// vecteur oblique dans le 4e cadran

				if (dx >= -dy) {
					// vecteur diagonal ou oblique proche de l’horizontale, dans le 8e octant
					int e = dx;
					dx *= 2;
					dy *= 2 ;  // e est positif
					while (true) {  // déplacements horizontaux
						this->add(pt1);
						pt1.x++;
						if (pt1.x == pt2.x)
							break;
						e += dy;
						if (e < 0) {
							pt1.y--;  // déplacement diagonal
							e += dx;
						}
					}
				} else {  // vecteur oblique proche de la verticale, dans le 7e octant
					int e = dy;
					dy *= 2;
					dx *= 2;  // e est négatif
					while (true) {  // déplacements verticaux
						this->add(pt1);
						pt1.y--;
						if (pt1.y == pt2.y)
							break;
						e += dx;
						if (e > 0) {
							pt1.x++;  // déplacement diagonal
							e += dy;
						}
					}
				}
			} else { // dy = 0 (et dx > 0)
				do {
					this->add(pt1);
					pt1.x++;
				} while (pt2.x != pt1.x);
			}
		} else if (dx) {  // dx < 0
			if (dy > 0) {
				// vecteur oblique dans le 2d quadran

				if (-dx >= dy) {
					// vecteur diagonal ou oblique proche de l’horizontale, dans le 4e octant
					int e = dx;
					dx *= 2;
					dy *= 2;  // e est négatif
					while (true) {  // déplacements horizontaux
						this->add(pt1);
						pt1.x--;
						if (pt1.x == pt2.x)
							break;
						e += dy;
						if (e >= 0) {
							pt1.y++;  // déplacement diagonal
							e += dx;
						}
					}
				} else {
					// vecteur oblique proche de la verticale, dans le 3e octant
					int e = dy;
					dy *= 2;
					dx *= 2;  // e est positif
					while (true) {  // déplacements verticaux
						this->add(pt1);
						pt1.y++;
						if (pt1.y == pt2.y)
							break;
						e += dx;
						if (e <= 0) {
							pt1.x--;  // déplacement diagonal
							e += dy;
						}
					}
				}

			} else if (dy) { // dy < 0 (et dx < 0)
				// vecteur oblique dans le 3e cadran

				if (dx <= dy) {
					// vecteur diagonal ou oblique proche de l’horizontale, dans le 5e octant
					int e = dx;
					dx *= 2;
					dy *= 2;  // e est négatif
					while (true) {  // déplacements horizontaux
						this->add(pt1);
						pt1.x--;
						if (pt1.x == pt2.x)
							break;
						e -= dy;
						if (e >= 0) {
							pt1.y--;  // déplacement diagonal
							e += dx;
						}
					}
				} else {  // vecteur oblique proche de la verticale, dans le 6e octant
					int e = dy;

					dy *= 2;
					dx *= 2;  // e est négatif
					while (true) {  // déplacements verticaux
						this->add(pt1);
						pt1.y--;
						if (pt1.y == pt2.y)
							break;
						e -= dx;
						if (e >= 0) {
							pt1.x--;  // déplacement diagonal
							e += dy;
						}
					}
				}
			} else {  // dy = 0 (et dx < 0)

				// vecteur horizontal vers la gauche
				do {
					this->add(pt1);
					pt1.x--;
				} while (pt2.x != pt1.x);

			}
		} else {  // dx = 0
			if (dy > 0) {
				do {
					this->add(pt1);
					pt1.y++;
				} while (pt1.y != pt2.y);
			} else if (dy) {
				do {
					this->add(pt1);
					pt1.y--;
				} while (pt1.y != pt2.y);
			}
		}
	}

	bool SelectedArea::pointInMap(Vector2<int> point) const
	{
		return this->pointInMap(point.x, point.y);
	}

	bool SelectedArea::pointInMap(int x, int y) const
	{
		if (Utils::isOutOfBound({x, y}, this->_size))
			return false;
		return this->_map[x + y * this->_size.x];
	}

	Vector2<unsigned int> SelectedArea::getSize() const
	{
		return _size;
	}

	void SelectedArea::setSize(Vector2<unsigned> size)
	{
		if (this->_size == size)
			return;

		this->_size = size;
		delete[] this->_map;
		this->_map = new bool[size.x * size.y];
		this->clear();
	}
}


