#pragma once
#ifndef SPATIALORGANIZER_CONCURRENTSPATIALMAP_HPP
#define SPATIALORGANIZER_CONCURRENTSPATIALMAP_HPP

#include <memory>

namespace Spatial
{
	/// @brief TODO
	/// @tparam Value TODO
	/// @tparam Allocator TODO
	template<class Value, class Allocator = std::allocator<char>>
	class ConcurrentSpatialMap
	{
	public:
		/// @brief Initializes the spatial map with a given cell size.
		/// @param cellSize Cell size.
		ConcurrentSpatialMap(const unsigned int cellSize);

	private:

	};
}

#endif
