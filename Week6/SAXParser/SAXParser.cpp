#include "SAXParser.h"
#include <string.h>

using namespace cppalgo;

///////////////////////////////////////////////////////////
//   SAXParser
///////////////////////////////////////////////////////////

SAXParser::SAXParser()
{
	Clear();
}

SAXParser::~SAXParser()
{

}

void SAXParser::Clear()
{
	m_bStarted = false;

	m_state = STATE_INITIAL;
	m_stateNext = STATE_INITIAL;
	m_buf.Clear();
	m_bufTemp.Clear();
	m_listElements.RemoveAll();
}

bool SAXParser::OnStartDocument()
{
	return true;
}	

bool SAXParser::OnEndDocument()
{
	return true;
}

bool SAXParser::OnStartElement(const String& strTagName, const Attributes& Attr, const String& strTagHierachy)
{
	return true;
}

bool SAXParser::OnEndElement(const String& strTagName, const Attributes& Attr, const String& strTagHierachy, const String& strText)
{
	return true;
}

bool SAXParser::AddStream(const char* pBuf, unsigned long dwLen)
{
	// 일단 버퍼에 넣고 
	m_buf.Add(pBuf, dwLen);
	char ch;

	bool fResult = true;

	// 오토마타 시작 
	while (true) {
		ch = m_buf.GetNext();
		if (ch == 0) {
			break;
		}

		if (m_state == STATE_INITIAL) {
			if (ch == '<') {
				if (!m_bStarted) {
					OnStartDocument();
					m_bStarted = true;
				}
				m_state = STATE_SKIP_WS;
				m_stateNext = STATE_START_OPEN_TAG;
			} else {
				if (m_listElements.IsEmpty()) {
					// discard all
					// 태그 바깥쪽의 텍스트다...
				} else {
					if (AddText(ch) < 0) {
						m_buf.PushBack();
					}
					//OnCollect(ch);
				}
			}
		} else if (m_state == STATE_SKIP_WS) {
			if (IsWS(ch)) {
				// discard white space	
			} else {
				m_state = m_stateNext;
				m_buf.PushBack();
			}
		} else if (m_state == STATE_START_OPEN_TAG) {
			//m_bufTemp.Clear();
			if (ch == '?') {
				m_state = STATE_SKIP_QUESTION;
			} else if (ch == '/') {
				m_state = STATE_COLLECT_CLOSE_TAG;	
			} else if (ch == '>') {
				// do nothing;
			} else {	
				m_bufTemp.Add(ch);
				m_state = STATE_COLLECT_OPEN_TAG;
			}
		} else if (m_state == STATE_COLLECT_OPEN_TAG) {
			if (ch == '/') {
				ch = m_buf.GetNext();
				if (ch == '>') {
					PushElement(m_bufTemp.GetBuffer());
					fResult = CallStartElement();
					if (!fResult) {
						break;
					}
					fResult = CallEndElement();
					if (!fResult) {
						break;
					}
					PopElement();
					if (m_listElements.GetCount() == 0) OnEndDocument();
					m_bufTemp.Clear();
					m_state = STATE_INITIAL;
				} else if (ch == 0) {
					m_buf.PushBack();					
					break;
				} else {		
					// '/>' 가 아니면 다시 물림.
					m_buf.PushBack();
					m_bufTemp.Add(ch);
				}
			} else if (ch == '>') {
				PushElement(m_bufTemp.GetBuffer());
				fResult = CallStartElement();
				if (!fResult) {
					break;
				}
				m_bufTemp.Clear();
				m_state = STATE_INITIAL;
			} else if (IsWS(ch)) {
				m_stateNext = STATE_COLLECT_ATTR;
				m_state = STATE_SKIP_WS;				
				PushElement(m_bufTemp.GetBuffer());
				m_bufTemp.Clear();				
			} else {
				m_bufTemp.Add(ch);
			}
		} else if (m_state == STATE_COLLECT_ATTR) {
			if (ch == '/') {
				ch = m_buf.GetNext();
				if (ch == '>') {
//					PushItem(m_bufTemp.GetBuffer());
					fResult = CallStartElement();
					if (!fResult) {
						break;
					}
					fResult = CallEndElement();
					if (!fResult) {
						break;
					}
					m_bufTemp.Clear();
					PopElement();
					if (m_listElements.GetCount() == 0) OnEndDocument();
					m_state = STATE_INITIAL;
				} else if (ch == 0) {
					m_buf.PushBack();					
					break;
				} else {		
					// '/>' 가 아니면 다시 물림.
					m_buf.PushBack();
					m_bufTemp.Add(ch);
				}
			} else if (ch == '>') {
				fResult = CallStartElement();
				if (!fResult) {
					break;
				}
				m_state = STATE_INITIAL;
			} else if (ch == '=') {
				AddAttrName(m_bufTemp.GetBuffer());
				m_bufTemp.Clear();
				m_state = STATE_SKIP_WS;
				m_stateNext = STATE_START_ATTR_VALUE;
			} else if (IsWS(ch)) { 
				// skip
			} else {
				// attr name
				m_bufTemp.Add(ch);
			}
		} else if (m_state == STATE_START_ATTR_VALUE) {
			if (ch == '\'') {
				m_state = STATE_COLLECT_ATTR_VALUE_SQ;
			} else if (ch == '\"') {
				m_state = STATE_COLLECT_ATTR_VALUE_DQ;
			} else {
				m_state = STATE_COLLECT_ATTR_VALUE_NQ;
			}
		} else if (m_state == STATE_COLLECT_ATTR_VALUE_SQ) {
			if (ch == '\'') {
				m_state = STATE_SKIP_WS;
				m_stateNext = STATE_COLLECT_ATTR;
			} else {
				if (AddAttrValue(ch) < 0) m_buf.PushBack();
			}
		} else if (m_state == STATE_COLLECT_ATTR_VALUE_DQ) {
			if (ch == '\"') {
				m_state = STATE_SKIP_WS;
				m_stateNext = STATE_COLLECT_ATTR;
			} else {
				if (AddAttrValue(ch) < 0) m_buf.PushBack();
			}
		} else if (m_state == STATE_COLLECT_ATTR_VALUE_NQ) {
			if (IsWS(ch)) {
				m_state = STATE_SKIP_WS;
				m_stateNext = STATE_COLLECT_ATTR;
			} else {
				if (AddAttrValue(ch) < 0) m_buf.PushBack();
			}
		} else if (m_state == STATE_COLLECT_CLOSE_TAG) {
			if (ch == '>') {
				if (CheckTagPair(m_bufTemp.GetBuffer())) {
					fResult = CallEndElement();
					if (!fResult) {
						break;
					}
					PopElement();
					if (m_listElements.GetCount() == 0) OnEndDocument();
				}
				m_bufTemp.Clear();
				m_state = STATE_INITIAL;
			} else {
				m_bufTemp.Add(ch);
			}
		} else if (m_state == STATE_SKIP_QUESTION) {
			if (ch == '?') {
				ch = m_buf.GetNext();
				if (ch == '>') {
					m_state = STATE_INITIAL;
				} else if (ch == 0) {
					m_buf.PushBack();
					break;
				} else {
					// discard
				}
			} else {
				// discard all except '?'
			}
		} else {
			
		}
	}

	m_buf.ClearGarbage();

	return fResult;
}

