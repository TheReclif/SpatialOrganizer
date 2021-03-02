#pragma once
#ifndef SPATIALORGANIZER_CONCURRENTLIST_HPP
#define SPATIALORGANIZER_CONCURRENTLIST_HPP

#include <memory>
#include <atomic>
#include <mutex>
#include <condition_variable>

#include <ConcurrentSharedPtr.hpp>

namespace Spatial
{
	template<typename T, class Allocator = std::allocator<T>>
	class ConcurrentStrippedList
	{
	public:
		class Node;

		ConcurrentStrippedList() {}

		void push_front(const T& value)
		{
			push_front_node(new Node(value));
		}
		void push_front(T&& value)
		{
			push_front_node(new Node(std::move(value)));
		}

		void remove(const NodePointer& n)
		{
			Node* np = n.get();
			if (np == nullptr)
				return;

			if (head.get() == np)
			{
				if (head.setIf(np->next, np))
				{
					np->next.reset();
					return;
				}
			}

			NodePointer p = head;
			
			while (p.get() != nullptr && p.)
			{
				//
			}
		}
		
		class NodePointer
		{
		public:
			static void releasePointer(Node* p)
			{
				if (p != nullptr && p->release())
				{
					delete p;
				}
			}

			NodePointer() : pointer(nullptr) {}
			NodePointer(Node* p) : pointer(p)
			{
				if (p != nullptr)
					p->acquire();
			}

			NodePointer& operator = (const NodePointer& t)
			{
				Node* tmp = t.pointer.exchange(nullptr);

				if (tmp != nullptr)
				{
					tmp->acquire();
					Node* exptected = nullptr;
					if (!t.pointer.compare_exchange_strong(expected, tmp))
					{
						tmp->release();
					}
					tmp = pointer.exchange(tmp);
					releasePointer(tmp);
				}

				return *this;
			}

			Node* get() const
			{
				return pointer.load();
			}

			Node* getAquire()
			{
				Node* tmp = pointer.exchange(nullptr);
				if (tmp != nullptr)
				{
					tmp->acquire();
					Node* exptected = nullptr;
					if (!pointer.compare_exchange_strong(expected, tmp))
					{
						tmp->release();
					}
				}
				return tmp;
			}

			Node* set(Node* value)
			{
				return pointer.exchange(value);
			}
			Node* setIf(Node* value, Node* expected)
			{
				if (!pointer.compare_exchange_weak(expected, value))
				{
					return expected;
				}
				return nullptr;
			}

			void reset()
			{
				Node* tmp = pointer.exchange(nullptr);
				releasePointer(tmp);
			}
		private:
			mutable std::atomic<Node*> pointer;
		};
		class Node
		{
		public:
			T value;

			NodePointer next;

			Node(const T& t) : value(t), ref_count(0) {}
			Node(T&& t) : value(std::move(t)), ref_count(0) {}

			void acquire()
			{
				ref_count.fetch_add(1);
			}
			bool release()
			{
				return ref_count.fetch_sub(1) <= 1;
			}
		private:
			std::atomic<size_t> ref_count;
		};
	
	private:
		
		NodePointer head;

		void push_front_node(Node* val)
		{
			NodePointer p(val);
			Node* next = nullptr;
			while (next = head.setIf(val, next)
			{
				val->next->set(next);
			}
		}
	};
}

#endif