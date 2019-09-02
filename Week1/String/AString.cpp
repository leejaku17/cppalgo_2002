#include <string.h>
#include <stdlib.h>
#include <stdarg.h>
#include <stdio.h>
#include "AString.h"

#ifndef min
#define min(a,b) ((a) < (b) ? (a) : (b))
#endif

// operator overloading (with friend)


using namespace cppalgo;

// inner functions
void String::_init()
{
	m_pBuffer = 0;
}

void String::_clear()
{
	if (m_pBuffer)
		delete [] m_pBuffer;
	_init();
}

void String::_copy(const char* lpsz)
{
	if (lpsz != 0) {
		int len = strlen(lpsz);
		m_pBuffer = new char [len + 1];
		if (m_pBuffer) {
			strcpy(m_pBuffer, lpsz);
		}
	}
}

// constructors

String::String()
{
	_init();
}

String::String(const String& stringSrc)
{
	_init();
	_copy(stringSrc.m_pBuffer);
}

String::String(const char* lpsz)
{
	_init();
	_copy(lpsz);
}

String::String(char* lpsz)
{
	_init();
	_copy(lpsz);
}

String::String(char ch)
{
	char str[2];
	str[0] = ch;
	str[1] = 0;
	
	_init();
	_copy(str);
}

String::String(long i)
{
	_init();
	Format("%d", i);
}

String::String(int i)
{
	_init();
	Format("%d", i);
}

String::String(double d)
{
	_init();
	Format("%g", d);
}

String::~String()
{
	_clear();
}

// basic operations

int String::GetLength() const
{
	if (m_pBuffer)
		return strlen(m_pBuffer);
	else
		return 0;
}

bool String::IsEmpty() const
{
	if (m_pBuffer) 
		return strlen(m_pBuffer) == 0;
	else
		return true;
}

void String::Empty()
{
	_clear();
}

char String::GetAt(int index) const
{
	if (index < 0 || index >= GetLength()) 
		return 0;
	else
		return m_pBuffer[index];
}

void String::SetAt(int index, char ch)
{
	if (index >= 0 || index < GetLength()) 
		m_pBuffer[index] = ch;
}

void String::Concat(const String& str)
{
	if (str.GetLength() == 0) {		// 더할게 없으면 그냥 리턴 
		return;
	}
	int len = GetLength() + str.GetLength() + 1;
	char *ptemp = new char [len];
	if (ptemp == 0) {
		return;		// 메모리 할당 에러 
	}
	
	ptemp[0] = 0;		// 빈 스트링으로 설정 
	
	if (!IsEmpty()) {
		strcpy(ptemp, m_pBuffer);
	}
	if (!str.IsEmpty()) {
		strcat(ptemp, str.m_pBuffer);
	}
	
	_clear();		// 기존의 버퍼 지움 
	m_pBuffer = ptemp;
}

char String::operator [] (int index) const
{
	return GetAt(index);
}

String::operator const char*() const
{
	return m_pBuffer;
}

const String& String::operator += (const String& string)
{
	Concat(string);
	return *this;
}


const String& String::operator = (const String& stringSrc)
{
	_clear();
	_copy(stringSrc.m_pBuffer);
	return *this;
}

String String::operator + (const String& str) const
{
	String str2;
	str2 = *this;
	str2.Concat(str);
	return str2;
}

bool String::operator == (const String& str) const
{
	if (Compare(str) == 0)
		return true;
	else
		return false;
}

bool String::operator != (const String& str) const
{
	return !(*this == str);
}

bool String::operator > (const String& str) const
{
	return Compare(str) > 0;
}

int String::Compare(const String& s) const
{
	if (m_pBuffer == 0 && s.m_pBuffer == 0)
		return 0;
	else if (m_pBuffer == 0 && s.m_pBuffer != 0)
		return -1;
	else if (m_pBuffer != 0 && s.m_pBuffer == 0)
		return 1;
	else
		return strcmp(m_pBuffer, s.m_pBuffer);
}

int String::CompareNoCase(const String& s) const
{
	return strcmpi(m_pBuffer, s.m_pBuffer);
}

