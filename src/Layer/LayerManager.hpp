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
		static constexpr unsigned MAGIC_NBR = 0xDAFE4E1A;

		struct SavedLayer {
			Vector2<int> pos;
			Vector2<unsigned> size;
			struct {
				bool visible : 1;
				bool locked : 1;
			} attributes;
			unsigned pixels[0];
		};

		struct MimpImage {
			unsigned magic;
			uint32_t nbLayers;
			Vector2<unsigned> size;
			SavedLayer layers[0];
			unsigned char metadata[0];
		};

		std::vector<std::shared_ptr<Layer>> _layers;
		unsigned int _selectedLayer = 0;
		Vector2<unsigned> _size;

		void _loadMimpImage(const std::string &path);
		void _loadClassicalImage(const std::string &path);
	public:
		LayerManager(const std::string &path);
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
		Vector2<unsigned> getSize() const;
		void setSize(const Vector2<unsigned> &size);
		void save(const std::string &path) const;
		void save(std::ostream &stream) const;

		static bool isValidMimpImage(std::istream &stream);

		//Iterator
		std::vector<std::shared_ptr<Layer>>::iterator begin();
		std::vector<std::shared_ptr<Layer>>::iterator end();
	};
}


#endif //MYGIMP_LAYERMANAGER_HPP
