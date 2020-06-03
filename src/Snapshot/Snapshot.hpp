/*
** EPITECH PROJECT, 2020
** MyGimp
** File description:
** Snapshot.hpp
*/
#ifndef MYGIMP_SNAPSHOT_HPP
#define MYGIMP_SNAPSHOT_HPP

namespace Mimp {
	class Image;

	class Snapshot {
	public:
		virtual void undo(Image &image) = 0;
		virtual void redo(Image &image) = 0;
	};
}


#endif //MYGIMP_SNAPSHOT_HPP
