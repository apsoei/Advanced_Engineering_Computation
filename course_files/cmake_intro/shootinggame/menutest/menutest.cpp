#include <stdio.h>
#include "fssimplewindow.h"

#include "shoot-3-class.h"

int main(void)
{
	FsOpenWindow(0,0,800,600,1);

	GameMenu menu;
	for(;;)
	{
		menu.RunOneStep();

		if(menu.key==FSKEY_S)
		{
			printf("Start\n");
		}
		else if(menu.key==FSKEY_ESC)
		{
			printf("Quit\n");
			break;
		}
	}

	return 0;
}
