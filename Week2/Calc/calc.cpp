#include "Calc.h"
#include "../Stack/ListStack.h"

#pragma comment (lib, "../cppalgo/release/cppalgo.lib")

using namespace cppalgo;

String Calculator::ToPostfix1(const String& strInfix)
{
	String strPostfix;
	ListStack<char> stack;
	char c;
	int i = 0;

	while (strInfix[i])
	{
		c = strInfix[i];
		if (c == ')')		// ')'를 만나면 연산자를 Pop한다
		{
			strPostfix += stack.Pop();
			strPostfix += ' ';
			i++;
		} 
		else if (String(c).FindOneOf("+-*/") == 0)   // 연산자이면 Push한다 
		{	
			stack.Push(c);
			i++;
		}
		else if (c >= '0' && c <= '9')  // 숫자는 연속으로 읽어 그대로 복사 
		{
			do 
			{
				strPostfix += c;
				i++;
				c = strInfix[i];
			} while (c >= '0' && c <= '9');

			strPostfix += ' ';
		}
		else
		{
			i++;
		}
	}

	return strPostfix;
}

String Calculator::ToPostfix2(const String& strInfix)
{
	String strPostfix;
	ListStack<char> stack;
	char c;
	int i = 0;

	while (strInfix[i])
	{
		c = strInfix[i];
		if (c == '(')   // (를 만나면 Push
		{
			stack.Push(c);
			i++;
		}
		else if (c == ')')  // )를 만나면 (가 나올때까지 Pop
		{
			while (!stack.IsEmpty() && stack.GetTop() != '(')
			{
				strPostfix += stack.Pop();
				strPostfix += ' ';
			}
			stack.Pop();
			i++;
		}
		else if (IsOperator(c))  // 연산자이면 
		{
			while (!stack.IsEmpty() && GetPrecedence(stack.GetTop()) >= GetPrecedence(c))
			{	// 우선순위가 높은 연산자들을 모두 Pop
				strPostfix += stack.Pop();
				strPostfix += ' ';
			}
			stack.Push(c);
			i++;
		}
		else if (c >= '0' && c <= '9')
		{	// 피연산자는 그냥 출력 
			do
			{
				strPostfix += c;
				c = strInfix[++i];
			} while (c >= '0' && c <= '9');
			strPostfix += ' ';
		}
		else 
		{
			i++;
		}
	}
	while (!stack.IsEmpty())
	{
		strPostfix += stack.Pop();
		strPostfix += ' ';
	}

	return strPostfix;
}

long Calculator::CalcPostfix(const String& strPostfix)
{
	long n;
	ListStack<long> stack;
	int i = 0;
	char c;
	while (strPostfix[i])
	{
		c = strPostfix[i];
		if (c >= '0' && c <= '9')
		{
			n = 0;
			do
			{
				n = n*10 + c - '0';
				c = strPostfix[++i];
			} while (c >= '0' && c <= '9');
			stack.Push(n);
		}
		else if (c == '+')
		{
			stack.Push(stack.Pop() + stack.Pop());
			i++;
		} 
		else if (c == '*')
		{
			stack.Push(stack.Pop() * stack.Pop());
			i++;
		}
		else if (c == '-')
		{
			n = stack.Pop();
			stack.Push(stack.Pop() - n);
			i++;
		}
		else if (c == '/')
		{
			n = stack.Pop();
			stack.Push(stack.Pop() / n);
			i++;
		}
		else
		{
			i++;
		}
	}
	return stack.Pop();
}

long Calculator::CalcInfix(const String& strInfix)
{
	String strPostfix = ToPostfix2(strInfix);
	return CalcPostfix(strPostfix);
}

long Calculator::GetPrecedence(char c)
{
	if (c == '(') return 0;
	if (c == '+' || c == '-') return 1;
	if (c == '*' || c == '/') return 2;
	
	return 3;
}