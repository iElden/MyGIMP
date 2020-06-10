/*
** EPITECH PROJECT, 2020
** MyGimp
** File description:
** Snapshot.hpp
*/
#ifndef MYGIMP_SNAPSHOT_HPP
#define MYGIMP_SNAPSHOT_HPP


namespace Mimp {
	class Editor;
	class Image;

	class Snapshot {
	public:
		virtual void undo(Image &image, Editor &editor) = 0;
		virtual void redo(Image &image, Editor &editor) = 0;
	};
}


#endif //MYGIMP_SNAPSHOT_HPP
