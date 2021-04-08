#include "../include/SpatialOrganizer.h"

#include <cmath>

std::size_t SpatialOrg::FloatHasher::operator()(const float arg) const
{
	return std::floor(arg);
}

template class SpatialOrg::SingleThreaded::SpatialHashSet<float, SpatialOrg::FloatHasher, std::allocator<float>>;
