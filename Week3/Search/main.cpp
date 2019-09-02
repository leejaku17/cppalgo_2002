#include "ArraySeqMap.h"
#include "ListSeqMap.h"
#include "BinMap.h"
#include "ItpMap.h"
#include "BinTreeMap.h"
#include "HashMap.h"
#include "ChainMap.h"
#include "RadixTreeMap.h"
#include "RadixTrieMap.h"
#include "BTreeMap.h"
#include "RBTreeMap.h"

#include "../String/AString.h"
#include <stdio.h>

#pragma comment(lib, "../cppalgo/Release/cppalgo.lib")

using namespace cppalgo;

class PersonHash;

struct Person
{
	int m_id;
	String m_name;

	Person() : m_id(0) {}
	Person(int id, const String& name) : m_id(id), m_name(name) {}
	Person(const Person& p) { m_id = p.m_id; m_name = p.m_name; }

	Person operator=(const Person& p) { m_id = p.m_id; m_name = p.m_name; return *this; }
	bool operator==(const Person& p) const { return m_id == p.m_id; }
	bool operator>(const Person& p) const { return m_id > p.m_id; }
	// Radix Search를 위한 연산자 정의 
	unsigned long operator>>(const unsigned long i) const { return m_id >> i; }

	friend class PersonHash;
};

class PersonHash
{
public:
	unsigned long hash(const Person& p) const { return (unsigned long)p.m_id * 11; }  // 반드시 const function이어야 한다. 
};

template ArraySeqMap<Person>;
template ListSeqMap<Person>;
template BinMap<Person>;
template BinTreeMap<Person>;
template HashMap<Person, PersonHash>;
template RadixTreeMap<Person>;
template RadixTrieMap<Person>;
template BTreeMap<Person>;
template RBTreeMap<Person>;

void ArraySeqMapTest()
{
	printf("ArraySeqMapTest\n");
	ArraySeqMap<Person>	map(100);
	map.Insert(Person(5, "Jake"));
	map.Insert(Person(3, "Devil"));
	map.Insert(Person(2, "Slash"));
	map.Insert(Person(1, "Newmania"));
	map.Insert(Person(3, "Franken"));
	map.Insert(Person(6, "Stone"));
	map.Insert(Person(3, "Cookp"));

	// Find Test
	Person key;
	key.m_id = 1;
	Person value;
	if (map.Find(key, value))
		printf("\tTest(Find)  id=%d name=%s\n", key.m_id, (const char*)value.m_name);
	else
		printf("\tTest(Find) Error\n");

	key.m_id = 3;
	if (map.Find(key, value))
		printf("\tTest(Find)  id=%d name=%s\n", key.m_id, (const char*)value.m_name);
	else
		printf("\tTest(Find) Error\n");
	
	// FindFirst/FindNext test
	key.m_id = 3;
	ArraySeqMap<Person>::MapPos pos;
	if (map.FindFirst(key, value, pos))
	{
		do
		{
			printf("\tTest(FindFirst) id=%d name=%s\n", key.m_id, (const char*)value.m_name);
		}
		while (map.FindNext(value, pos));
	}
	else
		printf("\tTest(FindFirst) Error\n");

	// Remove Test
	key.m_id = 1;
	if (map.Remove(key))
		printf("\tTest(Remove) id=%d Success\n", key.m_id);
	else
		printf("\tTest(Remove) id=%d Failed\n", key.m_id);
	if (map.Find(key, value))
		printf("\tTest(Find) id=%d value=%s\n", key.m_id, (const char*)value.m_name);
	else
		printf("\tTest(Find) id=%d Failed\n", key.m_id);

	// FindFirst/FindNext test
	key.m_id = 3;
	if (map.FindFirst(key, value, pos))
	{
		do
		{
			printf("\tTest(FindFirst) id=%d name=%s\n", key.m_id, (const char*)value.m_name);
		}
		while (map.FindNext(value, pos));
	}
	else
		printf("\tTest(FindFirst) Error\n");
}

