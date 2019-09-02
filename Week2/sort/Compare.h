#ifndef _Compare_h
#define _Compare_h

// operator> 와 operator== 만 정의하면 
// >= != <= < 연산자를 쓸 수 있도록  해줌. 

template <class TYPE> bool operator<(const TYPE& a, const TYPE& b)
{
	return b > a;
}

template <class TYPE> bool operator>=(const TYPE& a, const TYPE& b)
{
	return (a > b || a == b);
}

template <class TYPE> bool operator<=(const TYPE& a, const TYPE& b)
{
	return (b > a || a == b);
}

template <class TYPE> bool operator!=(const TYPE& a, const TYPE& b)
{
	return !(a == b);
}	


#endif