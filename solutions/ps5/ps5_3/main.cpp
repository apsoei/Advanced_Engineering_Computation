#include <algorithm>

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "bintree.h"


int main(void)
{
	srand((int)time(nullptr));

	BinaryTree <int,int> tree;
	int max=0;

	for(int i=0; i<100; ++i)
	{
		int r=rand()%100;
		tree.Insert(r,0);
		max=std::max(r,max);
	}

	auto hd=tree.Last();
	if(tree.GetKey(hd)!=max)
	{
		fprintf(stderr,"Last() function doesn't work!\n");
		return 1;
	}

	while(true==hd.IsNotNull())
	{
		auto prv=tree.FindPrev(hd);
		if(prv.IsNotNull() && tree.GetKey(hd)<tree.GetKey(prv))
		{
			fprintf(stderr,"FindPrev() function doesn't work!\n");
			return 1;
		}
		hd=prv;
	}

	return 0;
}
