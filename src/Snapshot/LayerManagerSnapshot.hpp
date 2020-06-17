/*
** EPITECH PROJECT, 2020
** MyGimp
** File description:
** LayerManagerSnapshot.hpp
*/
#ifndef MYGIMP_LAYERMANAGERSNAPSHOT_HPP
#define MYGIMP_LAYERMANAGERSNAPSHOT_HPP

#include "Snapshot.hpp"
#include "../Layer/LayerManager.hpp"
#include <memory>
namespace Mimp {
	class LayerManagerSnapshot : public Snapshot {
		std::shared_ptr<LayerManager> oldLayerManager;
	public:
		LayerManagerSnapshot(const LayerManager &layerManager);
		void undo(Image &image, Editor &editor) override;
		void redo(Image &image, Editor &editor) override;
	};
}

#endif //MYGIMP_LAYERMANAGERSNAPSHOT_HPP
