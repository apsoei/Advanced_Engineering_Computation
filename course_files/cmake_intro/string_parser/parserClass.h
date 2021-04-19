#ifndef PARSERCLASS_IS_INCLUDED
#define PARSERCLASS_IS_INCLUDED

class StringParser
{
protected:
	char *str;
	int *wordTop,*wordLength;
	int nw;

public:
	StringParser();
	~StringParser();
	void CleanUp(void);

	int Parse(char s[]);
protected:
	int Parse(int wordTop[],int wordLength[],int maxNumWord,char str[]);

public:
	int NW(void);
	void GetWord(char wd[],int maxn,int i);
};

#endif
