/*
** EPITECH PROJECT, 2020
** MyGimp
** File description:
** Image.cpp
*/
#include <SFML/Graphics/Image.hpp>
#include "Image.hpp"
#include "Exceptions.hpp"
#include "Snapshot/FrameBufferSnapshot.hpp"
#include "Snapshot/LayerSnapshot.hpp"
#include "Snapshot/SelectionSnapshot.hpp"

namespace Mimp {
	Layer &Image::getSelectedLayer() noexcept
	{
		return this->_layers.getSelectedLayer();
	}

	const Layer &Image::getSelectedLayer() const noexcept
	{
		return this->_layers.getSelectedLayer();
	}

	Image::Image(Vector2<unsigned> size):
		_size(size),
		_layers(size),
		selectedArea(std::make_shared<SelectedArea>(size))
	{}

	Image::Image(Vector2<unsigned> size, const LayerManager &layers):
		_size(size),
		_layers(layers),
		selectedArea(std::make_shared<SelectedArea>(size))
	{
	}

	LayerManager &Image::getLayers() noexcept
	{
		return this->_layers;
	}

	const LayerManager &Image::getLayers() const noexcept
	{
		return this->_layers;
	}

	Vector2<unsigned> Image::getImageSize() const noexcept
	{
		return this->_size;
	}

	void Image::exportImage(const std::string &path) const
	{
		FrameBuffer buffer({
			static_cast<unsigned>(this->getImageSize().x),
			static_cast<unsigned>(this->getImageSize().y)
		});
		auto size = buffer.getSize();
		sf::Image image;
		auto pixelArray = new sf::Color[size.x * size.y];

		this->_layers.render(buffer);
		for (unsigned x = 0; x < size.x; x++)
			for (unsigned y = 0; y < size.y; y++)
				pixelArray[x + y * size.x] = buffer.getPixel({static_cast<int>(x), static_cast<int>(y)});

		image.create(size.x, size.y, reinterpret_cast<const sf::Uint8 *>(pixelArray));
		delete[] pixelArray;
		if (!image.saveToFile(path))
			throw ExportErrorException("Cannot export to file " + path);
	}

	int Image::getMaxSnapshots() const noexcept
	{
		return _max_snapshots;
	}

	void Image::setMaxSnapshots(int maxSnapshots) noexcept
	{
		_max_snapshots = maxSnapshots;
	}

	void Image::takeSnapshot(std::shared_ptr<Snapshot> snapshot) noexcept
	{
		this->_snapshots.push_back(snapshot);
		if (this->_snapshots.size() > this->_max_snapshots)
			this->_snapshots.erase(this->_snapshots.begin());
		this->_redoSnapshots.clear();
	}

	void Image::takeFrameBufferSnapshot() noexcept
	{
		this->takeSnapshot(std::make_shared<FrameBufferSnapshot>(
				*this->getSelectedLayer().buffer, this->_layers.getSelectedLayerIndex()
		));
	}


	void Image::takeLayerSnapshot() noexcept
	{
		this->takeSnapshot(std::make_shared<LayerSnapshot>(
				this->getSelectedLayer(), this->_layers.getSelectedLayerIndex()
		));
	}

	void Image::takeSelectionSnapshot() noexcept
	{
		this->takeSnapshot(std::make_shared<SelectionSnapshot>(
				*this->selectedArea
		));
	}

	void Image::undoLastAction() noexcept
	{
		if (this->_snapshots.empty())
			return;
		std::shared_ptr<Snapshot> snapshot = this->_snapshots.back();
		snapshot->undo(*this);
		this->_redoSnapshots.emplace_back(snapshot);
		this->_snapshots.pop_back();
	}

	void Image::redoLastUndo() noexcept
	{
		if (this->_redoSnapshots.empty())
			return;
		std::shared_ptr<Snapshot> snapshot = this->_redoSnapshots.back();
		snapshot->redo(*this);
		this->_snapshots.emplace_back(snapshot);
		this->_redoSnapshots.pop_back();
	}

}