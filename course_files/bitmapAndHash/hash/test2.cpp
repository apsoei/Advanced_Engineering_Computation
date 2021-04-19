#include <iostream>
#include <string>
#include "yshash.h"
#include <stdlib.h>
#include <time.h>



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

int main(void)
{
	srand((int)time(NULL));
	ysHashSet <std::string> used;

	used.insert("Skyraider");
	used.insert("Phantom");
	used.insert("Tiger");
	used.insert("Crusader");
	used.insert("Thunderbolt");

	std::cout << (used.find("Eagle")!=used.end()) << std::endl;
	std::cout << (used.find("Tomcat")!=used.end()) << std::endl;
	std::cout << (used.find("Phantom")!=used.end()) << std::endl;
	std::cout << (used.find("Tiger")!=used.end()) << std::endl;
	std::cout << (used.find("Thunderbolt")!=used.end()) << std::endl;

	for(auto i : used)
	{
		std::cout << ">" << i << std::endl;
	}

	return 0;
}
