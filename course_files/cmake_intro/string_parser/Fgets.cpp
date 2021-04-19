#include <stdio.h>
#include <ctype.h>

char *Fgets(char str[],int maxn,FILE *fp)
{
	if(nullptr!=fgets(str,maxn,fp))
	{
		int i;
		for(i=0; 0!=str[i]; ++i)
		{
		}
		for(i=i; 0<=i && 0==isprint(str[i]); --i)
		{
			str[i]=0;
		}
		return str;
	}
	return nullptr;
}

