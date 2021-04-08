#pragma once
#ifndef SPATIALORGANIZER_STSPATIALHASHSET_H
#define SPATIALORGANIZER_STSPATIALHASHSET_H

#include <functional>
#include <atomic>
#include <vector>
#include <memory>

namespace SpatialOrg
{
	namespace SingleThreaded
	{
		/// @brief Single threaded spatial hash set implementation. No remove operation support as we don't need one.
		/// @tparam Key Key type
		/// @tparam Hasher Hash creator class. Its object will be used to hash the keys (std::hash<Key> on default)
		/// @tparam Allocator Memory allocator for internal use. Must satisfy "Allocator" C++ named requirement (https://en.cppreference.com/w/cpp/named_req/Allocator) and be reboundable to other types. std::allocator satisfies those requirements
		template<class Key, class Hasher = std::hash<Key>, class Allocator = std::allocator<Key>>
		class SpatialHashSet
		{
		public:
			SpatialHashSet(const unsigned int defaultSlotCount = 32);
			~SpatialHashSet() = default;

			bool tryInsert(Key&& key);
			bool isKeyPresent(const Key& key) const;

			void rehash(const unsigned int newSlotCount);

			std::size_t size() const;
			std::size_t capacity() const;
		private:
			struct Cell
			{
				bool occupied = false;
				Key key;
			};
		private:
			unsigned int incrementSlotCount;
			Hasher hasher;
			std::vector<Cell, std::allocator_traits<Allocator>::rebind_alloc<Cell>> memory;
		};
	}
}

#include "../src/SingleThreadedSpatialHashSet.inl"

#endif
