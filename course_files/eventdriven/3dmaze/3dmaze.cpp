#include <stdio.h>
#include <math.h>
#include <vector>
#include <iostream>

#include "mmlplayer.h"
#include "yssimplesound.h"

#include "fssimplewindow.h"

const double YsPi=3.1415927;

void DrawCube(double x0,double y0,double z0,double x1,double y1,double z1)
{
	glBegin(GL_QUADS);

	glColor3ub(255,0,0);
	glVertex3d(x0,y0,z0);
	glVertex3d(x1,y0,z0);
	glVertex3d(x1,y1,z0);
	glVertex3d(x0,y1,z0);

	glVertex3d(x0,y0,z1);
	glVertex3d(x1,y0,z1);
	glVertex3d(x1,y1,z1);
	glVertex3d(x0,y1,z1);

	glColor3ub(0,255,0);
	glVertex3d(x0,y0,z0);
	glVertex3d(x1,y0,z0);
	glVertex3d(x1,y0,z1);
	glVertex3d(x0,y0,z1);
                      
	glVertex3d(x0,y1,z0);
	glVertex3d(x1,y1,z0);
	glVertex3d(x1,y1,z1);
	glVertex3d(x0,y1,z1);

	glColor3ub(0,0,255);
	glVertex3d(x0,y0,z0);
	glVertex3d(x0,y1,z0);
	glVertex3d(x0,y1,z1);
	glVertex3d(x0,y0,z1);
                      
	glVertex3d(x1,y0,z0);
	glVertex3d(x1,y1,z0);
	glVertex3d(x1,y1,z1);
	glVertex3d(x1,y0,z1);

	glEnd();
}

void DrawFloor(double x0,double z0,double x1,double z1,double y0,int r,int g,int b)
{
	glColor3ub(r,g,b);

	glBegin(GL_QUADS);

	glVertex3d(x0,y0,z0);
	glVertex3d(x1,y0,z0);
	glVertex3d(x1,y0,z1);
	glVertex3d(x0,y0,z1);

	glEnd();
}

void DrawMaze(int nx,int nz,const char wall[],double d)
{
	for(int z=0; z<nz; ++z)
	{
		for(int x=0; x<nx; ++x)
		{
			auto c=wall[z*nx+x];
			double x0=(double)x*d;
			double y0=0.0;
			double z0=(double)z*d;
			double x1=(double)x*d+d;
			double y1=d;
			double z1=(double)z*d+d;

			if('X'==c)
			{
				DrawCube(x0,y0,z0,x1,y1,z1);
			}
			else if('G'==c)
			{
				DrawFloor(x0,z0,x1,z1,y0,255,255,0);
			}
			else if('S'==c)
			{
				DrawFloor(x0,z0,x1,z1,y0,0,255,255);
			}
		}
	}
}

void ResetViewPoint(double &xx,double &zz,int nx,int nz,const char wall[],double d)
{
	for(int z=0; z<nz; ++z)
	{
		for(int x=0; x<nx; ++x)
		{
			auto c=wall[z*nx+x];
			if('S'==c)
			{
				xx=(double)x*d+d/2.0;
				zz=(double)z*d+d/2.0;
			}
		}
	}
}

int GetBlock(int nx,int nz,const char wall[],double d,double x,double z)
{
	const int bx=(int)(x/d);
	const int bz=(int)(z/d);
	if(0<=bx && bx<nx && 0<=bz && bz<nz)
	{
		return wall[bz*nx+bx];
	}
	return 0;
}

