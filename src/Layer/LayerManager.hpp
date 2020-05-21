//
// Created by Gegel85 on 06/04/2020.
//

#ifndef MYGIMP_LAYERMANAGER_HPP
#define MYGIMP_LAYERMANAGER_HPP


#include <memory>
#include "Layer.hpp"

namespace Mimp
{
    //! @brief Define a LayerManager.
    class LayerManager {
	private:
		//! @brief Magic Number for .mimp saves
		//! @details This magic number is used to know if a .mimp file is valid for Mimp or not.
		static constexpr unsigned MAGIC_NBR = 0xDAFE4E1A;

        //! @brief Define a SavedLayer.
		struct SavedLayer {
			Vector2<int> pos; //!< Position of the SavedLayer
			Vector2<unsigned> size; //!< Size of the SavedLayer
			char name[32]; //!< Name of the Layer
			struct {
				bool visible : 1; //!< Is the Layer visible ?
				bool locked : 1; //!< Is the Layer locked ?
			} attributes; //!< Define the attributes of the SavedLayer.
			Color pixels[0]; //!< Array of FrameBuffer pixels
		};

        //! @brief Define a MimpImage.
		struct MimpImage {
			unsigned magic; //!< Magic number for .mimp files
			uint32_t nbLayers; //!< Number of layers in the Image
			Vector2<unsigned> size; //!< Size of the Image
			SavedLayer layers[0]; //!< Saved Layers
			unsigned char metadata[0]; //!< Metadatas
		};

		//! @brief Shared Pointers on layers
		std::vector<std::shared_ptr<Layer>> _layers;
		//! @brief Selected Layer
		unsigned int _selectedLayer = 0;
		//! @brief Size
		Vector2<unsigned> _size;

		//! @brief Is The LayerManager busy (thread)
		mutable bool _busy = false;

		//! @brief Check if the LayerManager is busy
		void _checkBusy() const;
		//! @brief Set LayerManager as state busy
		void _setBusy() const;
		//! @brief Set LayerManager as state not busy
		void _unsetBusy() const;

	public:
		//! @brief Constructor of the LayerManager
		//! @param path Path of the LayerManager
		LayerManager(const std::string &path);

		//! @brief Constructor of the LayerManager
		//! @param size Size of the Layers
		//! @param nbOfLayer Number of layers to create in the LayerManager.
		//! @param defaultColor Color of the Layers in the LayerManager. Default is Transparent.
		LayerManager(Vector2<unsigned> size, unsigned int nbOfLayer = 1, const Color &defaultColor = Color::Transparent);

		//! @brief Function to add a Layer to the LayerManager
		//! @param layer Layer to add to the LayerManager
		//! @return The created Layer
		Layer &addLayer(const Layer &layer);

		//! @brief Function to add a Layer to the LayerManager
		//! @param size Size of the Layer
		//! @param defaultColor Color of the Layer to add. Default is Transparent.
		//! @return The created Layer
		Layer &addLayer(Vector2<unsigned> size, const Color &defaultColor = Color::Transparent);

		//! @brief Operator to get a specific Layer in the LayerManager
		//! @param index Index of the Layer to get
		//! @return Layer Returned Layer
		Layer &operator[](unsigned int index);

		//! @brief Render the FrameBuffer on the screen
		//! @param buffer The FrameBuffer to render
		void render(FrameBuffer &buffer) const noexcept;

		//! @brief Select a Layer
		//! @param layer Layer to be selected
		//! @return Layer Returned Layer
		Layer &selectLayer(unsigned int layer);

		//! @brief Get the selected Layer
		//! @return Layer Selected Layer
		Layer &getSelectedLayer() noexcept;

		//! @brief Get the selected Layer index
		//! @return Selected Layer index
		unsigned getSelectedLayerIndex() noexcept;

		//! @brief Get the selected Layer
		//! @return Layer Selected Layer
		const Layer &getSelectedLayer() const noexcept;

		//! @brief Delete a Layer
		//! @param layer The Layer to delete
		void deleteLayer(unsigned int layer);

		//! @brief Set a new index to a Layer
		//! @param layerOldIndex Old index
		//! @param layerNewIndex New index
		void setLayerIndex(unsigned int layerOldIndex, unsigned int layerNewIndex);

		//! @brief Get the size of the LayerManager
		//! @return Vector2<unsigned> Size of the LayerManager
		Vector2<unsigned> getSize() const;

		//! @brief Set the size of the LayerManager
		//! @param size Set the new size of the LayerManager
		void setSize(const Vector2<unsigned> &size);

		//! @brief Save the LayerManager to a path in a .mimp file
		//! @param path Path where to save the file
		void save(const std::string &path) const;

		//! @brief Save the LayerManager to a path in a .mimp file
		//! @param stream Stream to use to write/save the file
		void save(std::ostream &stream) const;

		//! @brief Return the number of layers.
		//! @return size_t
		size_t size() const;

		//! @brief Load a Mimp Image from a path
		//! @param path Path of the Mimp Image to load
		void loadMimpImage(const std::string &path);

		//! @brief Import an Image from a path
		//! @param path Path of the Mimp Image to import
		void importImageFromFile(const std::string &path);

		//! @brief Import an Image from a path
		//! @param data Data of the Image.
		void importImageFromMemory(const std::string &data);

		//! @brief Is the Mimp Image Valid ?
		//! @param stream Stream of the Image to verify
		//! @return bool Validity of the Image
		static bool isValidMimpImage(std::istream &stream);

		//Iterator
		//! @brief Iterator begin for vectors of layers
		std::vector<std::shared_ptr<Layer>>::iterator begin();
		//! @brief Iterator end for vectors of layers
		std::vector<std::shared_ptr<Layer>>::iterator end();

		//Iterator
		//! @brief Iterator begin for vectors of layers
		std::vector<std::shared_ptr<Layer>>::const_iterator begin() const;

		//! @brief Iterator end for vectors of layers
		std::vector<std::shared_ptr<Layer>>::const_iterator end() const;
	};
}


#endif //MYGIMP_LAYERMANAGER_HPP
