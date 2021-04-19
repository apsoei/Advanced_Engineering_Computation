#include <iostream>
#include <string>
#include <unordered_set>



int main(void)
{
	std::unordered_set <std::string> set;
	set.insert("Carnegie");
	set.insert("Mellon");
	set.insert("University");

	for(auto s : set)
	{
		std::cout << s << std::endl;
	}


	std::hash <std::string> func;
	std::cout << func("ABC") << std::endl;

	return 0;
}