void SetUpMML(MMLSegmentPlayer &mmlplayer)
{
	mmlplayer.AddSegment(
		"@2T90L12V12",
		"@2T90L2S0M6000",
		"@2T90L4V12",
		"","","");

	mmlplayer.AddSegment(
		"O3G+O4C+EO3G+O4C+EO3G+O4C+EO3G+O4C+E",
		"O3C+1",
		"O2C+1",
		"","","");

	mmlplayer.AddSegment(
		"O3G+O4C+EO3G+O4C+EO3G+O4C+EO3G+O4C+E",
		"O2B1",
		"O1B1",
		"","","");

	mmlplayer.AddSegment(
		"O3AO4C+EO3AO4C+EO3AO4DF+O3AO4DF+",
		"O2AF+",
		"O1A2F+2",
		"","","");

	mmlplayer.AddSegment(
		"O3G+B+O4F+ O3G+O4C+EO3G+O4C+D+O3F+BO4D+",
		"O2G+1",
		"O1G+1",
		"","","");

	mmlplayer.AddSegment(
		"O3EG+O4C+O3G+O4C+EO3G+O4C+EO3G+O4C+E",
		"O3C+2.O4G+6G+12",
		"O2C+1",
		"","","");

	mmlplayer.AddSegment(
		"O3G+O4D+O4F+O3G+O4D+O4F+O3G+O4D+O4F+O3G+O4D+O4F+",
		"O4G+2.G+6G+12",
		"O2B+1",
		"","","");

	mmlplayer.AddSegment(
		"O3G+O4C+EO3G+O4C+EO3G+O4C+F+O3G+O4C+F+",
		"G+2A2",
		"O3C+2O2F+2",
		"","","");

	mmlplayer.AddSegment(
		"O3G+BO4EO3G+BO4EO3ABO4D+O3ABO4D+",
		"G+2F+4B4",
		"O2B2O2B2",
		"","","");

	mmlplayer.AddSegment(
		"O3G+BO4EO3G+BO4EO3G+BO4EO3G+BO4E",
		"O4E4R4R2",
		"O3E1",
		"","","");

	mmlplayer.AddSegment(
		"O3GBO4EO3GBO4EO3GBO4EO3GBO4E",
		"R4R2G6G12",
		"O3E1",
		"","","");

	mmlplayer.AddSegment(
		"O3GBO4FO3GBO4FO3GBO4FO3GBO4F",
		"G2.G6G12",
		"O3D",
		"","","");

	mmlplayer.AddSegment(
		"O3GO4CEO3GO4CEO3GO4C+EO3F+O4C+E",
		"G.F+4",
		"O3C4O2B4A+2",
		"","","");

	mmlplayer.AddSegment(
		"O3F+BO4DO3F+BO4DO3GBO4C+O3EBO4C+",
		"F+G4E4",
		"O2BE4G4",
		"","","");

	mmlplayer.AddSegment(
		"O3F+BO4DO3F+BO4DO3F+A+O4C+O3F+A+O4C+",
		"F+2F+2",
		"O2F+2F+2",
		"","","");

	mmlplayer.AddSegment(
		"O3BO4DF+O3BO4DF+O3BO4D+F+O3BO4D+F+",
		"R4R2B4",
		"O2B1",
		"","","");

	mmlplayer.AddSegment(
		"O3BO4EGO3BO4EGO3BO4EGO3BO4EG",
		"O5C2.O4A+4",
		"O2BO3EGE",
		"","","");

	mmlplayer.AddSegment(
		"O3BO4D+F+O3BO4D+F+O3BO4D+F+O3BO4D+F+",
		"B2.B4",
		"O2B1",
		"","","");

	mmlplayer.AddSegment(
		"O3BO4EGO3BO4EGO3BO4EGO3BO4EG",
		"O5C.O4A+4",
		"O2BO3EGE",
		"","","");

	mmlplayer.AddSegment(
		"O3BO4D+F+O3BO4D+F+O3BO4DE+O3BO4DE+",
		"O4B2B2",
		"O2B2G+2",
		"","","");

	mmlplayer.AddSegment(
		"O3BO4C+G+O3BO4C+G+O3AO4C+F+O3AO4C+F+",
		"B2A2",
		"O2E+2F+2",
		"","","");

	mmlplayer.AddSegment(
		"O3GBO4DO3GBO4DO3F+AO4D+O3F+AO4D+",
		"GF+",
		"O2B2B+",
		"","","");

	mmlplayer.AddSegment(
		"O3C+F+AC+F+AC+F+G+C+E+G+",
		"C+C+4C+4",
		"O2C+2C+2",
		"","","");

	mmlplayer.AddSegment(
		"O3F+AO4C+O3AO4C+F+C+F+AC+F+A",
		"R2R4O5C+6C+12",
		"O3F+1",
		"","","");

	mmlplayer.AddSegment(
		"C+G+BC+G+BC+G+BC+G+B",
		"C+2.C+6C+12",
		"O3E+1",
		"","","");

	mmlplayer.AddSegment(
		"C+F+AC+F+AC-F+AC+F+A",
		"C+2O4B+4O5C+4",
		"O3F+2D+C+",
		"","","");

	mmlplayer.AddSegment(
		"D+F+G+D+F+G+D+F+G+D+F+G+",
		"D+2.D+4",
		"O3C-2.C-",
		"","","");

	mmlplayer.AddSegment(
		"EG+O5C+O4EG+O5C+O4D+F+AC+EA+",
		"E2D+4C+4",
		"O3C+2O2F+4F+4",
		"","","");

	mmlplayer.AddSegment(
		"O4B+O3B+O4D+G+O3B+O4D+AO3B+O4D+F+O3B+O4D+",
		"O2F+1",
		"O1F+1",
		"","","");

	mmlplayer.AddSegment(
		"R12O3B+O4D+O3G+B+O4D+O3AB+O4D+O3G+B+O4D+",
		"O2G+1",
		"O1G+1",
		"","","");

	mmlplayer.AddSegment(
		"O3EO4EG+O5C+O4EG+O5EO4EG+O5C+O4EG+",
		"O2G+1",
		"O1G+1",
		"","","");

	mmlplayer.AddSegment(
		"R12O3EG+O4C+O3EG+O4EO3EG+O4C+O3EG+",
		"O2G+1",
		"O1G+1",
		"","","");

	mmlplayer.AddSegment(
		"O3D+AF+B+AO4D+O3B+O4F+D+AF+B+",
		"O2G+1",
		"O2G+1",
		"","","");

	mmlplayer.AddSegment(
		"O3EO4C+O3G+O4EC+G+EO5C+O4G+O5EC+O4G+",
		"O2G+1",
		"O1G+1",
		"","","");

	mmlplayer.AddSegment(
		"C+F+EA+F+O5C+O4A+O5EC+F+EA+",
		"O2G+1",
		"O1G+1",
		"","","");

	mmlplayer.AddSegment(
		"O4F+B+AO5D+O4B+O5F+D+AF+B+AO6D+",
		"O2G+1",
		"O1G+1",
		"","","");

	mmlplayer.AddSegment(
		"O5B+F+AD+F+O4B+O5D+O4AB+F+AD+",
		"O2G+1",
		"O1G+1",
		"","","");

	mmlplayer.AddSegment(
		"F+O3B+O4D+O3AB+F+AD+F+C+F+A",
		"O2G+1",
		"O1G+1",
		"","","");

	mmlplayer.AddSegment(
		"O2B+O3F+G+AG+F+D+F+AC+F+A",
		"O2G+1",
		"O1G+1",
		"","","");

	mmlplayer.AddSegment(
		"O2B+O3F+G+AG+F+DF+AC+F+A",
		"O2G+1",
		"O1G+1",
		"","","");

	mmlplayer.AddSegment(
		"O2B+O3F+G+AG+F+C+EO4C+O3C+EO4C+",
		"O2G+2A2",
		"O1G+2A2",
		"","","");

	mmlplayer.AddSegment(
		"O3D+F+O4C+O3D+F+O4C+O3D+F+B+O3D+F+B+",
		"O2F+2G+2",
		"O1F+2G+2",
		"","","");

	mmlplayer.AddSegment(
		"O3EG+O4C+O3G+O4C+EO3G+O4C+EO3G+O4C+E",
		"O3C+2R4O4G+6G+12",
		"O2G+1",
		"","","");

	mmlplayer.AddSegment(
		"O3G+O4D+F+O3G+O4D+F+O3G+O4D+F+O3G+O4D+F+",
		"O4G+2.G+6G+12",
		"O2B+1",
		"","","");

	mmlplayer.AddSegment(
		"O3G+O4C+EO3G+O4C+EO3AO4C+F+O3AO4C+F+",
		"G+2A2",
		"O3C+2O2F+2",
		"","","");

	mmlplayer.AddSegment(
		"O3G+BO4EO3G+BO4EO3ABO4D+O3ABO4D+",
		"O4G+2F+4B4",
		"O2B2B2",
		"","","");

	mmlplayer.AddSegment(
		"O3G+BO4EO3BO4EG+O3BO4EG+O3BO4EG+",
		"O4E4R4R4B6B12",
		"O3E1",
		"","","");

	mmlplayer.AddSegment(
		"O3BO4F+AO3BO4F+AO3BO4F+AO3BO4F+A",
		"O4B2.B6B12",
		"O3D+1",
		"","","");

	mmlplayer.AddSegment(
		"O3BO4EG+O3BO4EG+O3B+O4F+G+C+EG+",
		"B2B+4O5C+4",
		"O3E2DC+",
		"","","");

	mmlplayer.AddSegment(
		"O4D+F+G+O4D+F+G+EG+O5C+O4EG+O5C+",
		"O5D+2E2",
		"O2B+2O3C+2",
		"","","");

	mmlplayer.AddSegment(
		"O4DF+ADF+AO3B+O4F+G+O3B+O4F+G+",
		"O5D2O4B+2",
		"O2F+2G+2",
		"","","");

	mmlplayer.AddSegment(
		"O4C+EG+C+EG+C+E+G+C+E+G+",
		"O5C+2.C+4",
		"O3C+1",
		"","","");

	mmlplayer.AddSegment(
		"O4C+F+AC+F+AC+F+AC+F+A",
		"O5D.O4B+4",
		"O3C+F+AF+",
		"","","");

	mmlplayer.AddSegment(
		"C+E+G+C+E+G+C+E+G+C+E+G+",
		"O5C+2.C+4",
		"O3C+1",
		"","","");

	mmlplayer.AddSegment(
		"O4C+F+AC+F+AC+F+AC+F+A",
		"O5D2.O4B+4",
		"O3C+F+AF+",
		"","","");

	mmlplayer.AddSegment(
		"C+E+G+C+E+G+C+F+AC+F+A",
		"O5C+C+",
		"O3C+2O2F+2",
		"","","");

	mmlplayer.AddSegment(
		"O3BO4F+AO3BO4F+AO3BO4F+AO3BO4EG+",
		"O4B.B4",
		"O3D+2.E",
		"","","");

	mmlplayer.AddSegment(
		"O3AO4EG+O3AO4D+F+O3G+O4D+F+O3G+O4C+E",
		"O4A4A4G+4G+4",
		"O3C+D+O2B+O3C+",
		"","","");

	mmlplayer.AddSegment(
		"O3F+O4C+D+O3F+O4C+D+O3G+O4C+D+O3AO4C+D+",
		"O4F+G+4A4",
		"O2A2G+F+",
		"","","");

	mmlplayer.AddSegment(
		"O3G+O4C+EO3G+O4C+EO3F+B+O4D+O3F+B+O4D+",
		"G+G+",
		"G+2G+2",
		"","","");

	mmlplayer.AddSegment(
		"O3EG+O4C+O3G+O4C+EO3G+O4C+EO3G+O4C+E",
		"O4C+4R4R4O2G+6G+12",
		"O2G+2.",
		"","","");

	mmlplayer.AddSegment(
		"O3G+O4D+F+O3G+O4D+F+O3G+O4D+F+O3G+O4D+F+",
		"O2G+2.G+6G+12",
		"O1A+1",
		"","","");

	mmlplayer.AddSegment(
		"O3G+O4EC+G+EO5C+O4G+O5EC+G+EC+",
		"O2G+2.G+6G+12",
		"O1A+1",
		"","","");

	mmlplayer.AddSegment(
		"O4B+O5D+O4AB+F+AD+F+O3AAG+F+",
		"O2G+2.G+6G+12",
		"O1G+2.O3B+4",
		"","","");

	mmlplayer.AddSegment(
		"O4C+EC+G+EO5C+O4G+O5EC+G+EC+",
		"O2G+2.G+6G+12",
		"O2C+1",
		"","","");

	mmlplayer.AddSegment(
		"O4B+O5D+O4AB+F+AD+F+O3AAG+F+",
		"O2G+2.G+6G+12",
		"O1G+2.O3B+",
		"","","");

	mmlplayer.AddSegment(
		"O3EG+O4C+EC+O3G+C+EG+O4C+O3G+E",
		"O2G+2O3C+2",
		"O2C+1",
		"","","");

	mmlplayer.AddSegment(
		"O2G+O3C+EG+EC+O2G+O3C+O2G+EG+E",
		"O3G+2",
		"O3C+2",
		"","","");

	mmlplayer.AddSegment(
		"R2O4C+2",
		"R2O3E2",
		"O2C+2O3C+2",
		"","","");

	mmlplayer.AddSegment(
		"V10O4C+1",
		"V10O3E1",
		"V10O3C+1",
		"","","");
}


