#include <iostream>
#include "yshash.h"
#include <stdlib.h>
#include <time.h>



template <>
struct ysHash<int>
{
	std::size_t operator()(const int &key) const
	{
		return key;
	}
};

int main(void)
{
	srand((int)time(NULL));
	ysHashSet <int> used;

	int numbers[20];
	for(int i=0; i<20; ++i)
	{
	RETRY:
		int r=rand()%20;
		if(used.end()!=used.find(r))
		{
			goto RETRY;
		}
		numbers[i]=r;
		used.insert(r);
	}

	if(used.end()==used.find(10))
	{
		return 1;
	}

	for(auto n : numbers)
	{
		std::cout << n << std::endl;
	}

	for(auto i : used)
	{
		std::cout << ">" << i << std::endl;
	}

	return 0;
}
