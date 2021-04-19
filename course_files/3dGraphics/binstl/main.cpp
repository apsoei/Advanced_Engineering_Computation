#include <fssimplewindow.h>
#include "ysglfontdata.h"
#include <vector>
#include <chrono>
#include <ysclass.h>
#include <iostream>

#include "binstl.h"



void MakeBlock(std::vector <float> &vtx,std::vector <float> &nom,std::vector <float> &col,float x1,float y1,float z1,float x2,float y2,float z2)
{
	vtx.clear();
	col.clear();
	nom.clear();

	// 0  1 Quad
	// 3  2
	// 0-1-2  2-3-0  Triangles

    vtx.push_back(x1);vtx.push_back(y1);vtx.push_back(z1);
    vtx.push_back(x2);vtx.push_back(y1);vtx.push_back(z1);
    vtx.push_back(x2);vtx.push_back(y2);vtx.push_back(z1);

    vtx.push_back(x2);vtx.push_back(y2);vtx.push_back(z1);
    vtx.push_back(x1);vtx.push_back(y2);vtx.push_back(z1);
    vtx.push_back(x1);vtx.push_back(y1);vtx.push_back(z1);

	nom.push_back(0);nom.push_back(0);nom.push_back(-1);
	nom.push_back(0);nom.push_back(0);nom.push_back(-1);
	nom.push_back(0);nom.push_back(0);nom.push_back(-1);
	nom.push_back(0);nom.push_back(0);nom.push_back(-1);
	nom.push_back(0);nom.push_back(0);nom.push_back(-1);
	nom.push_back(0);nom.push_back(0);nom.push_back(-1);

	col.push_back(1);col.push_back(0);col.push_back(0);col.push_back(1);
	col.push_back(1);col.push_back(0);col.push_back(0);col.push_back(1);
	col.push_back(1);col.push_back(0);col.push_back(0);col.push_back(1);
	col.push_back(1);col.push_back(0);col.push_back(0);col.push_back(1);
	col.push_back(1);col.push_back(0);col.push_back(0);col.push_back(1);
	col.push_back(1);col.push_back(0);col.push_back(0);col.push_back(1);

    vtx.push_back(x1);vtx.push_back(y1);vtx.push_back(z2);
    vtx.push_back(x2);vtx.push_back(y1);vtx.push_back(z2);
    vtx.push_back(x2);vtx.push_back(y2);vtx.push_back(z2);

    vtx.push_back(x2);vtx.push_back(y2);vtx.push_back(z2);
    vtx.push_back(x1);vtx.push_back(y2);vtx.push_back(z2);
    vtx.push_back(x1);vtx.push_back(y1);vtx.push_back(z2);

	nom.push_back(0);nom.push_back(0);nom.push_back(1);
	nom.push_back(0);nom.push_back(0);nom.push_back(1);
	nom.push_back(0);nom.push_back(0);nom.push_back(1);
	nom.push_back(0);nom.push_back(0);nom.push_back(1);
	nom.push_back(0);nom.push_back(0);nom.push_back(1);
	nom.push_back(0);nom.push_back(0);nom.push_back(1);

	col.push_back(0);col.push_back(1);col.push_back(0);col.push_back(1);
	col.push_back(0);col.push_back(1);col.push_back(0);col.push_back(1);
	col.push_back(0);col.push_back(1);col.push_back(0);col.push_back(1);
	col.push_back(0);col.push_back(1);col.push_back(0);col.push_back(1);
	col.push_back(0);col.push_back(1);col.push_back(0);col.push_back(1);
	col.push_back(0);col.push_back(1);col.push_back(0);col.push_back(1);

    vtx.push_back(x1);vtx.push_back(y1);vtx.push_back(z1);
    vtx.push_back(x2);vtx.push_back(y1);vtx.push_back(z1);
    vtx.push_back(x2);vtx.push_back(y1);vtx.push_back(z2);

    vtx.push_back(x2);vtx.push_back(y1);vtx.push_back(z2);
    vtx.push_back(x1);vtx.push_back(y1);vtx.push_back(z2);
    vtx.push_back(x1);vtx.push_back(y1);vtx.push_back(z1);

	nom.push_back(0);nom.push_back(-1);nom.push_back(0);
	nom.push_back(0);nom.push_back(-1);nom.push_back(0);
	nom.push_back(0);nom.push_back(-1);nom.push_back(0);
	nom.push_back(0);nom.push_back(-1);nom.push_back(0);
	nom.push_back(0);nom.push_back(-1);nom.push_back(0);
	nom.push_back(0);nom.push_back(-1);nom.push_back(0);

	col.push_back(0);col.push_back(0);col.push_back(1);col.push_back(1);
	col.push_back(0);col.push_back(0);col.push_back(1);col.push_back(1);
	col.push_back(0);col.push_back(0);col.push_back(1);col.push_back(1);
	col.push_back(0);col.push_back(0);col.push_back(1);col.push_back(1);
	col.push_back(0);col.push_back(0);col.push_back(1);col.push_back(1);
	col.push_back(0);col.push_back(0);col.push_back(1);col.push_back(1);

    vtx.push_back(x1);vtx.push_back(y2);vtx.push_back(z1);
    vtx.push_back(x2);vtx.push_back(y2);vtx.push_back(z1);
    vtx.push_back(x2);vtx.push_back(y2);vtx.push_back(z2);

    vtx.push_back(x2);vtx.push_back(y2);vtx.push_back(z2);
    vtx.push_back(x1);vtx.push_back(y2);vtx.push_back(z2);
    vtx.push_back(x1);vtx.push_back(y2);vtx.push_back(z1);

	nom.push_back(0);nom.push_back(1);nom.push_back(0);
	nom.push_back(0);nom.push_back(1);nom.push_back(0);
	nom.push_back(0);nom.push_back(1);nom.push_back(0);
	nom.push_back(0);nom.push_back(1);nom.push_back(0);
	nom.push_back(0);nom.push_back(1);nom.push_back(0);
	nom.push_back(0);nom.push_back(1);nom.push_back(0);

	col.push_back(1);col.push_back(1);col.push_back(0);col.push_back(1);
	col.push_back(1);col.push_back(1);col.push_back(0);col.push_back(1);
	col.push_back(1);col.push_back(1);col.push_back(0);col.push_back(1);
	col.push_back(1);col.push_back(1);col.push_back(0);col.push_back(1);
	col.push_back(1);col.push_back(1);col.push_back(0);col.push_back(1);
	col.push_back(1);col.push_back(1);col.push_back(0);col.push_back(1);

    vtx.push_back(x1);vtx.push_back(y1);vtx.push_back(z1);
    vtx.push_back(x1);vtx.push_back(y2);vtx.push_back(z1);
    vtx.push_back(x1);vtx.push_back(y2);vtx.push_back(z2);

    vtx.push_back(x1);vtx.push_back(y2);vtx.push_back(z2);
    vtx.push_back(x1);vtx.push_back(y1);vtx.push_back(z2);
    vtx.push_back(x1);vtx.push_back(y1);vtx.push_back(z1);

	nom.push_back(-1);nom.push_back(0);nom.push_back(0);
	nom.push_back(-1);nom.push_back(0);nom.push_back(0);
	nom.push_back(-1);nom.push_back(0);nom.push_back(0);
	nom.push_back(-1);nom.push_back(0);nom.push_back(0);
	nom.push_back(-1);nom.push_back(0);nom.push_back(0);
	nom.push_back(-1);nom.push_back(0);nom.push_back(0);

	col.push_back(0.5);col.push_back(1);col.push_back(0.5);col.push_back(1);
	col.push_back(0.5);col.push_back(1);col.push_back(0.5);col.push_back(1);
	col.push_back(0.5);col.push_back(1);col.push_back(0.5);col.push_back(1);
	col.push_back(0.5);col.push_back(1);col.push_back(0.5);col.push_back(1);
	col.push_back(0.5);col.push_back(1);col.push_back(0.5);col.push_back(1);
	col.push_back(0.5);col.push_back(1);col.push_back(0.5);col.push_back(1);

    vtx.push_back(x2);vtx.push_back(y1);vtx.push_back(z1);
    vtx.push_back(x2);vtx.push_back(y2);vtx.push_back(z1);
    vtx.push_back(x2);vtx.push_back(y2);vtx.push_back(z2);

    vtx.push_back(x2);vtx.push_back(y2);vtx.push_back(z2);
    vtx.push_back(x2);vtx.push_back(y1);vtx.push_back(z2);
    vtx.push_back(x2);vtx.push_back(y1);vtx.push_back(z1);

	nom.push_back(1);nom.push_back(0);nom.push_back(0);
	nom.push_back(1);nom.push_back(0);nom.push_back(0);
	nom.push_back(1);nom.push_back(0);nom.push_back(0);
	nom.push_back(1);nom.push_back(0);nom.push_back(0);
	nom.push_back(1);nom.push_back(0);nom.push_back(0);
	nom.push_back(1);nom.push_back(0);nom.push_back(0);

	col.push_back(0);col.push_back(1);col.push_back(1);col.push_back(1);
	col.push_back(0);col.push_back(1);col.push_back(1);col.push_back(1);
	col.push_back(0);col.push_back(1);col.push_back(1);col.push_back(1);
	col.push_back(0);col.push_back(1);col.push_back(1);col.push_back(1);
	col.push_back(0);col.push_back(1);col.push_back(1);col.push_back(1);
	col.push_back(0);col.push_back(1);col.push_back(1);col.push_back(1);
}

