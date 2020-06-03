/*
** EPITECH PROJECT, 2020
** MyGimp
** File description:
** Image.hpp
*/
#ifndef MYGIMP_IMAGE_HPP
#define MYGIMP_IMAGE_HPP

#include "Layer/LayerManager.hpp"
#include "SelectedArea.hpp"
#include "Snapshot/Snapshot.hpp"

namespace Mimp {
    //! @brief Define the SelectedArea.
	class Image {
	protected:
		Vector2<unsigned> _size; //!< Size of the Image
		LayerManager _layers; //!< Layers of the Image
		std::vector<std::shared_ptr<Snapshot>> _snapshots = {};
		std::vector<std::shared_ptr<Snapshot>> _redoSnapshots = {};
		unsigned _max_snapshots = 10;
	public:
		SelectedArea selectedArea; //!< SelectedArea of the Image

		//! @brief Constructor of Image
		//! @param size Size of the Image
		Image(Vector2<unsigned> size);

		//! @brief Constructor of Image
		//! @param size Size of the Image
		//! @param layers Layers of the image
		Image(Vector2<unsigned> size, const LayerManager &layers);

		//! @brief Get the selected layer
		//! @return Layer The selected Layer
		Layer &getSelectedLayer() noexcept;

		//! @brief Get the selected layer
		//! @return Layer The selected Layer
		const Layer &getSelectedLayer() const noexcept;

		//! @brief Get all the layers
		//! @return LayerManager All the layers
		LayerManager &getLayers() noexcept;

		//! @brief Export an image
		//! @param path Path to the exported image
		void exportImage(const std::string &path) const;

		//! @brief Get all the layers
		//! @return LayerManager All the layers
		const LayerManager &getLayers() const noexcept;

		//! @brief Get the image size
		//! @return Vector2<unsigned> Size of the image
		Vector2<unsigned> getImageSize() const noexcept;

		int getMaxSnapshots() const noexcept;
		void setMaxSnapshots(int maxSnapshots) noexcept;
		void takeSnapshot(std::shared_ptr<Snapshot> snapshot) noexcept;
		void takeFrameBufferSnapshot() noexcept;
		void undoLastAction() noexcept;
		void redoLastUndo() noexcept;
	};
}


#endif //MYGIMP_IMAGE_HPP
