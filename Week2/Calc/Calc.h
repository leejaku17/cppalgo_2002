#ifndef _Calc_h
#define _Calc_h

#include "../String/AString.h"

namespace cppalgo
{
	class Calculator 
	{
	public:
		String ToPostfix1(const String& strInfix);
		String ToPostfix2(const String& strInfix);
		long CalcPostfix(const String& strPostfix);
		long CalcInfix(const String& strInfix);

	protected:
		// for ToPostfix2
		bool IsOperator(char c) { return (c == '+' || c == '-' || c == '*' || c == '/'); }
		long GetPrecedence(char c);
		
	};

};
#endif