class ApplicationMain
{
private:
	bool term=false;

	const double fovDeg=30.0;
	const double fovRad=YsPi/6.0;

	std::vector <float> vtx3d,col3d,nom3d;
	double viewDistance=40.0;
	YsMatrix3x3 viewRotation;
	YsVec3 viewTarget;
	decltype(std::chrono::high_resolution_clock::now()) lastT;

public:
	ApplicationMain(int argc,char *argv[]);

	bool LoadSTL(const char fName[]);

	bool MustTerminate(void) const;
	void RunOneStep(void);
	void SetUpHeadLight(void) const;
	void Draw(void) const;
};

ApplicationMain::ApplicationMain(int argc,char *argv[])
{
	viewTarget.Set(0.0,0.0,0.0);
	if(2<=argc)
	{
		LoadSTL(argv[1]);
	}
}

bool ApplicationMain::LoadSTL(const char fName[])
{
	if(true==OpenBinSTL(vtx3d,nom3d,fName))
	{
		float cen[3]={0,0,0},bbx[2][3];
		if(3<=vtx3d.size())
		{
			bbx[0][0]=vtx3d[0]; // Minimum xyz
			bbx[0][1]=vtx3d[1];
			bbx[0][2]=vtx3d[2];
			bbx[1][0]=vtx3d[0]; // Maximum xyz
			bbx[1][1]=vtx3d[1];
			bbx[1][2]=vtx3d[2];

			for(int i=0; i<vtx3d.size()/3; ++i)
			{
				col3d.push_back(0);
				col3d.push_back(1);
				col3d.push_back(0);
				col3d.push_back(1);
				cen[0]+=vtx3d[i*3];
				cen[1]+=vtx3d[i*3+1];
				cen[2]+=vtx3d[i*3+2];

				bbx[0][0]=std::min(bbx[0][0],vtx3d[i*3]);
				bbx[0][1]=std::min(bbx[0][1],vtx3d[i*3+1]);
				bbx[0][2]=std::min(bbx[0][2],vtx3d[i*3+2]);
				bbx[1][0]=std::max(bbx[1][0],vtx3d[i*3]);
				bbx[1][1]=std::max(bbx[1][1],vtx3d[i*3+1]);
				bbx[1][2]=std::max(bbx[1][2],vtx3d[i*3+2]);
			}
			auto nVTx=vtx3d.size()/3;
			cen[0]/=(float)nVTx;
			cen[1]/=(float)nVTx;
			cen[2]/=(float)nVTx;
			viewTarget.Set(cen[0],cen[1],cen[2]);

			auto dx=bbx[1][0]-bbx[0][0];
			auto dy=bbx[1][1]-bbx[0][1];
			auto dz=bbx[1][2]-bbx[0][2];
			auto d=sqrt(dx*dx+dy*dy+dz*dz);
			viewDistance=(d/2.0)/sin(fovRad/2.0);
		}
		return true;
	}
	return false;
}

