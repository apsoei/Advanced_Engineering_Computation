#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(void)
{
	srand(time(nullptr));

	int r=1+rand()%10;

	int a;

	printf("Guess 1-10>");
	scanf("%d",&a);

	if(a==r)
	{
		printf("Right!\n");
	}
	else
	{
		printf("Wrong!  Answer was %d\n",r);
	}

	return 0;
}
