#ifndef _ListStack_h
#define _ListStack_h

#include "../SList/SList.h"

namespace cppalgo
{
	template <class TYPE> class ListStack
	{
	public:
		enum Exception {
			STACK_OVERFLOW,
			STACK_UNDERFLOW,
			STACK_EMPTY
		};

	public:
		ListStack() {}
		~ListStack() {}

		long GetCount() const { return m_list.GetCount(); }
		bool IsEmpty() const { return m_list.IsEmpty(); }
		void RemoveAll() { m_list.RemoveAll(); }

		TYPE GetTop() const;
		void Push(const TYPE& newElem);
		TYPE Pop();

	protected:
		SimpleList<TYPE> m_list;
	};

	template <class TYPE> TYPE ListStack<TYPE>::GetTop() const
	{
		TYPE t;
		try {
			t = m_list.GetHead();
		} catch (SimpleList<TYPE>::Exception) {
			throw STACK_EMPTY;
		}
		return t;
	}

	template <class TYPE> void ListStack<TYPE>::Push(const TYPE& newElem)
	{ 
		m_list.AddHead(newElem); 
	}

	template <class TYPE> TYPE ListStack<TYPE>::Pop()
	{
		TYPE t;
		try {
			t = m_list.RemoveHead();
		} catch (SimpleList<TYPE>::Exception) {
			throw STACK_UNDERFLOW;
		}
		return t;
	}
};

#endif