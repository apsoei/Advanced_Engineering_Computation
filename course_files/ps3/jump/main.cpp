#include <fssimplewindow.h>
#include <math.h>
#include <chrono>

const double YsPI=3.1415927;
const double tol=0.0001;

void GetLeg(double v[6],double t)
{
	v[0]= 0.0;
	v[1]= 0.0;
	v[2]= 15.0;
	v[3]=-10.0;
	v[4]= 5.0;
	v[5]=-30.0;

	t=fmod(t,2.0);
	if(1.0<t)
	{
		t=2.0-t;
	}
	for(int i=1; i<3; ++i)
	{
		double s=sin(-t*YsPI/3.0);
		double c=cos(-t*YsPI/3.0);

		double x=v[i*2];
		double y=v[i*2+1];
		v[i*2  ]=c*x-s*y;
		v[i*2+1]=s*x+c*y;
	}
}

void GetArm(double v[6],double t)
{
	v[0]= 0.0;
	v[1]= 0.0;
	v[2]= 10.0;
	v[3]=-15.0;
	v[4]= 25.0;
	v[5]=- 5.0;

	t=fmod(t,2.0);
	if(1.0<t)
	{
		t=2.0-t;
	}
	for(int i=1; i<3; ++i)
	{
		double s=sin(-t*YsPI/2.0);
		double c=cos(-t*YsPI/2.0);

		double x=v[i*2];
		double y=v[i*2+1];
		v[i*2  ]=c*x-s*y;
		v[i*2+1]=s*x+c*y;
	}
}

void DrawHead(double cx,double cy)
{
	glBegin(GL_LINE_LOOP);
	for(int i=0; i<64; ++i)
	{
		double ang=YsPI*(double)i/32.0;
		double s=sin(ang);
		double c=cos(ang);
		glVertex2d(cx+c*15.0,cy+s*15.0);
	}
	glEnd();
}

void DrawRunning(double x0,double y0,double t)
{
	glBegin(GL_LINES);

	glVertex2d(x0     ,y0-30.0);
	glVertex2d(x0+10.0,y0-60.0);

	double v[6];
	GetLeg(v,t);
	glVertex2d(x0+v[0],y0-30.0-v[1]);
	glVertex2d(x0+v[2],y0-30.0-v[3]);

	glVertex2d(x0+v[2],y0-30.0-v[3]);
	glVertex2d(x0+v[4],y0-30.0-v[5]);

	GetLeg(v,t+1.0);
	glVertex2d(x0+v[0],y0-30.0-v[1]);
	glVertex2d(x0+v[2],y0-30.0-v[3]);

	glVertex2d(x0+v[2],y0-30.0-v[3]);
	glVertex2d(x0+v[4],y0-30.0-v[5]);

	GetArm(v,t);
	glVertex2d(x0+8.0+v[0],y0-55.0-v[1]);
	glVertex2d(x0+8.0+v[2],y0-55.0-v[3]);

	glVertex2d(x0+8.0+v[2],y0-55.0-v[3]);
	glVertex2d(x0+8.0+v[4],y0-55.0-v[5]);

	GetArm(v,t+1.0);
	glVertex2d(x0+8.0+v[0],y0-55.0-v[1]);
	glVertex2d(x0+8.0+v[2],y0-55.0-v[3]);

	glVertex2d(x0+8.0+v[2],y0-55.0-v[3]);
	glVertex2d(x0+8.0+v[4],y0-55.0-v[5]);

	glEnd();

	DrawHead(x0+10.0,y0-75.0);
}

void DrawObstract(double x,double y,double wid,double hei)
{
	glBegin(GL_QUADS);
	glVertex2d(x    ,y);
	glVertex2d(x+wid,y);
	glVertex2d(x+wid,y-hei);
	glVertex2d(x    ,y-hei);
	glEnd();
}

int main(void)
{
	double run=0.0;

	double x=300.0,y=500.0,vx=100.0,vy=0.0;
	double gndX=0.0;
	double obstX=800.0,obstY=500.0,obstWid=100.0,obstHei=100.0;

	std::chrono::time_point <std::chrono::high_resolution_clock> t0=std::chrono::high_resolution_clock::now();
	double prevSec=0.0;

	FsOpenWindow(0,0,800,600,1);
	for(;;)
	{
		FsPollDevice();

		auto t=std::chrono::high_resolution_clock::now()-t0;
		auto ms=std::chrono::duration_cast<std::chrono::milliseconds>(t).count();
		double sec=(double)ms/1000.0;
		double deltaT=sec-prevSec;

		if(-vy<tol)
		{
			run+=deltaT*3.0;
		}
		x+=deltaT*vx;
		gndX+=deltaT*vx;
		prevSec=sec;

		auto key=FsInkey();
		if(FSKEY_ESC==key)
		{
			break;
		}

		if(FSKEY_SPACE==key)
		{
			if(400.0<y && (fabs(vy)<tol || vy<-50.0))
			{
				vy=-100.0;
			}
		}
		vy+=80.0*deltaT;
		y+=vy*deltaT;
		if(500.0<=y && 0.0<=vy)
		{
			vy=0.0;
			y=500.0;
		}

		if(obstX+obstWid-gndX<0.0)
		{
			obstX=gndX+800.0;
		}

		if(obstX<=x && x<obstX+obstWid && obstY-obstHei<=y && y<obstY)
		{
			printf("Game Over\n");
			break;
		}

		glClear(GL_DEPTH_BUFFER_BIT|GL_COLOR_BUFFER_BIT);

		DrawRunning(x-gndX,y,run);

		DrawObstract(obstX-gndX,obstY,obstWid,obstHei);

		// Ground
		glBegin(GL_LINES);
		glVertex2i(0,500);
		glVertex2i(800,500);
		glEnd();

		FsSwapBuffers();
	}
	return 0;
}
