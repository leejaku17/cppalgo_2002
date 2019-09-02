#ifndef _CircularQueue_h
#define _CircularQueue_h

namespace cppalgo
{
	template <class TYPE> class CircularQueue
	{
	public:
		enum Exception {
			QUEUE_OVERFLOW,
			QUEUE_UNDERFLOW,
			INVALID_QUEUE_SIZE,
			MEMALLOC_FAILED,
			QUEUE_EMPTY
		};
	public:
		CircularQueue(long nSize = 100);
		~CircularQueue() { delete [] m_pArray; }

		long GetCount() const { return m_nCount; }
		bool IsEmpty() const { return GetCount() == 0; }
		void RemoveAll() { m_nFront = m_nRear; }

		TYPE GetFront() const;
		TYPE GetRear() const;

		void Put(const TYPE& newElem);
		TYPE Get();

	protected:
		long _inc(long n) const { return (n + 1) % m_nSize; }
		long _dec(long n) const { return (n + m_nSize - 1) % m_nSize; }

		TYPE* m_pArray;
		long m_nFront;
		long m_nRear;
		long m_nCount;
		long m_nSize;
	};

	template <class TYPE> CircularQueue<TYPE>::CircularQueue(long nSize)
	{
		if (nSize <= 0)
			throw INVALID_QUEUE_SIZE;
		m_pArray = new TYPE [nSize];
		if (m_pArray == 0)
			throw MEMALLOC_FAILED;

		m_nFront = m_nRear = 0;
		m_nCount = 0;
		m_nSize = nSize;
	}

	template <class TYPE> TYPE CircularQueue<TYPE>::GetFront() const
	{
		if (IsEmpty())
			throw QUEUE_EMPTY;
		return m_pArray[m_nFront];
	}

	template <class TYPE> TYPE CircularQueue<TYPE>::GetRear() const
	{
		if (IsEmpty())
			throw QUEUE_EMPTY;
		return m_pArray[_dec(m_nRear)];
	}

	template <class TYPE> void CircularQueue<TYPE>::Put(const TYPE& newElem)
	{
		if (_inc(m_nRear) == m_nFront)
			throw QUEUE_OVERFLOW;
		m_pArray[m_nRear] = newElem;
		m_nRear = _inc(m_nRear);
		m_nCount++;
	}

	template <class TYPE> TYPE CircularQueue<TYPE>::Get()
	{
		if (m_nFront == m_nRear)	// È¤Àº IsEmpty()
			throw QUEUE_UNDERFLOW;

		TYPE t = m_pArray[m_nFront];
		m_nFront = _inc(m_nFront);
		m_nCount--;
		return t;
	}
};

#endif