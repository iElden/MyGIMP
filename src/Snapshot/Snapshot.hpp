/*
** EPITECH PROJECT, 2020
** MyGimp
** File description:
** Snapshot.hpp
*/
#ifndef MYGIMP_SNAPSHOT_HPP
#define MYGIMP_SNAPSHOT_HPP

#include "../Image.hpp"

namespace Mimp {
	class Snapshot {
	public:
		virtual void rollback(Image &image) = 0;
	};
}


#endif //MYGIMP_SNAPSHOT_HPP