long SAXParser::AddText(char ch)
{
	long result = 0;
	if (m_listElements.GetCount() > 0) {
		stElement& elem = m_listElements.GetTail();
		
		String strXmlSpace;
		elem.m_attr.GetValue("xml:space", strXmlSpace);
		
		result = elem.m_bufText.AddAutomata(ch, strXmlSpace.Compare("preserve") == 0);
		return result;
	} else {
		return 0;
	}
}

bool SAXParser::IsWS(char ch)
{
	if (ch == ' ' || ch == '\t' || ch == '\r' || ch == '\n' || ch == '\b') {
		return true;
	} else {
		return false;
	}
}

bool SAXParser::IsAlnum(char ch)
{
	if ((ch >= 'a' && ch <= 'z') || (ch >= 'A' && ch <= 'Z') || (ch >= '0' && ch <= '9')) {
		return true;
	} else {
		return false;
	}
}

bool SAXParser::CallStartElement()
{
	if (m_listElements.GetCount() > 0) {
		stElement& elem = m_listElements.GetTail();
		String strHierachy = GetTagHierachy();
		return OnStartElement(elem.m_strTag, elem.m_attr, strHierachy);
	}
	return false;
}

bool SAXParser::CallEndElement()
{
	if (m_listElements.GetCount() > 0) {
		stElement& elem = m_listElements.GetTail();
		String strHierachy = GetTagHierachy();
		return OnEndElement(elem.m_strTag, elem.m_attr, strHierachy, elem.m_bufText.GetBuffer());
	}
	return false;
}

