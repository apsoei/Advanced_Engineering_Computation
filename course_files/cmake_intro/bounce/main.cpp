#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include "fssimplewindow.h"

const double YsPi=3.1415927;

void DrawCircle(int xi,int yi,int ri)
{
	double x=(double)xi;
	double y=(double)yi;
	double r=(double)ri;

	glBegin(GL_TRIANGLE_FAN);
	for(int a=0; a<64; ++a)
	{
		const double radian=YsPi*2.0*(double)a/64.0;
		const double c=cos(radian);
		const double s=sin(radian);

		glVertex2d(x+c*r,y+s*r);
	}
	glEnd();
}

void ConvertToScreen(int &sx,int &sy,double x,double y)
{
	sx=400+(int)(x*10.0);
	sy=600-(int)(y*10.0);
}

void MoveBall(double &x,double &y,double &vx,double &vy,double m,double dt)
{
	x+=vx*dt;
	y+=vy*dt;

	double Fx=0.0;
	double Fy=-9.8*m;

	double ax=Fx/m;
	double ay=Fy/m;

	vx+=ax*dt;
	vy+=ay*dt;
}

void BounceBall(double &x,double &y,double &vx,double &vy)
{
	if(y<1.0 && vy<0.0)
	{
		vy=-vy;
	}
	if((x<-39.0 && vx<0.0) || (39.0<x && 0.0<vx))
	{
		vx=-vx;
	}
}

void Collision(double x1,double y1,double &vx1,double &vy1,double r1,
               double x2,double y2,double &vx2,double &vy2,double r2)
{
	double dx=x2-x1;
	double dy=y2-y1;
	double distSq=dx*dx+dy*dy;
	double dist=sqrt(distSq);
	if(dist<r1+r2)
	{
		if(0.0<distSq)
		{
			double nx=(x2-x1)/dist;
			double ny=(y2-y1)/dist;
			double k1=vx1*nx+vy1*ny;
			double k2=vx2*nx+vy2*ny;

			if((k2>0.0 && k2<k1) ||
			   (k1<0.0 && k2<k1) ||
			   (k1>0.0 && k2<0.0))
			{
				vx1=vx1+nx*(k2-k1);
				vy1=vy1+ny*(k2-k1);

				vx2=vx2+nx*(k1-k2);
				vy2=vy2+ny*(k1-k2);
			}
		}
	}
}

int main(void)
{
	srand((int)time(NULL));

	FsOpenWindow(0,0,800,600,1);

	const int nBall=100;
	double ballX[nBall],ballY[nBall];
	double ballVx[nBall],ballVy[nBall];
	double dt=0.025;

	for(int i=0; i<nBall; ++i)
	{
		int x=rand()%20-10;
		int y=rand()%20+20;
		int vx=rand()%10-20;
		int vy=rand()%10-20;

		ballX[i]=(double)x;
		ballY[i]=(double)y;
		ballVx[i]=(double)vx;
		ballVy[i]=(double)vy;
	}

	bool term=false;
	while(true!=term)
	{
		FsPollDevice();

		int key=FsInkey();
		if(FSKEY_ESC==key)
		{
			term=true;
		}

		for(int i=0; i<nBall; ++i)
		{
			MoveBall(ballX[i],ballY[i],ballVx[i],ballVy[i],1.0,dt);
			BounceBall(ballX[i],ballY[i],ballVx[i],ballVy[i]);
		}

		for(int i=0; i<nBall; ++i)
		{
			for(int j=i+1; j<nBall; ++j)
			{
				Collision(ballX[i],ballY[i],ballVx[i],ballVy[i],1.0,
				          ballX[j],ballY[j],ballVx[j],ballVy[j],1.0);
			}
		}


		glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);

		glColor3ub(0,0,255);

		for(int i=0; i<nBall; ++i)
		{
			int sx,sy;
			ConvertToScreen(sx,sy,ballX[i],ballY[i]);
			DrawCircle(sx,sy,10);
		}

		FsSwapBuffers();

		FsSleep(25);
	}

	return 0;
}
