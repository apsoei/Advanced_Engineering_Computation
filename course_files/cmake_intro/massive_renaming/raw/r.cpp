#include <iostream>
#include <string>
#include <stdlib.h>



int main(void)
{
	while(true!=std::cin.eof())
	{
		std::string fName,newFName;
		std::getline(std::cin,fName);

		int state=0;
		for(auto c : fName)
		{
			if(0==state)
			{
				if('_'==c)
				{
					state=1;
				}
			}
			else
			{
				if('-'==c)
				{
					c='_';
				}
				newFName.push_back(c);
			}
		}

		if(newFName[0]=='q')
		{
			newFName[0]='Q';
		}

		std::cout << fName << std::endl;
		std::cout << newFName << std::endl;

		rename(fName.c_str(),newFName.c_str());
	}
	return 0;
}
