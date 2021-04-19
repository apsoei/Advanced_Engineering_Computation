#include <iostream>
#include "yshash.h"
#include <stdlib.h>
#include <time.h>



#include <string>
template <>
struct ysHash<std::string>
{
	std::size_t operator()(const std::string &key) const
	{
		std::size_t code=0;
		unsigned int prime[4]={3,5,7,11};
		for(int i=0; i<key.size(); ++i)
		{
			code+=key[i]*prime[i%4];  // i%4=i&3
		}
		return code;
	}
};



bool TestFind(const ysHashTable <std::string,std::string> &table,std::string key)
{
	auto iter=table.find(key);
	if(iter!=table.end())
	{
		std::cout << "Found " << iter->first << " to " << iter->second << std::endl;
		return true;
	}
	else
	{
		std::cout << "Not Found" << std::endl;
		return false;
	}
}

int main(void)
{
	srand((int)time(NULL));
	ysHashTable <std::string,std::string> table;

	table.insert("A1","Skyraider");
	table.insert("F4","Phantom");
	table.insert("F5","Tiger");
	table.insert("F8","Crusader");
	table.insert("A10","Thunderbolt");

	TestFind(table,"A1");
	TestFind(table,"F5");
	TestFind(table,"F22");
	TestFind(table,"F15");

//	for(auto s : table)
//	{
//		std::cout << ">" << s.first << " " << s.second << std::endl;
//	}
	for(auto iter=table.begin(); iter!=table.end(); ++iter)
	{
		std::cout << ">" << iter->first << " " << iter->second << std::endl;
	}

	if(5!=table.size())
	{
		return 1;
	}

	return 0;
}
