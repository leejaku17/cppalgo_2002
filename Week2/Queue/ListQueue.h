#ifndef _ListQueue_h
#define _ListQueue_h

#include "../SList/DList.h"

namespace cppalgo
{
	template <class TYPE> class ListQueue
	{
	public:
		enum Exception {
			QUEUE_OVERFLOW,
			QUEUE_UNDERFLOW,
			QUEUE_EMPTY
		};
	public:
		ListQueue() {}
		~ListQueue() {}

		long GetCount() const { return m_list.GetCount(); }
		bool IsEmpty() const { return m_list.IsEmpty(); }
		void RemoveAll() { m_list.RemoveAll(); }

		TYPE GetFront() const;
		TYPE GetRear() const;

		void Put(const TYPE& newElem);
		TYPE Get();

	protected:
		DoubleList<TYPE> m_list;
	};

	template <class TYPE> TYPE ListQueue<TYPE>::GetFront() const
	{
		TYPE t;
		try {
			t = m_list.GetHead();
		} catch (DoubleList<TYPE>::Exception) {
			throw QUEUE_EMPTY;
		}
		return t;
	}

	template <class TYPE> TYPE ListQueue<TYPE>::GetRear() const
	{
		TYPE t;
		try {
			t = m_list.GetTail();
		} catch (DoubleList<TYPE>::Exception) {
			throw QUEUE_EMPTY;
		}
		return t;
	}

	template <class TYPE> void ListQueue<TYPE>::Put(const TYPE& newElem)
	{
		m_list.AddTail(newElem);
	}

	template <class TYPE> TYPE ListQueue<TYPE>::Get()
	{
		TYPE t;
		try {
			t = m_list.RemoveHead();
		} catch (DoubleList<TYPE>::Exception) {
			throw QUEUE_UNDERFLOW;
		}	
		return t;
	}
};

#endif