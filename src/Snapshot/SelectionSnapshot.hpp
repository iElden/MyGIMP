/*
** EPITECH PROJECT, 2020
** MyGimp
** File description:
** SelectionSnapshot.hpp
*/
#ifndef MYGIMP_SELECTIONSNAPSHOT_HPP
#define MYGIMP_SELECTIONSNAPSHOT_HPP

#include <memory>
#include "Snapshot.hpp"
#include "../SelectedArea.hpp"


namespace Mimp {
	class SelectionSnapshot : public Snapshot {
		std::shared_ptr<SelectedArea> _oldSelection;
	public:
		SelectionSnapshot(const SelectedArea &oldSelection);
		void undo(Image &image) override;
		void redo(Image &image) override;
	};
}


#endif //MYGIMP_SELECTIONSNAPSHOT_HPP
