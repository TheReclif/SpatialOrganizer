#pragma once
#ifndef SPATIALORGANIZER_H
#define SPATIALORGANIZER_H

#include "SingleThreadedSpatialHashSet.h"

namespace SpatialOrg
{
	struct FloatHasher
	{
		std::size_t operator()(const float arg) const;
	};

	namespace SingleThreaded
	{
		extern template class SpatialHashSet<float, SpatialOrg::FloatHasher, std::allocator<float>>;
	}
}

#endif
