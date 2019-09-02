#include <stdio.h>
#include "SAXParser.h"
#include "string.h"

using namespace cppalgo;

class TestSAXParser : public SAXParser
{
	virtual bool OnStartDocument() {
		printf("OnStartDocument\n");
		return true;
	}

	virtual bool OnEndDocument() {
		printf("OnEndDocument\n");
		return true;
	}

	virtual bool OnStartElement(const String& strTagName, const Attributes& Attr, const String& strTagHierachy) {
		printf("OnStartElement : <%s> %s\n", (const char*)strTagName, (const char*)strTagHierachy);

		printf("\t");		
		unsigned long i = 0;
		String strName, strValue;
		while (Attr.GetValue(i, strName, strValue)) {
			printf("%s=\'%s\' ", (const char*)strName, (const char*)strValue);
			i++;
		}
		printf("\n");
		return true;
	}

	virtual bool OnEndElement(const String& strTagName, const Attributes& Attr, const String& strTagHierachy, const String& strText) {
		printf("OnEndElement : <%s> %s\n", (const char*)strTagName, (const char*)strTagHierachy);

		printf("\t");		
		unsigned long i = 0;
		String strName, strValue;
		while (Attr.GetValue(i, strName, strValue)) {
			printf("%s=\'%s\' ", (const char*)strName, (const char*)strValue);
			i++;
		}
		printf("\n");

		printf("\t%s\n", (const char*)strText);

		return true;
	}
};

void main(int argc, char *argv[])
{
	const char *szTestXml = 
		"<?xml version='1.0'?>"
		"<Root>"
		"    <Tag1 func='space-non-preserve' name2=\"value2\">"
		"                         C++로 배우는                알고리즘              "
		"    </Tag1>"
		"    <Tag2 func='space-preserve' xml:space='preserve'>"
		"        Space    preserve   "
		"    </Tag2>"
		"    <Tag3 func='amp-encoding' test='&amp;&gt;&gl'>"
		"        <Tag31 func='inner'>"
		"            this is &lt;Jake&gt;&apos;s Job"
		"        </Tag31>"
		"    </Tag3>"
		"</Root>";

	TestSAXParser parser;
	parser.AddStream(szTestXml, strlen(szTestXml));
}