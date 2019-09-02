#include <stdio.h>
#include "ParseTree.h"
#include "../Stack/ListStack.h"
#include "../Queue/ListQueue.h"

using namespace cppalgo;

void ParseTree::BuildParseTree(const String& strPostfix)
{
	Node *pNode;
	int i = 0;
	ListStack<Node*> NodeStack;

	RemoveAll();

	while (strPostfix[i])
	{
		while (strPostfix[i] == ' ')	
			i++;  // 공백문자는 무시 

		pNode = new Node;

		if (IsOperator(strPostfix[i])) {
			pNode->data = strPostfix[i];
			i++;

			pNode->pRight = NodeStack.Pop();
			pNode->pLeft = NodeStack.Pop();
		} else {
			do {
				pNode->data += strPostfix[i];
				i++;
			} while (strPostfix[i] != ' ' && i < strPostfix.GetLength());

			pNode->pLeft = m_pNodeTail;
			pNode->pRight = m_pNodeTail;
		}

		NodeStack.Push(pNode);
	}

	// 완료되었음. 
	m_pNodeHead->pLeft = NodeStack.Pop();
}

void ParseTree::Visit(Node *pNode)
{
	printf("%s ", (const char*)pNode->data);
}

void ParseTree::PreOrderTraverse(Node *pNode)
{
	if (pNode == 0)
		pNode = m_pNodeHead->pLeft;

	if (pNode != m_pNodeTail)
	{
		Visit(pNode);
		PreOrderTraverse(pNode->pLeft);
		PreOrderTraverse(pNode->pRight);
	}
}

void ParseTree::PostOrderTraverse(Node *pNode)
{
	if (pNode == 0)
		pNode = m_pNodeHead->pLeft;

	if (pNode != m_pNodeTail)
	{
		PostOrderTraverse(pNode->pLeft);
		PostOrderTraverse(pNode->pRight);
		Visit(pNode);
	}
}

void ParseTree::InOrderTraverse(Node *pNode)
{
	if (pNode == 0)
		pNode = m_pNodeHead->pLeft;

	if (pNode != m_pNodeTail)
	{
		InOrderTraverse(pNode->pLeft);
		Visit(pNode);
		InOrderTraverse(pNode->pRight);
	}
}

void ParseTree::LevelOrderTraverse(Node *pNode)
{
	ListQueue<Node*> queue;
	
	if (pNode == 0)
		pNode = m_pNodeHead->pLeft;

	queue.Put(pNode);
	while (!queue.IsEmpty())
	{
		pNode = queue.Get();
		Visit(pNode);
		if (pNode->pLeft != m_pNodeTail)
			queue.Put(pNode->pLeft);
		if (pNode->pRight != m_pNodeTail)
			queue.Put(pNode->pRight);
	}
}
