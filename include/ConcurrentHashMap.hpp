#pragma once
#ifndef SPATIALORGANIZER_CONCURRENTHASHMAP_HPP
#define SPATIALORGANIZER_CONCURRENTHASHMAP_HPP

#include <memory>
#include <functional>

namespace Spatial
{
	template<typename Key, typename T, class Hash = std::hash<Key>, class KeyEqual = std::equal_to<Key>, class Allocator = std::allocator<std::pair<const Key, T>>>
	class ConcurrentHashMap
	{
	public:
	private:
	};
}

#endif
