//
// Created by Gegel85 on 06/04/2020.
//

#ifndef MYGIMP_LAYERMANAGER_HPP
#define MYGIMP_LAYERMANAGER_HPP


#include <memory>
#include "Layer.hpp"

namespace Mimp
{
	class LayerManager {
	private:
		std::vector<std::shared_ptr<Layer>> _layers;
		unsigned int _selectedLayer;

	public:
		LayerManager(Vector2<unsigned> size, unsigned int nbOfLayer = 1, const Color &defaultColor = Color::Transparent);
		void addLayer(const Layer &layer);
		void addLayer(Vector2<unsigned> size, const Color &defaultColor = Color::Transparent);
		Layer &operator[](unsigned int index);
		void render(FrameBuffer &buffer) const noexcept;
		Layer &selectLayer(unsigned int layer);
		Layer &getSelectedLayer() noexcept;
		const Layer &getSelectedLayer() const noexcept;
		void deleteLayer(unsigned int layer);
		void setLayerIndex(unsigned int layerOldIndex, unsigned int layerNewIndex);

		//Iterator
		std::vector<std::shared_ptr<Layer>>::iterator begin();
		std::vector<std::shared_ptr<Layer>>::iterator end();
	};
}


#endif //MYGIMP_LAYERMANAGER_HPP
