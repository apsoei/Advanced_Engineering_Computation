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
	ysHashTable <int,int> table;
	for(int i=0; i<10; ++i)
	{
		table.insert(i,i*100);
	}

	for(int i=0; i<20; ++i)
	{
		auto iter=table.find(i);
		if(iter!=table.end())
		{
			std::cout << "Found " << iter->first << " to " << iter->second << std::endl;
		}
		else
		{
			std::cout << "Not Found" << std::endl;
		}
	}

	for(auto iter=table.begin(); iter!=table.end(); ++iter)
	{
		std::cout << ">" << iter->first << " " << iter->second << std::endl;
	}

	return 0;
}
