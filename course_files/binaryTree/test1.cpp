#include <iostream>
#include <stdlib.h> // #include <cstdlib>
#include <time.h>

#include "ysbintree.h"



void Traverse(BinaryTree <int,int> &tree,BinaryTree <int,int>::NodeHandle ndHd)
{
	if(ndHd!=nullptr)
	{
		Traverse(tree,tree.Left(ndHd));  // Take care of left sub-tree,
		std::cout << tree.GetKey(ndHd) << std::endl; // Take care of itself,
		Traverse(tree,tree.Right(ndHd)); // Take care of right sub-tree.
	}
}

void Print(const BinaryTree <int,int> &tree)
{
	for(auto ndHd=tree.First(); ndHd!=nullptr; ndHd=tree.FindNext(ndHd))
	{
		std::cout << "> " << tree.GetKey(ndHd) << ":" << tree.GetValue(ndHd) << std::endl; // Take care of itself,
	}
}

int main(void)
{
	srand((int)time(nullptr));

	BinaryTree <int,int> tree,tree2;

	for(int i=0; i<20; ++i)
	{
		tree.Insert(rand()%20,0);
	}

	// Traverse(tree,tree.RootNode());
	Print(tree);

	return 0;
}
