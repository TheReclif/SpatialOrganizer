#include "../include/SingleThreadedSpatialHashSet.h"

namespace SpatialOrg
{
	namespace SingleThreaded
	{
		template<class Key, class Hasher, class Allocator>
		SpatialHashSet<Key, Hasher, Allocator>::SpatialHashSet(const unsigned int defaultSlotCount)
			: hasher(), memory(defaultSlotCount), incrementSlotCount(defaultSlotCount)
		{
		}

		template<class Key, class Hasher, class Allocator>
		bool SpatialHashSet<Key, Hasher, Allocator>::tryInsert(Key&& key)
		{
			auto hash = hasher(key) % size();
			do
			{
				auto& cell = memory[hash];
				if (!cell.occupied)
				{
					cell.occupied = true;
					cell.key = std::move(key);
					return true;
				}
				else
				{
					if (cell.key == key)
					{
						return false;
					}
				}
				++hash;
			} while (hash < size());

			rehash(size() + incrementSlotCount);
			return tryInsert(std::move(key));
		}

		template<class Key, class Hasher, class Allocator>
		bool SpatialHashSet<Key, Hasher, Allocator>::isKeyPresent(const Key& key) const
		{
			auto hash = hasher(key) % size();
			do
			{
				auto& cell = memory[hash];
				if (cell.occupied)
				{
					if (cell.key == key)
					{
						return true;
					}
				}
				else
				{
					return false;
				}
				++hash;
			} while (hash < size());

			return false;
		}
	}
}