class ApplicationMain
{
public:
    // State variables
	// Problem:
	// const int NX=16,NY=16;
	// Giving an error because NX and NY are not constant enough.

	// Solution 1:
	//enum
	//{
	//	NX=16,
	//	NY=16
	//};
	
	// Solution 2:
	// #define NX 16
	// #define NY 16

	// char wall[NX*NY+1]=
	// {
	// //   0123456789ABCDEF
	// 	"XXXXXXXXXXXXXXXX"  //0
	// 	"X       X     GX"  //1
	// 	"X XXXX XXXXX XXX"  //2
	// 	"XXX X          X"  //3
	// 	"X   XX XXXXXXX X"  //4
	// 	"XXX  X XXXX XX X"  //5
	// 	"X X XX       X X"  //6
	// 	"X X  X XXXX XX X"  //7
	// 	"X X XX XXXX XXXX"  //8
	// 	"X X  X X     X X"  //9
	// 	"X   XX X XXXXX X"  //a
	// 	"XXX  X X       X"  //b
	// 	"X X XX XXXXXXXXX"  //c
	// 	"X X  X XX X XX X"  //d
	// 	"XS             X"  //e
	// 	"XXXXXXXXXXXXXXXX"  //f
	// };


	// Solution 3:
	const int NX,NY;
	std::vector <char> _wall;
	char *wall;

