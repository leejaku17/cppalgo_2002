#include <stdio.h>
#include "ArrayStack.h"
#include "ListStack.h"

using namespace cppalgo;

template ArrayStack<int>;
template ListStack<int>;

void main(void)
{
	ArrayStack<int> stack_int(5);
	stack_int.Push(5);
	stack_int.Push(4);
	stack_int.Push(3);
	stack_int.Push(2);
	stack_int.Push(1);

	int n = stack_int.GetTop();

	while (!stack_int.IsEmpty()) {
		printf("%d ", stack_int.Pop());
	}
	printf("\n");

	ListStack<char> stack_char;
	stack_char.Push('A');
	stack_char.Push('B');
	stack_char.Push('C');
	stack_char.Push('D');
	stack_char.Push('E');

	char c = stack_char.GetTop();

	while (!stack_char.IsEmpty()) {
		printf("%c ", stack_char.Pop());
	}
	printf("\n");

	try {
		stack_char.GetTop();
	} catch (ListStack<char>::Exception) {
		printf("Exception handled\n");
	}

}