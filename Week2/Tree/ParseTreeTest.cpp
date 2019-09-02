#include <stdio.h>
#include "BinaryTree.h"
#include "ParseTree.h"

using namespace cppalgo;

void main(void)
{
	ParseTree tree;
	String strPostfix = "A B + C D - * E / F G * +";

	tree.BuildParseTree(strPostfix);

	tree.PreOrderTraverse();
	printf("\n");
	tree.PostOrderTraverse();
	printf("\n");
	tree.InOrderTraverse();
	printf("\n");
	tree.LevelOrderTraverse();
	printf("\n");
}