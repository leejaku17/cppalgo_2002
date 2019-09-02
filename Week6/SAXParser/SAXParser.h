#ifndef _SAXParser_h
#define _SAXParser_h

#include "../String/AString.h"
#include "../SList/DList.h"

#pragma comment(lib, "../cppalgo/Release/cppalgo.lib")

namespace cppalgo {

class SAXParser 
{
public:
	SAXParser();
	virtual ~SAXParser();

	void Clear();
	bool AddStream(const char* pBuf, unsigned long dwLen);

	// overridables
	class Attributes;
	virtual bool OnStartDocument();
	virtual bool OnEndDocument();
	virtual bool OnStartElement(const String& strTagName, const Attributes& Attr, const String& strTagHierachy);
	virtual bool OnEndElement(const String& strTagName, const Attributes& Attr, const String& strTagHierachy, const String& strText);

public:
	static bool IsWS(char ch);
	static bool IsAlnum(char ch);

protected:	// inner classes
	class SAXBuffer  
	{
	public:
		SAXBuffer();
		virtual ~SAXBuffer();
		void SetIncrease(unsigned long dwLen);
		unsigned long Add(const char* pSrc, unsigned long dwLen);
		unsigned long Add(char ch);
		long AddAutomata(char ch, bool bPreserveSpace);
		const char* GetBuffer() const;
		unsigned long GetLength() const { return m_dwLen; }
		void Clear();
		
		bool PushBack(char ch);
		bool PushBack(void);
		bool Rewind();
		char GetNext();
		bool ClearGarbage();

		SAXBuffer(const SAXBuffer& buf);
		const SAXBuffer& operator=(const SAXBuffer& buf);
		
	protected:
		enum State {
			STATE_INITIAL,
			STATE_COLLECT_CHAR,
			STATE_SKIP_WS1,
			STATE_SKIP_WS2,
			STATE_AMP_COLLECT,
		};
		bool _prepareBuffer(unsigned long dwLen);
		char *m_pBuffer;
		unsigned long m_dwLen;
		unsigned long m_dwPhysicalLen;
		unsigned long m_dwStartPos;
		unsigned long m_dwIncrease;

		State m_state;
		String m_strTemp;
	};

public:
	class Attributes
	{
	public:
		Attributes();
		virtual ~Attributes();
		Attributes(const Attributes& a) { m_listItems = a.m_listItems; }
		const Attributes& operator=(const Attributes& a) { m_listItems = a.m_listItems; return *this; }

		unsigned long GetCount() const;
		bool GetValue(const char* pAttrName, String& strAttrValue) const ;
		bool GetValue(unsigned long dwIndex, String& strAttrName, String& strAttrValue) const;
		
	public:
		struct stItem {
			String m_strName;
			SAXBuffer m_bufValue;
		};
		bool AddName(const char* szName);
		long AddValueAutomata(char ch);
		
	protected:
		DoubleList<stItem> m_listItems;		
	};

protected:
	struct stElement
	{
		Attributes m_attr;
		String m_strTag;
		SAXBuffer m_bufText;
	};

private:
	enum ParseState {
		STATE_INITIAL,
		STATE_SKIP_WS,
		STATE_START_OPEN_TAG,
		STATE_COLLECT_OPEN_TAG,
		STATE_COLLECT_CLOSE_TAG,
		STATE_SKIP_QUESTION,
		STATE_COLLECT_ATTR,
		STATE_START_ATTR_VALUE,
		STATE_COLLECT_ATTR_VALUE_SQ,
		STATE_COLLECT_ATTR_VALUE_DQ,
		STATE_COLLECT_ATTR_VALUE_NQ,
	};
private:	// inner functions
	long AddText(char ch);
	bool CallStartElement();
	bool CallEndElement();
	String GetTagHierachy();
	bool PushElement(const char* szTag);
	bool PopElement();
	bool CheckTagPair(const char *szTag);
	bool AddAttrName(const char* szAttrName);
	long AddAttrValue(char ch);
private:	// data members
	SAXBuffer m_buf;
	SAXBuffer m_bufTemp;
	ParseState m_state;
	ParseState m_stateNext;
	DoubleList<stElement> m_listElements;
	bool m_bStarted;
};

};

#endif
