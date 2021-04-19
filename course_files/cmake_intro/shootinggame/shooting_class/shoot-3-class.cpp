#include <stdlib.h>

#include "fssimplewindow.h"
#include "ysglfontdata.h"
#include "shoot-3-class.h"


void GameMenu::RunOneStep(void)
{
	key=0;

	FsPollDevice();
	key=FsInkey();

	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);

	glColor3ub(0,0,255);

	glRasterPos2d(100.0,100.0);
	YsGlDrawFontBitmap16x20("SHOOTING GAME");

	glRasterPos2d(100.0,120.0);
	YsGlDrawFontBitmap16x20("Press S to start");

	glRasterPos2d(100.0,140.0);
	YsGlDrawFontBitmap16x20("Press ESC to quit");

	FsSwapBuffers();
	FsSleep(25);
}


void Missile::Initialize(void)
{
	state=0;
}

void Missile::Launch(int x,int y)
{
	if(0==state)
	{
		state=1;
		this->x=x;
		this->y=y;
	}
}

void Missile::Move(void)
{
	if(1==state)
	{
		y-=10;
	}
}

void Missile::Disappear(void)
{
	state=0;
}

void Missile::Draw(void)
{
	glColor3ub(255,0,0);

	glBegin(GL_LINES);
	glVertex2i(x,y);
	glVertex2i(x,y+9);
	glEnd();
}




void Target::Initialize(void)
{
	state=1;
	x=0;
	y=50+rand()%100;
	w=80+rand()%10;
	h=20;
	v=20+rand()%10;
}

void Target::Move(void)
{
	x+=v;
	if(800<x)
	{
		x=0;
	}
}

bool Target::CheckCollision(Missile m)
{
	if(x<=m.x && m.x<x+w && y<=m.y && m.y<y+h)
	{
		return true;
	}
	return false;
}

void Target::Disappear(void)
{
	state=0;
}

void Target::Draw(void)
{
	glColor3ub(0,255,255);

	glBegin(GL_QUADS);
	glVertex2i(x  ,y);
	glVertex2i(x+w,y);
	glVertex2i(x+w,y+h);
	glVertex2i(x  ,y+h);
	glEnd();
}


void Player::Initialize(int x0,int y0)
{
	this->x=x0;
	this->y=y0;
	this->n=0;
}

void Player::KeyPress(int key)
{
	switch(key)
	{
	case FSKEY_LEFT:
		x-=10;
		break;
	case FSKEY_RIGHT:
		x+=10;
		break;
	}
}

void Player::Draw(void)
{
	glColor3ub(0,0,255);

	glBegin(GL_QUADS);

	glVertex2i(x-15,y);
	glVertex2i(x+14,y);
	glVertex2i(x+14,y-9);
	glVertex2i(x-15,y-9);

	glVertex2i(x-5,y-19);
	glVertex2i(x+5,y-19);
	glVertex2i(x+5,y);
	glVertex2i(x-5,y);

	glEnd();
}


void ShootingGame::InitializeProgram(void)
{
	state=STATE_MENU;
	termProgram=false;
}

void ShootingGame::InitializeGame(void)
{
	player.Initialize(400,550);

	for(auto &s : missile)
	{
		s.Initialize();  // s.state=0;
	}

	for(auto &t : target)
	{
		t.Initialize();
	}
}


void ShootingGame::RunOneStep(void)
{
	switch(state)
	{
	case STATE_INITIALIZING:
		InitializeProgram();
		break;
	case STATE_MENU:
		RunOneStep_Menu();
		break;
	case STATE_GAME:
		RunOneStep_Game();
		if(true==termGame)
		{
			state=STATE_MENU;
		}
		break;
	}
}

void ShootingGame::RunOneStep_Menu(void)
{
	menu.RunOneStep();
	if(menu.key==FSKEY_ESC)
	{
		termProgram=true;
	}
	else if(menu.key==FSKEY_S)
	{
		InitializeGame();
		state=STATE_GAME;
	}
}

void ShootingGame::RunOneStep_Game(void)
{
	FsPollDevice();

	auto key=FsInkey();
	player.KeyPress(key);
	switch(key)
	{
	case FSKEY_SPACE:
		for(auto &m : missile)
		{
			if(0==m.state)
			{
				player.n++;
				m.Launch(player.x,player.y);
				break;
			}
		}
		break;
	case FSKEY_ESC:
		termGame=true;
		break;
	}

	for(auto &m : missile)
	{
		if(1==m.state)
		{	
			m.Move();
			if(0>m.y)
			{
				m.Disappear();
			}
		}
	}
	for(auto &t : target)
	{
		if(1==t.state)
		{
			t.Move();
		}
	}

	for(auto &m : missile)
	{
		if(1==m.state)
		{
			for(auto &t : target)
			{
				if(1==t.state && true==t.CheckCollision(m))
				{
					t.Disappear();
					m.Disappear();
				}
			}
		}
	}


	int nAlive=0;
	for(auto t : target)
	{
		nAlive+=t.state;
	}
	if(0==nAlive)
	{
		termGame=true;
	}


	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
	for(auto m : missile)
	{
		if(1==m.state)
		{
			m.Draw();
		}
	}
	for(auto t : target)
	{
		if(1==t.state)
		{
			t.Draw();
		}
	}
	player.Draw();
	FsSwapBuffers();

	FsSleep(25);
}

bool ShootingGame::MustTerminate(void)
{
	return termProgram;
}