	MMLSegmentPlayer mmlplayer;
	YsSoundPlayer player;
	YsSoundPlayer::Stream stream;
	YsSoundPlayer::SoundData nextWave;



	const double speed=6.0;
	const double rotSpeed=YsPi;
	const double blockDim=3.0;

	double x,y,z,h;

	double t=0.0;

	bool term=false;


	ApplicationMain() : NX(16),NY(16)  // In Solution 3, init NX NY here.
	{
		// Solution 3 continued >> :
		_wall.resize(NX*NY);
		char wallSrc[]=
		{
		//   0123456789ABCDEF
			"XXXXXXXXXXXXXXXX"  //0
			"X       X     GX"  //1
			"X XXXX XXXXX XXX"  //2
			"XXX X          X"  //3
			"X   XX XXXXXXX X"  //4
			"XXX  X XXXX XX X"  //5
			"X X XX       X X"  //6
			"X X  X XXXX XX X"  //7
			"X X XX XXXX XXXX"  //8
			"X X  X X     X X"  //9
			"X   XX X XXXXX X"  //a
			"XXX  X X       X"  //b
			"X X XX XXXXXXXXX"  //c
			"X X  X XX X XX X"  //d
			"XS             X"  //e
			"XXXXXXXXXXXXXXXX"  //f
		};
		for(int i=0; i<NX*NY; ++i)
		{
			_wall[i]=wallSrc[i];
		}
		wall=_wall.data();
		// Solution 3 continued << :

		x=0;
		y=1.5;
		z=10.0;
		h=0;
		ResetViewPoint(x,z,NX,NY,wall,blockDim);

		SetUpMML(mmlplayer);
		player.Start();
		player.StartStreaming(stream);
	}
    bool MustTerminate(void) const
    {
		return term;
	}
    void RunOneStep(void)
    {
		player.KeepPlaying();  // <- This line is only needed for Linux ALSA.
		if(YSTRUE==player.StreamPlayerReadyToAcceptNextSegment(stream,nextWave))
		{
			player.AddNextStreamingSegment(stream,nextWave);
			auto rawWave=mmlplayer.GenerateWave(100);  // Create for next 100ms
			nextWave.CreateFromSigned16bitStereo(YM2612::WAVE_SAMPLING_RATE,rawWave);

			if(0!=mmlplayer.GetLastErrorCode())
			{
				for(auto msg : mmlplayer.GetLastError().Format())
				{
					std::cout << msg << std::endl;
				}
			}
		}


		FsPollDevice();
		auto key=FsInkey();

		auto ms=FsPassedTime();
		auto dt=(double)ms/1000.0;
		t+=dt;

		if(FSKEY_ESC==key)
		{
			term=true;
			return;
		}

		if(0!=FsGetKeyState(FSKEY_SPACE))
		{
			if(y<8.0)
			{
				y+=0.1;
			}
		}
		else
		{
			if(y>1.5)
			{
				y-=0.1;
			}
			if(y<1.5)
			{
				y=1.5;
			}
		}


		const double vx=-sin(h);
		const double vz=-cos(h);

		const double prevX=x;
		const double prevZ=z;

		if(0!=FsGetKeyState(FSKEY_UP))
		{
			x+=speed*vx*dt;
			z+=speed*vz*dt;
		}
		if(0!=FsGetKeyState(FSKEY_DOWN))
		{
			x-=speed*vx*dt;
			z-=speed*vz*dt;
		}
		if(0!=FsGetKeyState(FSKEY_LEFT))
		{
			h+=dt*rotSpeed;
		}
		if(0!=FsGetKeyState(FSKEY_RIGHT))
		{
			h-=dt*rotSpeed;
		}

		if('X'==GetBlock(NX,NY,wall,blockDim,x,z) ||
		   'X'==GetBlock(NX,NY,wall,blockDim,x+blockDim/10.0,z) ||
		   'X'==GetBlock(NX,NY,wall,blockDim,x-blockDim/10.0,z))
		{
			x=prevX;
		}
		if('X'==GetBlock(NX,NY,wall,blockDim,x,z) ||
		   'X'==GetBlock(NX,NY,wall,blockDim,x       ,z+blockDim/10.0) ||
		   'X'==GetBlock(NX,NY,wall,blockDim,x       ,z-blockDim/10.0))
		{
			z=prevZ;
		}

		if('G'==GetBlock(NX,NY,wall,blockDim,x,z))
		{
			printf("Goal!\n");
			term=true;
			return;
		}

		FsSleep(10);
	}
    void Draw(void) const
    {
		int wid,hei;
		FsGetWindowSize(wid,hei);

		glEnable(GL_DEPTH_TEST);

		glClear(GL_DEPTH_BUFFER_BIT|GL_COLOR_BUFFER_BIT);

		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		gluPerspective(45.0,(double)wid/(double)hei,0.1,40.0);

		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();

		glRotated(-h*180.0/YsPi,0,1,0);
		glTranslated(-x,-y,-z);

		DrawMaze(NX,NY,wall,blockDim);
 
		FsSwapBuffers();
	}
};
int main(void)
{
	FsOpenWindow(0,0,800,600,1);
    ApplicationMain app;
    while(true!=app.MustTerminate())
    {
        app.RunOneStep();
        app.Draw();
    }
    return 0;
}
