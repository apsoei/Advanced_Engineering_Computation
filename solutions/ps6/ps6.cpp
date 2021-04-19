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

	// Do 3D Rendering here >>
	// Do 3D Rendering here <<

	glEnable(GL_DEPTH_TEST);


	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(fovDegree,(double)wid/(double)hei,viewDistance/10.0,viewDistance*3.0);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();


	// This is the correct timing to set up a head light (a light moves with the view point) >>
	// Also the light needs to be normalized.
	GLfloat lightDir[]={0,1/sqrt(2.0f),1/sqrt(2.0f),0};
	glLightfv(GL_LIGHT0,GL_POSITION,lightDir);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glEnable(GL_COLOR_MATERIAL);
	// This is the correct timing to set up a head light (a light moves with the view point) <<


	YsMatrix4x4 tfm;
	tfm.Translate(0.0,0.0,-viewDistance);
	tfm*=viewRotation;
	tfm.Translate(-viewTarget);

	double glTfm[16];
	tfm.GetOpenGlCompatibleMatrix(glTfm);
	glMultMatrixd(glTfm);

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

	int nPlg=vtx2d.size()/2;
	float cenX=0,cenY=0;
	for(int i=0; i+1<vtx2d.size(); i+=2)
	{
		cenX+= vtx2d[i];
		cenY+=-vtx2d[i+1];
	}
	cenX/=(float)nPlg;
	cenY/=(float)nPlg;


	vtx3d.clear();
	col3d.clear();
	for(int i=0; i+1<vtx2d.size(); i+=2)
	{
		float x0= vtx2d[i];
		float y0=-vtx2d[i+1];
		float x1= vtx2d[(i+2)%vtx2d.size()];
		float y1=-vtx2d[(i+3)%vtx2d.size()];

		// Front-side Triangle
		vtx3d.push_back(x0);  vtx3d.push_back(y0);  vtx3d.push_back(-100.0f);
		vtx3d.push_back(x1);  vtx3d.push_back(y1);  vtx3d.push_back(-100.0f);
		vtx3d.push_back(cenX);vtx3d.push_back(cenY);vtx3d.push_back(-100.0f);
		col3d.push_back(0);col3d.push_back(0);col3d.push_back(1);col3d.push_back(1);
		col3d.push_back(0);col3d.push_back(0);col3d.push_back(1);col3d.push_back(1);
		col3d.push_back(0);col3d.push_back(0);col3d.push_back(1);col3d.push_back(1);

		// Back-side Triangle
		vtx3d.push_back(x1);  vtx3d.push_back(y1);  vtx3d.push_back( 100.0f);
		vtx3d.push_back(x0);  vtx3d.push_back(y0);  vtx3d.push_back( 100.0f);
		vtx3d.push_back(cenX);vtx3d.push_back(cenY);vtx3d.push_back( 100.0f);
		col3d.push_back(0);col3d.push_back(0);col3d.push_back(1);col3d.push_back(1);
		col3d.push_back(0);col3d.push_back(0);col3d.push_back(1);col3d.push_back(1);
		col3d.push_back(0);col3d.push_back(0);col3d.push_back(1);col3d.push_back(1);

		// Two Side Triangles
		vtx3d.push_back(x1);  vtx3d.push_back(y1);  vtx3d.push_back(-100.0f);
		vtx3d.push_back(x0);  vtx3d.push_back(y0);  vtx3d.push_back(-100.0f);
		vtx3d.push_back(x0);  vtx3d.push_back(y0);  vtx3d.push_back( 100.0f);
		col3d.push_back(0);col3d.push_back(1);col3d.push_back(0);col3d.push_back(1);
		col3d.push_back(0);col3d.push_back(1);col3d.push_back(0);col3d.push_back(1);
		col3d.push_back(0);col3d.push_back(1);col3d.push_back(0);col3d.push_back(1);

		vtx3d.push_back(x0);  vtx3d.push_back(y0);  vtx3d.push_back( 100.0f);
		vtx3d.push_back(x1);  vtx3d.push_back(y1);  vtx3d.push_back( 100.0f);
		vtx3d.push_back(x1);  vtx3d.push_back(y1);  vtx3d.push_back(-100.0f);
		col3d.push_back(0);col3d.push_back(1);col3d.push_back(0);col3d.push_back(1);
		col3d.push_back(0);col3d.push_back(1);col3d.push_back(0);col3d.push_back(1);
		col3d.push_back(0);col3d.push_back(1);col3d.push_back(0);col3d.push_back(1);
	}

	CalculateNormal(); // Call this after you set triangles in vtx3d.
}
void ApplicationMain::ResetViewDistanceAndTarget(void)
{
	if(3<=vtx3d.size())
	{
		float minx=vtx3d[0],miny=vtx3d[1],minz=vtx3d[2];
		float maxx=vtx3d[0],maxy=vtx3d[1],maxz=vtx3d[2];
		for(int i=0; i+2<vtx3d.size(); i+=3)
		{
			minx=std::min(minx,vtx3d[i]);
			miny=std::min(miny,vtx3d[i+1]);
			minz=std::min(minz,vtx3d[i+2]);
			maxx=std::max(maxx,vtx3d[i]);
			maxy=std::max(maxy,vtx3d[i+1]);
			maxz=std::max(maxz,vtx3d[i+2]);
		}
		viewTarget.Set((minx+maxx)/2.0f,(miny+maxy)/2.0f,(minz+maxz)/2.0f);

		double dx=maxx-minx;
		double dy=maxy-miny;
		double dz=maxz-minz;
		double d=sqrt(dx*dx+dy*dy+dz*dz);
		viewDistance=(d/2.0)/sin(fovRadian/2);
	}
}
void ApplicationMain::SaveBinaryStl(void)
{
	unsigned char buffer[80];
	for(auto &b : buffer)
	{
		b=0;
	}

	FILE *fp=fopen("extruded.stl","wb");
	if(nullptr!=fp)
	{
		fwrite(buffer,1,80,fp); // 80 bytes.  Comment

		unsigned int nTri=vtx3d.size()/9;
		fwrite(&nTri,1,4,fp);

		for(unsigned int i=0; i<nTri; ++i)
		{
			*(float *)(buffer   )=nom3d[i*9  ];
			*(float *)(buffer+ 4)=nom3d[i*9+1];
			*(float *)(buffer+ 8)=nom3d[i*9+2];

			*(float *)(buffer+12)=vtx3d[i*9];
			*(float *)(buffer+16)=vtx3d[i*9+1];
			*(float *)(buffer+20)=vtx3d[i*9+2];
			*(float *)(buffer+24)=vtx3d[i*9+3];
			*(float *)(buffer+28)=vtx3d[i*9+4];
			*(float *)(buffer+32)=vtx3d[i*9+5];
			*(float *)(buffer+36)=vtx3d[i*9+6];
			*(float *)(buffer+40)=vtx3d[i*9+7];
			*(float *)(buffer+44)=vtx3d[i*9+8];

			buffer[48]=0;
			buffer[49]=0;
			fwrite(buffer,1,50,fp);
		}

		fclose(fp);
	}
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