String SAXParser::GetTagHierachy()
{
	String strHierachy;
	POS pos = m_listElements.GetHeadPosition();
	while (pos) {
		stElement& elem = m_listElements.GetNext(pos);
		strHierachy += elem.m_strTag + "/";
	}

	return strHierachy;
}

bool SAXParser::PushElement(const char* szTag)
{
	stElement elem;
	elem.m_strTag = szTag;
	m_listElements.AddTail(elem);

	return true;
}

bool SAXParser::PopElement()
{
	if (m_listElements.GetCount() > 0) {
		m_listElements.RemoveTail();
		return true;
	} else return false;
}

bool SAXParser::AddAttrName(const char* szAttrName)
{
	if (m_listElements.GetCount() > 0) {
		stElement& elem = m_listElements.GetTail();
		return elem.m_attr.AddName(szAttrName);
	}
	return false;
}

long SAXParser::AddAttrValue(char ch)
{
	long result = 0;
	if (m_listElements.GetCount() > 0) {
		stElement& elem = m_listElements.GetTail();
		result = elem.m_attr.AddValueAutomata(ch);
		return result;
	} else {
		return 0;
	}
}

bool SAXParser::CheckTagPair(const char *szTag)
{
	if (m_listElements.GetCount() > 0) {
		stElement& elem = m_listElements.GetTail();
		if (elem.m_strTag.Compare(szTag) == 0) {
			return true;
		} else {
			return false;
		}
	} else {
		return false;
	}
}

///////////////////////////////////////////////////////////
//  SAXParser::Attributes
///////////////////////////////////////////////////////////

SAXParser::Attributes::Attributes()
{

}

SAXParser::Attributes::~Attributes()
{

}

unsigned long SAXParser::Attributes::GetCount() const 
{
	return m_listItems.GetCount();
}

bool SAXParser::Attributes::GetValue(const char* pAttrName, String& strAttrValue) const 
{
	POS pos = m_listItems.GetHeadPosition();
	while (pos) {
		stItem& Item = m_listItems.GetNext(pos);
		if (Item.m_strName.Compare(pAttrName) == 0) {
			strAttrValue = Item.m_bufValue.GetBuffer();
			return true;
		}
	}
	return false;
}

bool SAXParser::Attributes::GetValue(unsigned long dwIndex, String& strAttrName, String& strAttrValue) const 
{
	POS pos = m_listItems.GetHeadPosition();
	int index = 0;
	while (pos) {
		stItem Item = m_listItems.GetNext(pos);
		if (index == (int)dwIndex) {
			strAttrName = Item.m_strName;
			strAttrValue = Item.m_bufValue.GetBuffer();
			return true;
		}
		if (index > (int)dwIndex) {
			break;
		}
		index ++;
	}
	return false;
}
		
