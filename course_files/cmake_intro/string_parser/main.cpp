#include <stdio.h>

#include "Fgets.h"
#include "parserClass.h"

int main(void)
{
	printf("Enter a sentence:");

	char str[256];
	Fgets(str,255,stdin);

	StringParser parser;
	parser.Parse(str);

	for(int i=0; i<parser.NW(); ++i)
	{
		char wd[256];
		parser.GetWord(wd,255,i);
		printf(" [%d] %s\n",i,wd);
	}

	return 0;
}