void String::MakeUpper()
{
	for (int i = 0; i < GetLength(); i++) 
		m_pBuffer[i] = (char)toupper(m_pBuffer[i]);
}

void String::MakeLower()
{
	for (int i = 0; i < GetLength(); i++)
		m_pBuffer[i] = (char)tolower(m_pBuffer[i]);
}

void String::Format(const char* lpszFormat, ...)
{
    va_list arglist;

	char temp[8192];

    va_start(arglist, lpszFormat);
    vsprintf(temp, lpszFormat, arglist);
    va_end(arglist);

	_clear();
    
	_copy(temp); 	
}

int String::Replace(const String& strOld, const String& strNew)
{
	int start = 0;
	int index = 0;
	int nCount = 0;
	String str;

	while (index >= 0) {
		index = Find(strOld, start);
		if (index >= 0) {
			str += Mid(start, index - start);
			str += strNew;
			start = index + strOld.GetLength();
			nCount++;
		}
	}

	str += Mid(start);

	*this = str;

	return nCount;
}

int String::Find(const String& str, int nStart) const
{
	int index = -1;

	if (str.IsEmpty())
		return -1;

	if (IsEmpty())
		return -1;

	char *p = strstr(m_pBuffer + nStart , str);
	if (p == 0) {
		return -1;
	} else {
		return (p - m_pBuffer);
	}

	return index;
}

int String::FindNoCase(const String& str, int nStart) const
{
	int index = -1;
	if (str.IsEmpty()) 
		return index;

	int nCount = GetLength() - str.GetLength();
	for (int i = nStart; i < nCount; i++) {
		if (strnicmp(m_pBuffer + i, str.m_pBuffer, str.GetLength()) == 0) {
			index = i;
			return index;
		}
	}

	return index;
}

int String::ReverseFind(char ch) const
{
	for (int i = GetLength() - 1; i >= 0; i--) {
		if (m_pBuffer[i] == ch) {
			return i;
		}
	}
	return i;
}

int String::FindOneOf(const char* lpszSep) const
{
	if (m_pBuffer == 0) {
		return -1;
	}

	int i, j;
	for (i = 0; i < GetLength(); i++) {
		bool fFound = false;
		for (j = 0; j < (int)strlen(lpszSep); j++) {
			if (lpszSep[j] == m_pBuffer[i]) {
				fFound = true;
				break;
			}
		}

		if (fFound) {
			return i;
		}
	}

	return -1;
}

String String::Mid(int nFirst, int nCount) const
{
	String str;
	int len = GetLength();

	if (nFirst < len) {
		if (nCount < 0) {
			str._copy(m_pBuffer + nFirst);
		} else {
			int realCount = min(len - nFirst, nCount);
			char *temp = new char [realCount + 1];
			if (temp) {
				memcpy(temp, m_pBuffer + nFirst, realCount);
				temp[realCount] = 0;
				str._clear();
				str.m_pBuffer = temp;
			}
		}
	} 

	return str;
}

String String::Left(int nCount) const
{
	return Mid(0, nCount);
}

String String::Right(int nCount) const
{
	return Mid(GetLength() - nCount, nCount);
}

void String::TrimLeft()
{
	if (m_pBuffer == 0) {
		return;
	}

	char ws[] = " \t\r\n\b";
	int index = 0;

	for (index = 0; index < GetLength(); index ++) {
		if (strchr(ws, m_pBuffer[index]) != 0) {

		} else {
			break;
		}
	}

	String str(m_pBuffer + index);
	*this = str;
}

void String::TrimRight()
{
	if (m_pBuffer == 0) {
		return;
	}

	char ws[] = " \t\r\n\b";
	int index;

	for (index = GetLength() - 1; index >= 0; index--) {
		if (strchr(ws, m_pBuffer[index]) == 0){
			break;
		}
	}

	String str = Left(index + 1);
	*this = str;
}

String String::GetToken(const char* lpszSep, int& nPos)
{
	int index = 0;

	if (nPos < 0) {
		return "";
	}

	String strSrc = Mid(nPos);

	index = strSrc.FindOneOf(lpszSep);

	if (index >= 0) {
		nPos = nPos + index + 1;
		return strSrc.Left(index);
	} else {
		nPos = -1;
		return strSrc;
	}
}
