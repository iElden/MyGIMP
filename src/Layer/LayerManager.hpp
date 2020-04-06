//
// Created by Gegel85 on 06/04/2020.
//

#ifndef MYGIMP_LAYERMANAGER_HPP
#define MYGIMP_LAYERMANAGER_HPP


#include "Layer.hpp"

namespace Mimp
{
	class LayerManager {
	private:
		std::vector<Layer> _layers;
		unsigned int _selectedLayer;

	public:
		LayerManager();
		void addLayer(const Layer &layer);
		void addLayer(Vector2<unsigned> size, const Color &defaultColor = Color::Transparent);
		Layer &operator[](unsigned int index);
		void render(FrameBuffer &buffer) const noexcept;
		Layer &selectLayer(unsigned int layer);
		Layer &getSelectedLayer() noexcept;
		void deleteLayer(unsigned int layer);
		void setLayerIndex(unsigned int layerOldIndex, unsigned int layerNewIndex);

		//Iterator
		std::vector<Layer>::iterator begin();
		std::vector<Layer>::iterator end();
	};
}


#endif //MYGIMP_LAYERMANAGER_HPP
