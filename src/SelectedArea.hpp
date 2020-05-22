/*
** EPITECH PROJECT, 2020
** MyGimp
** File description:
** SelectedArea.hpp
*/
#ifndef MYGIMP_SELECTEDAREA_HPP
#define MYGIMP_SELECTEDAREA_HPP


#include <vector>
#include "Data/Vector2.hpp"
#include "Layer/Layer.hpp"

namespace Mimp {
    //! @brief Define the SelectedArea.
	class SelectedArea {
		Vector2<unsigned> _size; //!< Size of the SelectedArea.

	private:
		bool *_map;
		unsigned _nbPoints = 0;

	public:
        //! @brief Copy constructor of the SelectedArea.
        //! @param other SelectedArea to copy.
		SelectedArea(const SelectedArea &);

        //! @brief Copy constructor of the SelectedArea.
        //! @param width Width of the SelectedArea
        //! @param height Height of the SelectedArea
        SelectedArea(unsigned width, unsigned height);

        //! @brief Constructor of the SelectedArea.
        //! @param size Size of the SelectedArea.
        //! @param buffer Contains the points to select when creating. Default is nullptr (None).
		SelectedArea(Vector2<unsigned> size, const bool *buffer = nullptr);

		//! @brief SelectedAreaDestructor
		~SelectedArea();

		//! @brief Set the size of the SelectedArea.
        //! @param size The new size
		void setSize(Vector2<unsigned> size);

		//! @brief Get the size of the SelectedArea.
        //! @param Vector2<unsigned int>
		Vector2<unsigned int> getSize() const;

		//! @brief Remove all the points from the SelectedArea.
		void clear() noexcept;

        //! @brief Select all the points in the SelectedArea.
		void selectAll() noexcept;

        //! @brief Fill a Layer with a Color.
        //! @param layer The Layer to fill.
        //! @param color The Color used to fill.
		void fill(Layer &layer, const Color &color);

		//! @brief Is the AreaSelected selected ?
		//! @return bool
		bool isAnAreaSelected() const noexcept;

        //! @brief Returns all the selected points.
        //! @return std::vector<Vector2<int>>
        std::vector<Vector2<int>> getPoints() const noexcept;

        //! @brief Add a point to the selection.
        //! @param point The position of the point in vectorize form.
		void add(Vector2<int> point);

        //! @brief Add a point to the selection.
        //! @param x X position of the point
        //! @param y Y position of the point
		void add(int x, int y);

        //! @brief Remove a point to the selection.
        //! @param point The position of the point in vectorize form.
		void remove(Vector2<int> point);

        //! @brief Remove a point to the selection.
        //! @param x X position of the point
        //! @param y Y position of the point
		void remove(int x, int y);

		//! @brief Inverse the selection.
		void invert() noexcept;

		//! @brief Test if a point is selected.
		//! @param point The position of the point in vectorize form.
		//! @return bool
		bool pointInMap(Vector2<int> point) const;

        //! @brief Test if a point is selected.
        //! @param x X position of the point
        //! @param y Y position of the point
        //! @return bool
        bool pointInMap(int x, int y) const;
	};
}


#endif //MYGIMP_SELECTEDAREA_HPP
