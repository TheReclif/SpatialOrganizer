#pragma once
#ifndef SPATIALORGANIZER_STSPATIALHASHSET_H
#define SPATIALORGANIZER_STSPATIALHASHSET_H

#include <functional>
#include <vector>
#include <memory>
#include <stdexcept>

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
			/// @brief Default constructor.
			/// @param defaultSlotCount Capacity of the container after its initialization
			SpatialHashSet(const unsigned int defaultSlotCount = 32);
			~SpatialHashSet() = default;

			/// @brief Tries to insert the key into the hash set. If it's not possible because the capacity is too small, the rehashing operation will take place, increasing the capacity of the container by steps consisting of "defaultSlotCount" elements. Complexity: amortized constant on average, worst case linear in the size of the container.
			/// @param key Key to insert
			/// @return true if the insertion took place, false if the key was already present in the hash set
			bool tryInsert(Key&& key);
			/// @brief Checks if the given key is present in the hash set. Same complexity as tryInsert.
			/// @param key Key to check
			/// @return true if the key is present, false otherwise
			bool isKeyPresent(const Key& key) const;

			/// @brief Performs a rehashing operation. The resulting capacity may be greater if the rehashing with the current amount of elements is not possible.
			/// @param newSlotCount Minimum amount of slots for the container to have after the operation
			void rehash(const unsigned int newSlotCount);
			/// @brief Resets the slots. size() becomes 0 afterwards.
			void clear();

			/// @brief Returns the amount of elements
			/// @return Amount of container elements
			std::size_t size() const;
			/// @brief Returns the maximum capacity of this set.
			/// @return Amount of element slots
			std::size_t capacity() const;
		private:
			struct Cell
			{
				bool occupied = false;
				Key key;
			};
			using MemContainer = std::vector<Cell, std::allocator_traits<Allocator>::rebind_alloc<Cell>>;
		private:
			unsigned int incrementSlotCount;
			std::size_t elementsCount;
			Hasher hasher;
			MemContainer memory;
		};
	}
}

#include "../src/SingleThreadedSpatialHashSet.inl"

#endif
