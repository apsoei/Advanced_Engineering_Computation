#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <string.h>

#include "fssimplewindow.h"

void DrawTarget(int x,int y,int sizeX,int sizeY)
{
	glColor3ub(0,255,255);
	glBegin(GL_QUADS);
	glVertex2i(x       ,y);
	glVertex2i(x+sizeX,y);
	glVertex2i(x+sizeX,y+sizeY);
	glVertex2i(x      ,y+sizeY);
	glEnd();
}

void MoveTarget(int &x,int &y,int scrnSizeX,int scrnSizeY)
{
	x+=20;
	if(x>scrnSizeX)
	{
		x=0;
	}
}

int CheckHitTarget(int missileX,int missileY,int targetX,int targetY,int targetSizeX,int targetSizeY)
{
	int relativeX,relativeY;
	relativeX=missileX-targetX;
	relativeY=missileY-targetY;
	if(0<=relativeX && relativeX<targetSizeX && 0<=relativeY && relativeY<targetSizeY)
	{
		return 1;
	}
	else
	{
		return 0;
	}
}

void DrawPlayer(int x,int y)
{
	glColor3ub(0,0,255);
	glBegin(GL_QUADS);
	glVertex2i(x-5,y-19);
	glVertex2i(x+4,y-19);
	glVertex2i(x+4,y   );
	glVertex2i(x-5,y   );

	glVertex2i(x-15,y-9);
	glVertex2i(x+14,y-9);
	glVertex2i(x+14,y  );
	glVertex2i(x-15,y  );
	glEnd();
}

class ApplicationMain
{
public:
    // State variables
	int terminate=0,playerX=400,playerY=580;
	int missile=0,missileX=0,missileY=0,nShot=0;
	int targetX=0,targetY=100,targetSizeX=100,targetSizeY=20;

	bool MustTerminate(void) const
    {
		return 0!=terminate;
	}
    void RunOneStep(void)
    {
		FsPollDevice();
		int key=FsInkey();

		switch(key)
		{
		case FSKEY_ESC:
			terminate=1;
			break;
		case FSKEY_LEFT:
			playerX-=10;
			break;
		case FSKEY_RIGHT:
			playerX+=10;
			break;
		case FSKEY_SPACE:
			if(0==missile)
			{
				missile=1;
				missileX=playerX;
				missileY=playerY;
				nShot++;
			}
			break;
		}

		if(missile!=0)
		{
			missileY-=15;
			if(missileY<0)
			{
				missile=0;
			}
		}

		MoveTarget(targetX,targetY,800,600);

		if(CheckHitTarget(missileX,missileY,targetX,targetY,targetSizeX,targetSizeY)==1)
		{
			printf("Hit!\n");
			printf("You shot %d missiles to shoot it down.\n",nShot);
			terminate=1;
		}

		FsSleep(20);
	}
    void Draw(void) const
    {
		glClear(GL_DEPTH_BUFFER_BIT|GL_COLOR_BUFFER_BIT);
		DrawPlayer(playerX,playerY);

		if(missile!=0)
		{
			glColor3ub(255,0,0);
			glBegin(GL_LINES);
			glVertex2i(missileX,missileY);
			glVertex2i(missileX,missileY+14);
			glEnd();
		}

		DrawTarget(targetX,targetY,targetSizeX,targetSizeY);

		FsSwapBuffers();
	}
};
int main(void)
{
    ApplicationMain app;
	FsOpenWindow(16,16,800,600,1);
    while(true!=app.MustTerminate())
    {
        app.RunOneStep();
        app.Draw();
    }
    return 0;
}