void ListSeqMapTest()
{
	printf("ListSeqMapTest\n");
	ListSeqMap<Person>	map;
	map.Insert(Person(5, "Jake"));
	map.Insert(Person(3, "Devil"));
	map.Insert(Person(2, "Slash"));
	map.Insert(Person(1, "Newmania"));
	map.Insert(Person(3, "Franken"));
	map.Insert(Person(6, "Stone"));
	map.Insert(Person(3, "Cookp"));

	// Find Test
	Person key;
	key.m_id = 1;
	Person value;
	if (map.Find(key, value))
		printf("\tTest(Find)  id=%d name=%s\n", key.m_id, (const char*)value.m_name);
	else
		printf("\tTest(Find) Error\n");
	
	// FindFirst/FindNext test
	key.m_id = 3;
	ListSeqMap<Person>::MapPos pos;
	if (map.FindFirst(key, value, pos))
	{
		do
		{
			printf("\tTest(FindFirst) id=%d name=%s\n", key.m_id, (const char*)value.m_name);
		}
		while (map.FindNext(value, pos));
	}
	else
		printf("\tTest(FindFirst) Error\n");

	// Remove Test
	key.m_id = 1;
	if (map.Remove(key))
		printf("\tTest(Remove) id=%d Success\n", key.m_id);
	else
		printf("\tTest(Remove) id=%d Failed\n", key.m_id);
	if (map.Find(key, value))
		printf("\tTest(Find) id=%d value=%s\n", key.m_id, (const char*)value.m_name);
	else
		printf("\tTest(Find) id=%d Failed\n", key.m_id);

	// FindFirst/FindNext test
	key.m_id = 3;
	if (map.FindFirst(key, value, pos))
	{
		do
		{
			printf("\tTest(FindFirst) id=%d name=%s\n", key.m_id, (const char*)value.m_name);
		}
		while (map.FindNext(value, pos));
	}
	else
		printf("\tTest(FindFirst) Error\n");
}

void BinMapTest()
{
	printf("BinMapTest\n");
	BinMap<Person>	map;
	map.Insert(Person(5, "Jake"));
	map.Insert(Person(3, "Devil"));
	map.Insert(Person(2, "Slash"));
	map.Insert(Person(1, "Newmania"));
	map.Insert(Person(3, "Franken"));
	map.Insert(Person(6, "Stone"));
	map.Insert(Person(3, "Cookp"));

	// Find Test
	Person key;
	key.m_id = 1;
	Person value;
	if (map.Find(key, value))
		printf("\tTest(Find)  id=%d name=%s\n", key.m_id, (const char*)value.m_name);
	else
		printf("\tTest(Find) Error\n");
	
	// FindFirst/FindNext test
	key.m_id = 3;
	BinMap<Person>::MapPos pos;
	if (map.FindFirst(key, value, pos))
	{
		do
		{
			printf("\tTest(FindFirst) id=%d name=%s\n", key.m_id, (const char*)value.m_name);
		}
		while (map.FindNext(value, pos));
	}
	else
		printf("\tTest(FindFirst) Error\n");

	// Remove Test
	key.m_id = 1;
	if (map.Remove(key))
		printf("\tTest(Remove) id=%d Success\n", key.m_id);
	else
		printf("\tTest(Remove) id=%d Failed\n", key.m_id);
	if (map.Find(key, value))
		printf("\tTest(Find) id=%d value=%s\n", key.m_id, (const char*)value.m_name);
	else
		printf("\tTest(Find) id=%d Failed\n", key.m_id);

	// FindFirst/FindNext test
	key.m_id = 3;
	if (map.FindFirst(key, value, pos))
	{
		do
		{
			printf("\tTest(FindFirst) id=%d name=%s\n", key.m_id, (const char*)value.m_name);
		}
		while (map.FindNext(value, pos));
	}
	else
		printf("\tTest(FindFirst) Error\n");
}

void ItpMapTest()
{
	printf("ItpMapTest\n");
	ItpMap<int>	map;
	map.Insert(5);
	map.Insert(3);
	map.Insert(2);
	map.Insert(1);
	map.Insert(3);
	map.Insert(6);
	map.Insert(3);

	// Find Test
	int key;
	key = 1;
	int value;
	if (map.Find(key, value))
		printf("\tTest(Find)  id=%d value=%d\n", key, value);
	else
		printf("\tTest(Find) Error\n");
	
	// FindFirst/FindNext test
	key = 3;
	ItpMap<int>::MapPos pos;
	if (map.FindFirst(key, value, pos))
	{
		do
		{
			printf("\tTest(FindFirst) id=%d value=%d\n", key, value);
		}
		while (map.FindNext(value, pos));
	}
	else
		printf("\tTest(FindFirst) Error\n");

	// Remove Test
	key = 1;
	if (map.Remove(key))
		printf("\tTest(Remove) id=%d Success\n", key);
	else
		printf("\tTest(Remove) id=%d Failed\n", key);
	if (map.Find(key, value))
		printf("\tTest(Find) id=%d value=%d\n", key, value);
	else
		printf("\tTest(Find) id=%d Failed\n", key);

	// FindFirst/FindNext test
	key = 3;
	if (map.FindFirst(key, value, pos))
	{
		do
		{
			printf("\tTest(FindFirst) id=%d value=%d\n", key, value);
		}
		while (map.FindNext(value, pos));
	}
	else
		printf("\tTest(FindFirst) Error\n");
}

