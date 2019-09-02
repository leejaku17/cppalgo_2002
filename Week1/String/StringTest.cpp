#include "AString.h"

using namespace cppalgo;

void main(void)
{
	// constructor test
	String str1;			// default constructor È£Ãâ 
	String str2("String Test");		// constructor
	String str3('A');				// constructor
	String str4 = str2;				// copy constructor
	String str5(156);				// constructor
	String str6(1.1);

	// assignment test
	str1 = str2 = str3;
	str1 += str5;

	str1 = "Assignment";		

	// operator test
	str1 = String("Assignment") + " and " + "Add String " + str5;
	bool f;
	f = (str1 == str5);
	f = (str1 != str5);
	f = (str1 == str1);		
	char ch = str1[5];

	// compare test
	str1 = "CompareNoCase";
	str2 = "COMPARENOCASE";

	int n;
	n = str1.CompareNoCase(str2);

	// basic functions
	str1.Empty();

	str1 = "CompareNoCase";
	n = str1.Find("No", 0);
	n = str1.FindNoCase("NO", 0);
	n = str1.ReverseFind('C');
	str1.Replace("e", "EEE");

	str1 = "0123456789";
	str2 = str1.Left(3);
	str2 = str1.Right(3);
	str2 = str1.Mid(3, 3);

	str1 = "    \ttrim   test     \r\n";
	str1.TrimLeft();
	str1.TrimRight();

	str1.Format("Format %s %d", "test", 555);

	str1 = "This is[Token]Test.";
	n = 0;
	while (n >= 0) {
		str2 = str1.GetToken(" []", n);
	}

	str2 = (const char*)str1;
}