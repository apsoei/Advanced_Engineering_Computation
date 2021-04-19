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
	int i=1;
	for(auto ndHd=tree.First(); ndHd!=nullptr; ndHd=tree.FindNext(ndHd))
	{
		std::cout << i << "> " << tree.GetKey(ndHd) << ":" << tree.GetValue(ndHd) << std::endl; // Take care of itself,
		++i;
	}
}

int main(void)
{
	srand((int)time(nullptr));

	BinaryTree <int,int> tree;

	for(int i=0; i<20; ++i)
	{
		tree.Insert(rand()%20,0);
	}

	auto ndHd=tree.First();
	int nRemain=0;
	while(ndHd!=nullptr)
	{
		auto nextNdHd=tree.FindNext(ndHd);
		if(0!=tree.GetKey(ndHd)%2)
		{
			std::cout << "Deleting " << tree.GetKey(ndHd) << std::endl;
			tree.Delete(ndHd);
		}
		else
		{
			std::cout << "Not Deleting " << tree.GetKey(ndHd) << std::endl;
			++nRemain;
		}
		ndHd=nextNdHd;
	}

	std::cout << nRemain << " remaining." << std::endl;

	// Traverse(tree,tree.RootNode());
	Print(tree);

	return 0;
}
