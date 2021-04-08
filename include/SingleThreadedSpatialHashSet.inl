#include "SingleThreadedSpatialHashSet.h"

namespace SpatialOrg
{
	namespace SingleThreaded
	{
		template<class Key, class Hasher, class Allocator>
		SpatialHashSet<Key, Hasher, Allocator>::SpatialHashSet(const unsigned int defaultSlotCount)
			: hasher(), memory(defaultSlotCount), incrementSlotCount(defaultSlotCount), elementsCount(0)
		{
		}

		template<class Key, class Hasher, class Allocator>
		bool SpatialHashSet<Key, Hasher, Allocator>::tryInsert(Key&& key)
		{
			if (size() == capacity())
			{
				rehash(capacity() + incrementSlotCount);
			}

			auto hash = hasher(key) % capacity();
			do
			{
				auto& cell = memory[hash];
				if (!cell.occupied)
				{
					cell.occupied = true;
					cell.key = std::move(key);
					++elementsCount;
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
			} while (hash < capacity());

			rehash(capacity() + incrementSlotCount);
			return tryInsert(std::move(key));
		}

		template<class Key, class Hasher, class Allocator>
		bool SpatialHashSet<Key, Hasher, Allocator>::isKeyPresent(const Key& key) const
		{
			auto hash = hasher(key) % capacity();
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
			} while (hash < capacity());

			return false;
		}

		template<class Key, class Hasher, class Allocator>
		void SpatialHashSet<Key, Hasher, Allocator>::rehash(const unsigned int newSlotCount)
		{
			if (newSlotCount == 0)
			{
				throw std::invalid_argument("newSlotCount must be greater than 0");
			}
			if (newSlotCount < capacity())
			{
				throw std::invalid_argument("newSlotCount must be greater than or equal the set's capacity");
			}

			MemContainer newMem(newSlotCount);
			for (const auto& x : memory)
			{
				if (!x.occupied)
				{
					continue;
				}

				auto hash = hasher(x.key) % newSlotCount;
				do
				{
					auto& slot = newMem[hash];
					if (!slot.occupied)
					{
						slot = x;
						hash = newSlotCount;
					}
					++hash;
				} while (hash < newSlotCount);

				if (hash == newSlotCount)
				{
					newMem.clear();
					newMem.shrink_to_fit();
					rehash(newSlotCount + incrementSlotCount);
					return;
				}
			}

			memory = std::move(newMem);
		}

		template<class Key, class Hasher, class Allocator>
		void SpatialHashSet<Key, Hasher, Allocator>::clear()
		{
			if (size() == 0)
			{
				return;
			}
			for (auto& x : memory)
			{
				x.occupied = false;
			}
			elementsCount = 0;
		}

		template<class Key, class Hasher, class Allocator>
		std::size_t SpatialHashSet<Key, Hasher, Allocator>::size() const
		{
			return elementsCount;
		}

		template<class Key, class Hasher, class Allocator>
		std::size_t SpatialHashSet<Key, Hasher, Allocator>::capacity() const
		{
			return memory.capacity();
		}
	}
}
