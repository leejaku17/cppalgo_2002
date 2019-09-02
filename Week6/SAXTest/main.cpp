#include <stdio.h>
#include "../SList/DList.h"
#include "../String/AString.h"
#include "../SAXParser/SAXParser.h"

#import "msxml.dll"		// for DOM Parser

#pragma comment(lib, "../cppalgo/Release/cppalgo.lib")

using namespace cppalgo;

void ReadXML_DOM(const char* xml)
{
	/*
	String strXml = xml;
	// loadXML은 <? ?> 태그를 처리하지 못하기 때문에 제거해야 한다. 
	int index = strXml.Find("?>");
	if (index > 0) strXml = strXml.Mid(index + 2);
	*/

	MSXML::IXMLDOMDocumentPtr spXmlDoc;
	HRESULT hr;

	hr = spXmlDoc.CreateInstance("Microsoft.XMLDOM");
	if (FAILED(hr)) return;

	spXmlDoc->async = false;	// synchronous read
	spXmlDoc->load(xml);

	MSXML::IXMLDOMNodeListPtr spRecords;
	spRecords = spXmlDoc->getElementsByTagName("Record");
	
	for (int i = 0; i < spRecords->length; i++) {
		MSXML::IXMLDOMNodePtr spRecord;
		spRecord = spRecords->item[i];
		String strType = (const char*)spRecord->attributes->getNamedItem("type")->text;
		String strName = (const char*)spRecord->selectSingleNode("Person")->attributes->getNamedItem("name")->text;
		String strAge = (const char*)spRecord->selectSingleNode("Person")->attributes->getNamedItem("age")->text;
		String strProfile = (const char*)spRecord->selectSingleNode("Profile")->text;

		printf("%dst Record\n", i);
		printf("\tType = %s\n", (const char*)strType);
		printf("\tName = %s\n", (const char*)strName);
		printf("\tAge = %s\n", (const char*)strAge);
		printf("\tProfile = %s\n", (const char*)strProfile);
	}
}

struct Record
{
	String strType;
	String strName;
	long nAge;
	String strProfile;
};

class RecordParser : public SAXParser
{
public:
	void ClearRecord() 
	{ 
		m_record.strType.Empty(); m_record.strName.Empty(); m_record.strProfile.Empty();
		m_record.nAge = 0;
	}

	bool OnStartDocument() { return true; }
	bool OnEndDocument() { return true; }
	bool OnStartElement(const String& strTagName, const Attributes& Attr, const String& strTagHierachy)
	{
		if (strTagName.Compare("Record") == 0) ClearRecord();	
		return true;
	}
	bool OnEndElement(const String& strTagName, const Attributes& Attr, const String& strTagHierachy, const String& strText)
	{
		if (strTagName.Compare("Person") == 0) {
			Attr.GetValue("name", m_record.strName);
			String strAge;
			Attr.GetValue("age", strAge);
			m_record.nAge = atoi(strAge);
		} else if (strTagName.Compare("Profile") == 0) {
			m_record.strProfile = strText;
		} else if (strTagName.Compare("Record") == 0) {
			Attr.GetValue("type", m_record.strType);	// return값 체크 
			m_listRecords.AddTail(m_record);
		}
		return true;
	}

	DoubleList<Record> m_listRecords;
	Record m_record;
};

void ReadXML_SAX(const char *xml)
{
	RecordParser sink;
	sink.AddStream(xml, strlen(xml));

	POS pos = sink.m_listRecords.GetHeadPosition();
	int i = 0;
	while (pos) {
		Record &r = sink.m_listRecords.GetNext(pos);
		printf("Record %d\n", i);
		printf("\tType = %s\n", (const char*)r.strType);
		printf("\tName = %s\n", (const char*)r.strName);
		printf("\tAge = %d\n", r.nAge);
		printf("\tProfile = %s\n", (const char*)r.strProfile);
		i++;
	}
}

void main(int argc, char *argv[])
{
	if (argc < 2) {
		printf("Usage : SAXTest [xml file name]\n");
		return;
	}

	FILE *fp = 0;
	fp = fopen(argv[1], "rb");
	fseek(fp, 0, SEEK_END);
	int len = ftell(fp);
	fseek(fp, 0, SEEK_SET);

	char *pxml = new char[len + 1];
	fread(pxml, 1, len, fp);
	pxml[len] = 0;

	CoInitialize(NULL);

	ReadXML_DOM(argv[1]);

	CoUninitialize();

	ReadXML_SAX(pxml);


	fclose(fp);




	delete [] pxml;
}