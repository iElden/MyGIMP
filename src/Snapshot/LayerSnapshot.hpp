/*
** EPITECH PROJECT, 2020
** MyGimp
** File description:
** LayerSnapshot.hpp
*/
#ifndef MYGIMP_LAYERSNAPSHOT_HPP
#define MYGIMP_LAYERSNAPSHOT_HPP

#include <memory>
#include "Snapshot.hpp"
#include "../Layer/Layer.hpp"
#include "../Editor.hpp"

namespace Mimp {
	class LayerSnapshot : public Snapshot {
		int layerNumber;
		std::shared_ptr<Layer> oldLayer;
	public:
		LayerSnapshot(const Layer &layer, int layerNb);
		void undo(Image &image, Editor &editor) override;
		void redo(Image &image, Editor &editor) override;
	};
}


#endif //MYGIMP_LAYERSNAPSHOT_HPP
