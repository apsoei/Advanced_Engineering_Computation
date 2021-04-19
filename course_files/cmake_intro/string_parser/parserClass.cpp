#include <stdio.h>
#include <string.h>
#include <math.h>
#include <ctype.h>

#include "parserClass.h"

static void GetWord(char wd[],char str[],int wordTop,int wordLength,int bufSize)
{
	int l=wordLength;
	if(bufSize<l)
	{
		l=bufSize;
	}
	strncpy(wd,str+wordTop,l);
	wd[l]=0;
}

StringParser::StringParser()
{
	str=nullptr;
	wordTop=nullptr;
	wordLength=nullptr;
	nw=0;
}
StringParser::~StringParser()
{
	CleanUp();
}
void StringParser::CleanUp(void)
{
	if(nullptr!=str)
	{
		delete [] str;
		str=nullptr;
	}
	if(nullptr!=wordTop)
	{
		delete [] wordTop;
		wordTop=nullptr;
	}
	if(nullptr!=wordLength)
	{
		delete [] wordLength;
		wordTop=nullptr;
	}
}

int StringParser::NW(void)
{
	return nw;
}

int StringParser::Parse(char s[])
{
	CleanUp();

	int n=strlen(s);
	str=new char [n+1];
	strcpy(str,s);

	wordTop=new int [1+n/2];
	wordLength=new int [1+n/2];
	nw=Parse(wordTop,wordLength,1+n/2,s);
	return nw;
}

int StringParser::Parse(int wordTop[],int wordLength[],int maxNumWord,char str[])
{
	int state=0;  // 0:Blank   1:Visible Letter
	int nw=0;
	for(int i=0; 0!=str[i]; ++i)
	{
		switch(state)
		{
		case 0:
			if(' '!=str[i] && isprint(str[i]))
			{
				if(nw<maxNumWord)
				{
					wordTop[nw]=i;
					wordLength[nw]=1;
				}
				else
				{
					goto LOOPOUT;
				}
				++nw;
				state=1;
			}
			else
			{
			}
			break;
		case 1:
			if(' '!=str[i] && isprint(str[i]))
			{
				wordLength[nw-1]++;
			}
			else
			{
				state=0;
			}
			break;
		}
	}
LOOPOUT:

	return nw;
}

void StringParser::GetWord(char wd[],int maxn,int idx)
{
	wd[0]=0;
	if(0<=idx && idx<nw)
	{
		for(int i=0; i<wordLength[idx] && i<maxn; ++i)
		{
			wd[i]=str[wordTop[idx]+i];
			wd[i+1]=0;
		}
	}
}