void HashMapTest()
{
	printf("HashMapTest\n");
	HashMap<Person, PersonHash>	map(PersonHash(), 10);
	map.Insert(Person(5, "Jake"));
	map.Insert(Person(3, "Devil"));
	map.Insert(Person(2, "Slash"));
	map.Insert(Person(1, "Newmania"));
	map.Insert(Person(3, "Franken"));
	map.Insert(Person(6, "Stone"));
	map.Insert(Person(3, "Cookp"));

	// Find Test
	Person key;
	key.m_id = 1;
	Person value;
	if (map.Find(key, value))
		printf("\tTest(Find)  id=%d name=%s\n", key.m_id, (const char*)value.m_name);
	else
		printf("\tTest(Find) Error\n");

	key.m_id = 3;
	if (map.Find(key, value))
		printf("\tTest(Find)  id=%d name=%s\n", key.m_id, (const char*)value.m_name);
	else
		printf("\tTest(Find) Error\n");
	
	// FindFirst/FindNext test
	key.m_id = 3;
	HashMap<Person, PersonHash>::MapPos pos;
	if (map.FindFirst(key, value, pos))
	{
		do
		{
			printf("\tTest(FindFirst) id=%d name=%s\n", key.m_id, (const char*)value.m_name);
		}
		while (map.FindNext(value, pos));
	}
	else
		printf("\tTest(FindFirst) Error\n");

	// Remove Test
	key.m_id = 1;
	if (map.Remove(key))
		printf("\tTest(Remove) id=%d Success\n", key.m_id);
	else
		printf("\tTest(Remove) id=%d Failed\n", key.m_id);
	if (map.Find(key, value))
		printf("\tTest(Find) id=%d value=%s\n", key.m_id, (const char*)value.m_name);
	else
		printf("\tTest(Find) id=%d Failed\n", key.m_id);

	// FindFirst/FindNext test
	key.m_id = 3;
	if (map.FindFirst(key, value, pos))
	{
		do
		{
			printf("\tTest(FindFirst) id=%d name=%s\n", key.m_id, (const char*)value.m_name);
		}
		while (map.FindNext(value, pos));
	}
	else
		printf("\tTest(FindFirst) Error\n");
}

void RadixTreeMapTest()
{
	printf("RadixTreeMapTest\n");
	RadixTreeMap<Person> map;
	map.Insert(Person(5, "Jake"));
	map.Insert(Person(3, "Devil"));
	map.Insert(Person(2, "Slash"));
	map.Insert(Person(1, "Newmania"));
	map.Insert(Person(3, "Franken"));
	map.Insert(Person(6, "Stone"));
	map.Insert(Person(3, "Cookp"));

	// Find Test
	Person key;
	key.m_id = 1;
	Person value;
	if (map.Find(key, value))
		printf("\tTest(Find)  id=%d name=%s\n", key.m_id, (const char*)value.m_name);
	else
		printf("\tTest(Find) Error\n");

	key.m_id = 3;
	if (map.Find(key, value))
		printf("\tTest(Find)  id=%d name=%s\n", key.m_id, (const char*)value.m_name);
	else
		printf("\tTest(Find) Error\n");

	key.m_id = 5;
	if (map.Find(key, value))
		printf("\tTest(Find)  id=%d name=%s\n", key.m_id, (const char*)value.m_name);
	else
		printf("\tTest(Find) Error\n");
	
	// FindFirst/FindNext test
	/*
	key.m_id = 3;
	RadixTreeMap<Person, PersonHash>::MapPos pos;
	if (map.FindFirst(key, value, pos))
	{
		do
		{
			printf("\tTest(FindFirst) id=%d name=%s\n", key.m_id, (const char*)value.m_name);
		}
		while (map.FindNext(value, pos));
	}
	else
		printf("\tTest(FindFirst) Error\n");
	*/
	// Remove Test
	key.m_id = 1;
	if (map.Remove(key))
		printf("\tTest(Remove) id=%d Success\n", key.m_id);
	else
		printf("\tTest(Remove) id=%d Failed\n", key.m_id);
	if (map.Find(key, value))
		printf("\tTest(Find) id=%d value=%s\n", key.m_id, (const char*)value.m_name);
	else
		printf("\tTest(Find) id=%d Failed\n", key.m_id);

	/*
	// FindFirst/FindNext test
	key.m_id = 3;
	if (map.FindFirst(key, value, pos))
	{
		do
		{
			printf("\tTest(FindFirst) id=%d name=%s\n", key.m_id, (const char*)value.m_name);
		}
		while (map.FindNext(value, pos));
	}
	else
		printf("\tTest(FindFirst) Error\n");
		*/
}

