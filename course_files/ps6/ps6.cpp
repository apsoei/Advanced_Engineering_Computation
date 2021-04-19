#include <fssimplewindow.h>
#include "ysclass.h"
#include <stdio.h>
#include <chrono>

// You can use fstream or stdio, whichever you like for writing a binary-stl.
// I have a feeling that it is easier to do with C standard library.



class ApplicationMain
{
private:
	bool term=false;
	std::vector <float> vtx2d;	// Clicked points.
	std::vector <float> col2d;	// Color for clicked points.  Make it all (0,0,0,1)

	double fovRadian=YsPi/6.0;  // 30 degrees
	double fovDegree=30.0;

	YsMatrix3x3 viewRotation;
	YsVec3 viewTarget;
	double viewDistance=0.0;
	std::vector <float> vtx3d;	// Extruded Shape Triangles
	std::vector <float> col3d;
	std::vector <float> nom3d;

	decltype(std::chrono::high_resolution_clock::now()) lastT;
public:
	ApplicationMain();
	bool MustTerminate(void) const;
	void RunOneStep(void);
	void Draw(void) const;

	// Write this function.
	// This function must make an extruded shape from the polygon that the user created by clicking.
	// The shape must be stored in vtx3d,col3d, and nom3d.
	// You don't have to deal with a concave polygon.
	// If the user makes a concave polygon, the output may have self-intersecting or overlapping triangles.
	// (It would be great if you can write your own tessellation function, but it would be beyond the scope.)
	// Also you can assume the user draws a polygon clockwise.
	// For calculating normal, I have written CalculateNormal() function for you.
	void RecreateExtrusion(void);

	// See Binary-STL Viewer example, and fill this function.
	void ResetViewDistanceAndTarget(void);

	// Write this function.
	// This function must save the extruded shape in "extruded.stl" in the current working directory.
	void SaveBinaryStl(void);

	void CalculateNormal(void);
};

ApplicationMain::ApplicationMain()
{
	viewTarget=YsVec3::Origin();
	viewDistance=800.0;
	lastT=std::chrono::high_resolution_clock::now();
}
bool ApplicationMain::MustTerminate(void) const
{
	return term;
}
void ApplicationMain::RunOneStep(void)
{
	auto deltaT=std::chrono::high_resolution_clock::now()-lastT;
	auto deltaTinMS=std::chrono::duration_cast<std::chrono::microseconds>(deltaT).count();
	double dt=(double)deltaTinMS/1000000.0;
	lastT=std::chrono::high_resolution_clock::now();

	auto key=FsInkey();
	if(FSKEY_ESC==key)
	{
		term=true;
	}
	if(FSKEY_S==key)
	{
		SaveBinaryStl();
	}
	int lb,mb,rb,mx,my;
	int evt=FsGetMouseEvent(lb,mb,rb,mx,my);
	if(FSMOUSEEVENT_LBUTTONDOWN==evt)
	{
		vtx2d.push_back((float)mx);
		vtx2d.push_back((float)my);
		col2d.push_back(0);
		col2d.push_back(0);
		col2d.push_back(0);
		col2d.push_back(1);
		RecreateExtrusion();
		ResetViewDistanceAndTarget();
	}

	if(FsGetKeyState(FSKEY_LEFT))
	{
		YsMatrix3x3 rot;
		rot.RotateXZ(dt*YsPi/6);
		viewRotation=rot*viewRotation;
	}
	if(FsGetKeyState(FSKEY_RIGHT))
	{
		YsMatrix3x3 rot;
		rot.RotateXZ(-dt*YsPi/6);
		viewRotation=rot*viewRotation;
	}
	if(FsGetKeyState(FSKEY_UP))
	{
		YsMatrix3x3 rot;
		rot.RotateYZ(dt*YsPi/6);
		viewRotation=rot*viewRotation;
	}
	if(FsGetKeyState(FSKEY_DOWN))
	{
		YsMatrix3x3 rot;
		rot.RotateYZ(-dt*YsPi/6);
		viewRotation=rot*viewRotation;
	}
}
void ApplicationMain::Draw(void) const
{
	int wid,hei;
	FsGetWindowSize(wid,hei);

	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);

	glEnable(GL_DEPTH_TEST);


	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(fovDegree,(double)wid/(double)hei,viewDistance/10.0,viewDistance*3.0);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	// Replace with your code here >>
	glTranslated(0,0,-300.0);
	// Replace with your code here <<

	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_COLOR_ARRAY);
	glEnableClientState(GL_NORMAL_ARRAY);
	glColorPointer(4,GL_FLOAT,0,col3d.data());
	glVertexPointer(3,GL_FLOAT,0,vtx3d.data());
	glNormalPointer(GL_FLOAT,0,nom3d.data());
	glDrawArrays(GL_TRIANGLES,0,vtx3d.size()/3);  // Divide by 3 because a 3D vector consists of 3 components.
	glDisableClientState(GL_VERTEX_ARRAY);
	glDisableClientState(GL_COLOR_ARRAY);
	glDisableClientState(GL_NORMAL_ARRAY);


	glDisable(GL_DEPTH_TEST);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0,wid,hei,0,-1,1);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_COLOR_ARRAY);
	glColorPointer(4,GL_FLOAT,0,col2d.data());
	glVertexPointer(2,GL_FLOAT,0,vtx2d.data());
	glDrawArrays(GL_LINE_STRIP,0,vtx2d.size()/2);  // Divide by 2 because a 2D vector consists of 2 components.
	glDisableClientState(GL_VERTEX_ARRAY);
	glDisableClientState(GL_COLOR_ARRAY);

	FsSwapBuffers();
}

