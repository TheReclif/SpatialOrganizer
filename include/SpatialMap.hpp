#pragma once
#ifndef SPATIALORGANIZER_SPATIALMAP_HPP
#define SPATIALORGANIZER_SPATIALMAP_HPP

#include <memory>

namespace Spatial
{
	/// @brief TODO
	/// @tparam Value TODO
	/// @tparam Allocator TODO
	template<class Value, class Allocator = std::allocator<char>>
	class SpatialMap
	{
	public:
		/// @brief Initializes the spatial map with a given cell size.
		/// @param cellSize Cell size.
		SpatialMap(const unsigned int cellSize);

	private:

	};
}

#endif
