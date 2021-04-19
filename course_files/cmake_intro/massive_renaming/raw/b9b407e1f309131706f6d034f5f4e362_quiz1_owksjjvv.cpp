#include <stdio.h>
#include <stdlib.h>
#include <time.h>



void CopyFile(const char ofn[],const char ifn[])
{
	FILE *ifp=fopen(ifn,"r");
	FILE *ofp=fopen(ofn,"w");
	if(nullptr!=ifp && nullptr!=ofp)
	{
		char str[256];
		while(nullptr!=fgets(str,255,ifp))
		{
			fputs(str,ofp);
		}
	}
	if(nullptr!=ifp)
	{
		fclose(ifp);
	}
	if(nullptr!=ofp)
	{
		fclose(ifp);
	}
}

int main(void)
{
	srand(time(nullptr));
	for(int i=0; i<64; ++i)
	{
		int ptr=0;
		char outFn[256];

		outFn[ptr++]='r';
		outFn[ptr++]='a';
		outFn[ptr++]='w';
		outFn[ptr++]='/';

		for(int j=0; j<32; ++j)
		{
			int r=rand()%16;
			if(r<10)
			{
				outFn[ptr++]='0'+r;
			}
			else
			{
				outFn[ptr++]='a'+r-10;
			}
		}
		outFn[ptr++]='_';
		if(rand()%2)
		{
			outFn[ptr++]='q';
		}
		else
		{
			outFn[ptr++]='Q';
		}
		outFn[ptr++]='u';
		outFn[ptr++]='i';
		outFn[ptr++]='z';
		outFn[ptr++]='1';
		if(rand()%2)
		{
			outFn[ptr++]='-';
		}
		else
		{
			outFn[ptr++]='_';
		}

		int nLetter=4+rand()%5;
		for(int j=0; j<nLetter; ++j)
		{
			int r=rand()%('z'-'a'+1);
			outFn[ptr++]='a'+r;
		}
		outFn[ptr++]='.';
		outFn[ptr++]='c';
		outFn[ptr++]='p';
		outFn[ptr++]='p';
		outFn[ptr++]=0;
		printf("%s\n",outFn);

		CopyFile(outFn,"genraw.cpp");
	}
	return 0;
}

