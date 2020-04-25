//
// Created by Gegel85 on 06/04/2020.
//

#ifndef MYGIMP_LAYERMANAGER_HPP
#define MYGIMP_LAYERMANAGER_HPP


#include <memory>
#include "Layer.hpp"

namespace Mimp
{
	//! @brief Layer Manager of Mimp
	//! @details Manages layers of Mimp
	class LayerManager {
	private:
		//! @brief Magic Number for .mimp saves
		//! @details This magic number is used to know if a .mimp file is valid for Mimp or not
		static constexpr unsigned MAGIC_NBR = 0xDAFE4E1A;

		//! @brief Saved Layer in Mimp
		struct SavedLayer {
			//! @brief position of the SavedLayer
			Vector2<int> pos;
			//! @brief size of the SavedLayer
			Vector2<unsigned> size;
			//! @brief Name of the layer
			char name[32];
			//! @brief attributes of the SavedLayer
			//! @details Contains "visible" and "locked" options
			struct {
				bool visible : 1;
				bool locked : 1;
			} attributes;
			//! @brief pixels
			unsigned pixels[0];
		};

		//! @brief Image in Mimp
		struct MimpImage {
			//! @brief Magic number validation
			unsigned magic;
			//! @brief Number of layers in the image
			uint32_t nbLayers;
			//! @brief Size of the image
			Vector2<unsigned> size;
			//! @brief Saved Layers
			SavedLayer layers[0];
			//! @brief Metadatas
			unsigned char metadata[0];
		};

		//! @brief Shared Pointers on layers
		std::vector<std::shared_ptr<Layer>> _layers;
		//! @brief Selected Layer
		unsigned int _selectedLayer = 0;
		//! @brief Size
		Vector2<unsigned> _size;

		//! @brief Is The layer manager busy (thread)
		mutable bool _busy = false;

		//! @brief Check if the layer manager is busy
		void _checkBusy() const;
		//! @brief Set layer manager as state busy
		void _setBusy() const;
		//! @brief Set layer manager as state not busy
		void _unsetBusy() const;

	public:
		//! @brief Constructor of the Layer Manager
		//! @param path Path of the layer manager
		LayerManager(const std::string &path);
		//! @brief Constructor of the Layer Manager
		//! @param size Size of the layers
		//! @param nbOfLayer Number of layers to create in the layer manager
		//! @param defaultColor Color of the layers in the layer manager
		LayerManager(Vector2<unsigned> size, unsigned int nbOfLayer = 1, const Color &defaultColor = Color::Transparent);
		//! @brief Function to add a layer to the layer manager
		//! @param layer Layer to add to the layer manager
		void addLayer(const Layer &layer);
		//! @brief Function to add a layer to the layer manager
		//! @param size Size of the layer
		//! @param defaultColor Color of the layer to add
		void addLayer(Vector2<unsigned> size, const Color &defaultColor = Color::Transparent);
		//! @brief Operator to get a specific layer in the layer manager
		//! @param index Index of the layer to get
		//! @return Layer Returned layer
		Layer &operator[](unsigned int index);
		//! @brief Render the framebuffer on the screen
		//! @param buffer The framebuffer to render
		void render(FrameBuffer &buffer) const noexcept;
		//! @brief Select a layer
		//! @param layer Layer to be selected
		//! @return Layer Returned Layer
		Layer &selectLayer(unsigned int layer);
		//! @brief Get the selected layer
		//! @return Layer Selected Layer
		Layer &getSelectedLayer() noexcept;
		//! @brief Get the selected layer
		//! @return Layer Selected Layer
		const Layer &getSelectedLayer() const noexcept;
		//! @brief Delete a layer
		//! @param layer The layer to delete
		void deleteLayer(unsigned int layer);
		//! @brief Set a new layer index to a layer
		//! @param layerOldIndex Old index
		//! @param layerOldIndex New index
		void setLayerIndex(unsigned int layerOldIndex, unsigned int layerNewIndex);
		//! @brief Get the size of the layer manager
		//! @return Vector2<unsigned> Size of the layer manager
		Vector2<unsigned> getSize() const;
		//! @brief Set the size of the layer manager
		//! @param size Set the new size of the layer manager
		void setSize(const Vector2<unsigned> &size);
		//! @brief Save the layer manager to a path in a .mimp file
		//! @param path Path where to save the file
		void save(const std::string &path) const;
		//! @brief Save the layer manager to a path in a .mimp file
		//! @param stream Stream to use to write/save the file
		void save(std::ostream &stream) const;

		size_t size() const;

		//! @brief Load a Mimp Image from a path
		//! @param path Path of the Mimp image to load
		void loadMimpImage(const std::string &path);
		//! @brief Import an image from a path
		//! @param path Path of the Mimp image to import
		void importImage(const std::string &path);

		//! @brief Is the Mimp Image Valid ?
		//! @param stream Stream of the image to verify
		//! @return bool Validity of the image
		static bool isValidMimpImage(std::istream &stream);

		//Iterator
		//! @brief Iterator begin for vectors of layers
		std::vector<std::shared_ptr<Layer>>::iterator begin();
		//! @brief Iterator end for vectors of layers
		std::vector<std::shared_ptr<Layer>>::iterator end();
	};
}


#endif //MYGIMP_LAYERMANAGER_HPP