bool ApplicationMain::MustTerminate(void) const
{
	return term;
}
void ApplicationMain::RunOneStep(void)
{
	auto currentT=std::chrono::high_resolution_clock::now();
	auto deltaT=currentT-lastT;
	auto tick=std::chrono::duration_cast<std::chrono::microseconds>(deltaT).count();
	lastT=currentT;

	double dt=(double)tick/1000000.0;

	auto key=FsInkey();
	if(FSKEY_ESC==key)
	{
		term=true;
	}

	if(FsGetKeyState(FSKEY_UP))
	{
		YsMatrix3x3 rot;
		rot.RotateYZ(dt*YsPi/3.0);
		viewRotation=rot*viewRotation;
	}
	if(FsGetKeyState(FSKEY_DOWN))
	{
		YsMatrix3x3 rot;
		rot.RotateYZ(-dt*YsPi/3.0);
		viewRotation=rot*viewRotation;
	}
	if(FsGetKeyState(FSKEY_LEFT))
	{
		YsMatrix3x3 rot;
		rot.RotateXZ(dt*YsPi/3.0);
		viewRotation=rot*viewRotation;
	}
	if(FsGetKeyState(FSKEY_RIGHT))
	{
		YsMatrix3x3 rot;
		rot.RotateXZ(-dt*YsPi/3.0);
		viewRotation=rot*viewRotation;
	}

	int lb,mb,rb,mx,my;
	auto evt=FsGetMouseEvent(lb,mb,rb,mx,my);
	if(FSMOUSEEVENT_LBUTTONDOWN==evt)
	{
	}
}
void ApplicationMain::SetUpHeadLight(void) const
{
    GLfloat lightDir[]={0,1/sqrt(2.0f),1/sqrt(2.0f),0};
    glLightfv(GL_LIGHT0,GL_POSITION,lightDir);
    glEnable(GL_COLOR_MATERIAL);
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
}
void ApplicationMain::Draw(void) const
{
	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);

	glEnable(GL_DEPTH_TEST);

	int wid,hei;
	FsGetWindowSize(wid,hei);
	double aspect=(double)wid/(double)hei;

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(fovDeg,aspect,viewDistance/10.0,viewDistance*10.0);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	SetUpHeadLight();

	/* In a traditional OpenGL it could be:
	glTranslated(0.0,0.0,-40.0);
	glRotated ....
	glTranslated(centerize the object);
	*/

	YsMatrix4x4 modelView;
	modelView.Translate(0.0,0.0,-viewDistance);
	modelView*=viewRotation;
	modelView.Translate(-viewTarget);

	double glMat[16];
	modelView.GetOpenGlCompatibleMatrix(glMat);
	glMultMatrixd(glMat);

	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_NORMAL_ARRAY);
	glEnableClientState(GL_COLOR_ARRAY);
	glColorPointer(4,GL_FLOAT,0,col3d.data());
	glVertexPointer(3,GL_FLOAT,0,vtx3d.data());
	glNormalPointer(GL_FLOAT,0,nom3d.data());
	glDrawArrays(GL_TRIANGLES,0,vtx3d.size()/3);
	glDisableClientState(GL_VERTEX_ARRAY);
	glDisableClientState(GL_NORMAL_ARRAY);
	glDisableClientState(GL_COLOR_ARRAY);

	FsSwapBuffers();
}



int main(int argc,char *argv[])
{
	FsOpenWindow(0,0,800,600,1);
	ApplicationMain app(argc,argv);
	while(true!=app.MustTerminate())
	{
		FsPollDevice();
		app.RunOneStep();
		app.Draw();
	}
	return 0;
}