void ApplicationMain::RecreateExtrusion(void)
{
	// Extrude the polygon by adding -100 and +100 depth.
	// Make triangles for the polygon by connecting the center and each edge.
	// Make sure back side of the polygon has the reverse-order triangles from the front side.

	vtx3d.clear();
	col3d.clear();

	// Replace with your code here >>
	vtx3d.push_back(   0.0);  vtx3d.push_back(   0.0);  vtx3d.push_back(0);
	vtx3d.push_back( 500.0);  vtx3d.push_back(   0.0);  vtx3d.push_back(0);
	vtx3d.push_back( 500.0);  vtx3d.push_back( 500.0);  vtx3d.push_back(0);

	vtx3d.push_back( 500.0);  vtx3d.push_back( 500.0);  vtx3d.push_back(0);
	vtx3d.push_back(   0.0);  vtx3d.push_back( 500.0);  vtx3d.push_back(0);
	vtx3d.push_back(   0.0);  vtx3d.push_back(   0.0);  vtx3d.push_back(0);

	col3d.push_back(0);col3d.push_back(0);col3d.push_back(1);col3d.push_back(1);
	col3d.push_back(0);col3d.push_back(0);col3d.push_back(1);col3d.push_back(1);
	col3d.push_back(0);col3d.push_back(0);col3d.push_back(1);col3d.push_back(1);
	col3d.push_back(0);col3d.push_back(0);col3d.push_back(1);col3d.push_back(1);
	col3d.push_back(0);col3d.push_back(0);col3d.push_back(1);col3d.push_back(1);
	col3d.push_back(0);col3d.push_back(0);col3d.push_back(1);col3d.push_back(1);
	// Replace with your code here <<

	CalculateNormal(); // Call this after you set triangles in vtx3d.
}
void ApplicationMain::ResetViewDistanceAndTarget(void)
{
	if(3<=vtx3d.size())
	{
		// Your code here >>

		// Your code here <<
	}
}
void ApplicationMain::SaveBinaryStl(void)
{
	// Save the extruded shape in extruded.stl
	// Your code here >>

	// Your code here <<
}

void ApplicationMain::CalculateNormal(void)
{
	nom3d.resize(vtx3d.size());
	for(int i=0; i+8<vtx3d.size(); i+=9) // Every (x1,y1,z1,x2,y2,z2,x3,y3,z3)
	{
		YsVec3 v1,v2,v3;
		v1.Set(vtx3d[i  ],vtx3d[i+1],vtx3d[i+2]);
		v2.Set(vtx3d[i+3],vtx3d[i+4],vtx3d[i+5]);
		v3.Set(vtx3d[i+6],vtx3d[i+7],vtx3d[i+8]);

		YsVec3 n=(v2-v1)^(v3-v1);
		n.Normalize();
		nom3d[i  ]=n.xf();
		nom3d[i+1]=n.yf();
		nom3d[i+2]=n.zf();
		nom3d[i+3]=n.xf();
		nom3d[i+4]=n.yf();
		nom3d[i+5]=n.zf();
		nom3d[i+6]=n.xf();
		nom3d[i+7]=n.yf();
		nom3d[i+8]=n.zf();
	}
}

int main(void)
{
	FsOpenWindow(0,0,800,600,1);
	ApplicationMain app;
	while(true!=app.MustTerminate())
	{
		FsPollDevice();
		app.RunOneStep();
		app.Draw();
	}
	return 0;
}
