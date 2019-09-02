#ifndef _STRING_H
#define _STRING_H

namespace cppalgo {
	
	class String 
	{
	public:
		// constructors
		String();		// default constructor
		String(const String& stringSrc);		// copy constructor
		String(char* lpsz);
		String(const char* lpcsz);
		String(char ch);
		String(long i);
		String(int i);
		String(double d);
		~String();
		
		// basics
		int GetLength() const;
		bool IsEmpty() const;
		void Empty();
		char GetAt(int index) const;
		void SetAt(int index, char ch);
		int Compare(const String& s) const;
		int CompareNoCase(const String& s) const;
		void Concat(const String& str);
		
		// conversions
		operator const char*() const;
		
		// operator overloading
		char operator[](int index) const;
		const String& operator =(const String& stringSrc);
		const String& operator +=(const String& string);

		String operator +(const String& str) const;
		bool operator ==(const String& str) const;
		bool operator !=(const String& str) const;
		bool operator >(const String& str) const;
		
		// substring
		String Mid(int nFirst, int nCount = -1) const;
		String Left(int nCount) const; 
		String Right(int nCount) const;
		
		// conversion
		void MakeUpper();
		void MakeLower();
		
		// find/replace
		int Replace(const String& strOld, const String& strNew);
		int Find(const String& str, int nStart = 0) const;
		int ReverseFind(char ch) const;
		int FindOneOf(const char* lpszSep) const;
		int FindNoCase(const String& str, int nStart = 0) const;
		
		void TrimLeft();
		void TrimRight();
		
		// format
		void Format(const char* lpszFormat, ...);
		
		// Tokenize
		String GetToken(const char* lpszSep, int& nPos);
		
	protected:
		char *m_pBuffer;
		
		// inner function
		void _init();
		void _clear();
		void _copy(const char* lpsz);
	};
	
};

#endif /*_STRING_H*/