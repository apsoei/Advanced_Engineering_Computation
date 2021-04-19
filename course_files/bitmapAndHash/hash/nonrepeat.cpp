#include <iostream>
#include <unordered_set>
#include <stdlib.h>
#include <time.h>



int main(void)
{
	srand((int)time(NULL));
	std::unordered_set <int> used;

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

	for(auto n : numbers)
	{
		std::cout << n << std::endl;
	}

	return 0;
}