void RadixTrieMapTest()
{
	printf("RadixTrieMapTest\n");
	RadixTrieMap<Person> map;
	map.Insert(Person(5, "Jake"));
	map.Insert(Person(3, "Devil"));
	map.Insert(Person(2, "Slash"));
	map.Insert(Person(1, "Newmania"));
	map.Insert(Person(3, "Franken"));
	map.Insert(Person(6, "Stone"));
	map.Insert(Person(3, "Cookp"));

	// Find Test
	Person key;
	key.m_id = 1;
	Person value;
	if (map.Find(key, value))
		printf("\tTest(Find)  id=%d name=%s\n", key.m_id, (const char*)value.m_name);
	else
		printf("\tTest(Find) Error\n");

	key.m_id = 3;
	if (map.Find(key, value))
		printf("\tTest(Find)  id=%d name=%s\n", key.m_id, (const char*)value.m_name);
	else
		printf("\tTest(Find) Error\n");

	key.m_id = 5;
	if (map.Find(key, value))
		printf("\tTest(Find)  id=%d name=%s\n", key.m_id, (const char*)value.m_name);
	else
		printf("\tTest(Find) Error\n");
	
	// FindFirst/FindNext test
	/*
	key.m_id = 3;
	RadixTrieMap<Person, PersonHash>::MapPos pos;
	if (map.FindFirst(key, value, pos))
	{
		do
		{
			printf("\tTest(FindFirst) id=%d name=%s\n", key.m_id, (const char*)value.m_name);
		}
		while (map.FindNext(value, pos));
	}
	else
		printf("\tTest(FindFirst) Error\n");
	*/
	// Remove Test
	key.m_id = 1;
	if (map.Remove(key))
		printf("\tTest(Remove) id=%d Success\n", key.m_id);
	else
		printf("\tTest(Remove) id=%d Failed\n", key.m_id);
	if (map.Find(key, value))
		printf("\tTest(Find) id=%d value=%s\n", key.m_id, (const char*)value.m_name);
	else
		printf("\tTest(Find) id=%d Failed\n", key.m_id);

	/*
	// FindFirst/FindNext test
	key.m_id = 3;
	if (map.FindFirst(key, value, pos))
	{
		do
		{
			printf("\tTest(FindFirst) id=%d name=%s\n", key.m_id, (const char*)value.m_name);
		}
		while (map.FindNext(value, pos));
	}
	else
		printf("\tTest(FindFirst) Error\n");
		*/
}

void BTreeMapTest()
{
	printf("BTreeMapTest\n");
	BTreeMap<Person> map(3);
	map.Insert(Person(5, "Jake"));
	map.Insert(Person(3, "Devil"));
	map.Insert(Person(2, "Slash"));
	map.Insert(Person(1, "Newmania"));
	map.Insert(Person(3, "Franken"));
	map.Insert(Person(6, "Stone"));
	map.Insert(Person(3, "Cookp"));

	// Find Test
	Person key;
	key.m_id = 1;
	Person value;
	if (map.Find(key, value))
		printf("\tTest(Find)  id=%d name=%s\n", key.m_id, (const char*)value.m_name);
	else
		printf("\tTest(Find) Error\n");

	key.m_id = 3;
	if (map.Find(key, value))
		printf("\tTest(Find)  id=%d name=%s\n", key.m_id, (const char*)value.m_name);
	else
		printf("\tTest(Find) Error\n");

	key.m_id = 5;
	if (map.Find(key, value))
		printf("\tTest(Find)  id=%d name=%s\n", key.m_id, (const char*)value.m_name);
	else
		printf("\tTest(Find) Error\n");
	
	// FindFirst/FindNext test
	/*
	key.m_id = 3;
	BTreeMap<Person, PersonHash>::MapPos pos;
	if (map.FindFirst(key, value, pos))
	{
		do
		{
			printf("\tTest(FindFirst) id=%d name=%s\n", key.m_id, (const char*)value.m_name);
		}
		while (map.FindNext(value, pos));
	}
	else
		printf("\tTest(FindFirst) Error\n");
	*/
	// Remove Test
	key.m_id = 1;
	if (map.Remove(key))
		printf("\tTest(Remove) id=%d Success\n", key.m_id);
	else
		printf("\tTest(Remove) id=%d Failed\n", key.m_id);
	if (map.Find(key, value))
		printf("\tTest(Find) id=%d value=%s\n", key.m_id, (const char*)value.m_name);
	else
		printf("\tTest(Find) id=%d Failed\n", key.m_id);

	/*
	// FindFirst/FindNext test
	key.m_id = 3;
	if (map.FindFirst(key, value, pos))
	{
		do
		{
			printf("\tTest(FindFirst) id=%d name=%s\n", key.m_id, (const char*)value.m_name);
		}
		while (map.FindNext(value, pos));
	}
	else
		printf("\tTest(FindFirst) Error\n");
		*/
}

void main(void)
{
	ArraySeqMapTest();
	ListSeqMapTest();	
	BinMapTest();
	ItpMapTest();
	HashMapTest();
	RadixTreeMapTest();
	RadixTrieMapTest();
	BTreeMapTest();
}