bool SAXParser::Attributes::AddName(const char* szName)
{
	stItem Item;
	Item.m_strName = szName;
	m_listItems.AddTail(Item);
	return true;
}

long SAXParser::Attributes::AddValueAutomata(char ch)
{
	long result = 0;
	if (m_listItems.GetCount() > 0) {
		stItem& item = m_listItems.GetTail();
		result = item.m_bufValue.AddAutomata(ch, false);
		return result;
	} else {
		return 0;
	}
}

///////////////////////////////////////////////////////////
//  SAXParser::SAXBuffer
///////////////////////////////////////////////////////////

SAXParser::SAXBuffer::SAXBuffer()
{
	m_pBuffer = 0;
	m_dwLen = 0;
	m_dwPhysicalLen = 0;
	m_dwStartPos = 0;
	m_dwIncrease = 64;
	m_state = STATE_INITIAL;
}

SAXParser::SAXBuffer::~SAXBuffer()
{
	if (m_pBuffer) {
		delete [] m_pBuffer;
	}
	m_pBuffer = 0;
}

void SAXParser::SAXBuffer::Clear()
{
	if (m_pBuffer) {
		delete [] m_pBuffer;
	}
	m_pBuffer = 0;
	m_dwLen = 0;
	m_dwPhysicalLen = 0;
	m_dwStartPos = 0;
	m_state = STATE_INITIAL;
	m_strTemp.Empty();
}

void SAXParser::SAXBuffer::SetIncrease(unsigned long dwLen)
{
	m_dwIncrease = dwLen;
}

bool SAXParser::SAXBuffer::_prepareBuffer(unsigned long dwLen)
{
	if ((int)(dwLen + m_dwLen) > (int)(m_dwPhysicalLen - 1)) {
		int newLen = ((dwLen + m_dwLen + 1 + m_dwIncrease - 1) / m_dwIncrease) * m_dwIncrease;
		char *pTemp = new char [newLen];
		if (pTemp == 0) {
			return false;
		}

		if (m_dwLen > 0 && m_pBuffer != 0) {
			strncpy(pTemp, m_pBuffer, m_dwLen);
			pTemp[m_dwLen] = 0;
			//lstrcpyn(pTemp, m_pBuffer, m_dwLen + 1);
			delete [] m_pBuffer;
		}

		m_pBuffer = pTemp;
		m_dwPhysicalLen = newLen;
	}
	return true;
}

unsigned long SAXParser::SAXBuffer::Add(const char* pSrc, unsigned long dwLen)
{
	int newLen = dwLen;
	if (!_prepareBuffer(newLen)) {
		return 0;
	}

	strncpy(m_pBuffer + m_dwLen, pSrc, newLen);
	m_pBuffer[m_dwLen + newLen] = 0;
	//lstrcpyn(m_pBuffer + m_dwLen, pSrc, newLen + 1);
	m_dwLen += newLen;

	return m_dwLen;
}

unsigned long SAXParser::SAXBuffer::Add(char ch)
{
	if (!_prepareBuffer(1)) {
		return 0;
	}

	m_pBuffer[m_dwLen] = ch;
	m_dwLen ++;

	return m_dwLen;
}

const char* SAXParser::SAXBuffer::GetBuffer() const
{
	//assert(m_dwLen < m_dwPhysicalLen);
	if (m_pBuffer == 0) {
		return "";
	} 

	m_pBuffer[m_dwLen] = 0;

	return m_pBuffer;
}

bool SAXParser::SAXBuffer::PushBack(char ch)
{
//	assert(m_dwStartPos > 0);

	m_dwStartPos--;
	m_pBuffer[m_dwStartPos] = ch;

	return true;
}

bool SAXParser::SAXBuffer::PushBack()
{
//	assert(m_dwStartPos > 0);

	m_dwStartPos--;

	return true;
}

bool SAXParser::SAXBuffer::Rewind()
{
	m_dwStartPos = 0;
	return true;
}

