#include <stdio.h>
#include "CircularQueue.h"
#include "ListQueue.h"

using namespace cppalgo;

template CircularQueue<int>;
template ListQueue<char>;

void main(void)
{
	CircularQueue<int> q_int(5);
	q_int.Put(1);
	q_int.Put(2);
	q_int.Put(3);
	q_int.Put(4);

	try {
		q_int.Put(5);
	} catch (CircularQueue<int>::Exception) {
		printf("Queue overflow\n");
	}
	q_int.Get();
	q_int.Get();
	q_int.Put(5);
	q_int.Put(6);

	while (!q_int.IsEmpty())
	{
		int t = q_int.Get();
		printf("%d ", t);
	}
	printf("\n");

	ListQueue<char> q_char;
	q_char.Put('A');
	q_char.Put('B');
	q_char.Put('C');
	q_char.Put('D');

	while (!q_char.IsEmpty())
	{
		printf("%c ", q_char.Get());
	}
	printf("\n");

}