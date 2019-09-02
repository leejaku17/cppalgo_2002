#ifndef _ParseTree_h
#define _ParseTree_h

#include "BinaryTree.h"
#include "../String/AString.h"

#pragma comment (lib, "../cppalgo/Release/cppalgo.lib")

using namespace cppalgo;
class ParseTree : public BinaryTree<String>
{
public:
	void BuildParseTree(const String& strPostfix);
	bool IsOperator(char c) { return (c == '+' || c == '-' || c == '*' || c == '/'); }
	void PreOrderTraverse(Node *pNode = 0);
	void PostOrderTraverse(Node *pNode = 0);
	void InOrderTraverse(Node *pNode = 0);
	void LevelOrderTraverse(Node *pNode = 0);
	void Visit(Node *pNode);
};

#endif