char SAXParser::SAXBuffer::GetNext()
{
	char ch;
	if (m_dwStartPos < m_dwLen) {
		ch = m_pBuffer[m_dwStartPos];
		m_dwStartPos ++;
	} else {
		ch = 0;
	}

	return ch;
}

bool SAXParser::SAXBuffer::ClearGarbage()
{
	int newLen = ((m_dwLen - m_dwStartPos + 1 + m_dwIncrease - 1) / m_dwIncrease) * m_dwIncrease;	
	if (m_pBuffer != 0 && m_dwLen > 0) {
		char *pTemp = new char [newLen];
		if (pTemp == 0) {
			return false;
		}
		strncpy(pTemp, m_pBuffer + m_dwStartPos, m_dwLen - m_dwStartPos);
		pTemp[m_dwLen - m_dwStartPos] = 0;
		//lstrcpyn(pTemp, m_pBuffer + m_dwStartPos, m_dwLen - m_dwStartPos + 1);

		delete [] m_pBuffer;
		m_pBuffer = pTemp;
		m_dwPhysicalLen = newLen;
		m_dwLen = m_dwLen - m_dwStartPos;
		m_dwStartPos = 0;
	}

	return true;
}

long SAXParser::SAXBuffer::AddAutomata(char ch, bool bPreserveSpace)
{
	long result = 1;

	if (m_state == STATE_INITIAL) {
		if (SAXParser::IsWS(ch)) {
			m_state = STATE_SKIP_WS1;
		} else {
			m_state = STATE_COLLECT_CHAR;
			result = -1;	// pushback
		}
	} else if (m_state == STATE_COLLECT_CHAR) {
		if (ch == '&') {
			m_state = STATE_AMP_COLLECT;
		} else if (SAXParser::IsWS(ch)) {
			m_state = STATE_SKIP_WS2;
		} else {
			Add(ch);
			m_state = STATE_COLLECT_CHAR;
		}
	} else if (m_state == STATE_SKIP_WS1) {
		if (bPreserveSpace) {
			Add(ch);
			m_state = STATE_SKIP_WS1;
		} else {
			if (SAXParser::IsWS(ch)) {
				m_state = STATE_SKIP_WS1;
			} else {
				m_state = STATE_COLLECT_CHAR;
				result = -1;    // pushback
			}
		}
	} else if (m_state == STATE_SKIP_WS2) {
		if (bPreserveSpace) {
			Add(ch);
			m_state = STATE_SKIP_WS2;
		} else {
			if (SAXParser::IsWS(ch)) {
				m_state = STATE_SKIP_WS2;
			} else {
				Add(' ');
				m_state = STATE_COLLECT_CHAR;
				result = -1;	// pushback
			}
		}
	} else if (m_state == STATE_AMP_COLLECT) {
		if (ch == ';') {
			if (m_strTemp.Compare("amp") == 0) Add('&');
			else if (m_strTemp.Compare("gt") == 0) Add('>');
			else if (m_strTemp.Compare("lt") == 0) Add('<');
			else if (m_strTemp.Compare("apos") == 0) Add('\'');
			else if (m_strTemp.Compare("quot") == 0) Add('\"');
			else result = 0;

			m_strTemp.Empty();
			m_state = STATE_COLLECT_CHAR;
		} else {
			m_strTemp += ch;
			m_state = STATE_AMP_COLLECT;
		}
	}

	return result;
}

SAXParser::SAXBuffer::SAXBuffer(const SAXBuffer& buf)
{
	m_pBuffer = 0;
	m_dwLen = 0;
	m_dwPhysicalLen = 0;
	m_dwStartPos = 0;
	m_dwIncrease = 64;

	Add(buf.GetBuffer(), buf.GetLength());
}

const SAXParser::SAXBuffer& SAXParser::SAXBuffer::operator=(const SAXBuffer& buf)
{
	Clear();
	Add(buf.GetBuffer(), buf.GetLength());
	return *this;
}
