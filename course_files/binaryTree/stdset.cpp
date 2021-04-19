#include <iostream>
#include <set>
#include <stdlib.h> // #include <cstdlib>

int main(void)
{
	std::set <int> s;
	for(int i=0; i<20; ++i)
	{
		s.insert(rand()%20);
	}

	std::cout << "Size=" << s.size() << std::endl;
	for(auto i : s)
	{
		std::cout << i << std::endl;
	}

	return 0;
}
