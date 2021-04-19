#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "fssimplewindow.h"

#include "shoot-3-class.h"



int main(void)
{
	FsOpenWindow(0,0,800,600,1);
	srand((int)time(NULL));

	ShootingGame game;
	game.state=STATE_INITIALIZING;

	while(true!=game.MustTerminate())
	{
		game.RunOneStep();
	}

	return 0;
}



