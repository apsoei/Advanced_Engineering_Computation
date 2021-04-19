#ifndef SHOOT_3_CLASS_H_IS_INCLUDED
#define SHOOT_3_CLASS_H_IS_INCLUDED

class GameMenu
{
public:
	int key;
	void RunOneStep(void);
};


class Missile
{
public:
	int x,y,state;
	void Initialize(void);
	void Launch(int x,int y);
	void Move(void);
	void Disappear(void);
	void Draw(void);

	// void Explode(void);
	// void Hit(void);
	// bool CheckHitTarget(class Target &target);
};

class Target
{
public:
	int x,y,w,h,v,state;
	void Initialize(void);
	void Move(void);
	bool CheckCollision(Missile m);
	void Disappear(void);
	void Draw(void);
};


class Player
{
public:
	int x,y;
	int n;

	void Initialize(int x0,int y0);
	void KeyPress(int key);
	void Draw(void);
};


const int nMissile=5;
const int nTarget=5;

const int STATE_INITIALIZING=0;
const int STATE_MENU=1;
const int STATE_GAME=2;

class ShootingGame
{
public:
	int state;


	GameMenu menu;

	bool termProgram;
	bool termGame;

	int nShot;
	Player player;
	Missile missile[nMissile];
	Target target[nTarget];

	void InitializeProgram(void);
	void InitializeGame(void);

	void RunOneStep(void);
	void RunOneStep_Menu(void);
	void RunOneStep_Game(void);
	bool MustTerminate(void);
};


#endif
