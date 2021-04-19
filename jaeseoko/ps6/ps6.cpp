#include <fssimplewindow.h>
#include "ysclass.h"
#include <stdio.h>
#include <chrono>

#include <iostream>

// #ifdef min
// #undef min
// #endif
// #ifdef max
// #undef max
// #endif

// You can use fstream or stdio, whichever you like for writing a binary-stl.
// I have a feeling that it is easier to do with C standard library.



class ApplicationMain
{
private:
	bool term=false;
	std::vector <float> vtx2d;	// Clicked points.
	std::vector <float> col2d;	// Color for clicked points.  Make it all (0,0,0,1)

	double fovRadian= YsPi/6.0;  // 30 degrees;
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

	// Enable head light >>>>>>>>>>>>>>>>>>>>>>>>>>>>>

	void SetUpHeadLight(void) const;

	// Enable head light <<<<<<<<<<<<<<<<<<<<<<<<<<<<<
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
	// glTranslated(0,0,-300.0);
	YsMatrix4x4 modelView;
	modelView.Translate(0.0,0.0,-viewDistance);
	modelView*=viewRotation;
	modelView.Translate(-viewTarget);

	double glMat[16];
	modelView.GetOpenGlCompatibleMatrix(glMat);
	glMultMatrixd(glMat);
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
	// glEnable(GL_DEPTH_TEST);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0,wid,hei,0,-1,1);
	
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	// Enable lighting >>>>>>>>>>>>>>>>>>>>>>

	SetUpHeadLight();

	// Enable lighting <<<<<<<<<<<<<<<<<<<<<<

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
	float zFront = 100.0, zBack = -100.0;
	vtx3d.clear();
	col3d.clear();

	// Replace with your code here >>
	// vtx3d.push_back(   0.0);  vtx3d.push_back(   0.0);  vtx3d.push_back(0+zFront);
	// vtx3d.push_back( 500.0);  vtx3d.push_back(   0.0);  vtx3d.push_back(0+zFront);
	// vtx3d.push_back( 500.0);  vtx3d.push_back( 500.0);  vtx3d.push_back(0+zFront);

	// vtx3d.push_back( 500.0);  vtx3d.push_back( 500.0);  vtx3d.push_back(0+zBack);
	// vtx3d.push_back(   0.0);  vtx3d.push_back( 500.0);  vtx3d.push_back(0+zBack);
	// vtx3d.push_back(   0.0);  vtx3d.push_back(   0.0);  vtx3d.push_back(0+zBack);

	// col3d.push_back(0);col3d.push_back(0);col3d.push_back(1);col3d.push_back(1);
	// col3d.push_back(0);col3d.push_back(0);col3d.push_back(1);col3d.push_back(1);
	// col3d.push_back(0);col3d.push_back(0);col3d.push_back(1);col3d.push_back(1);
	// col3d.push_back(0);col3d.push_back(0);col3d.push_back(1);col3d.push_back(1);
	// col3d.push_back(0);col3d.push_back(0);col3d.push_back(1);col3d.push_back(1);
	// col3d.push_back(0);col3d.push_back(0);col3d.push_back(1);col3d.push_back(1);

	std::vector <float> vtxFront;
	std::vector <float> vtxBack;

	float cen[2] = {0,0};
	for(int i = 0; i<vtx2d.size()/2; ++i)
	{
		cen[0] += vtx2d[i*2];
		cen[1] += vtx2d[i*2 + 1];
	}
	auto nVtx2d = vtx2d.size()/2;
	cen[0]/=(float)nVtx2d;
	cen[1]/=(float)nVtx2d;

	// Make front and back faces with triangles.
	for(int i = 0; i+1<vtx2d.size(); i+=2)
	{	if(i==vtx2d.size()-2)
		{
			// Front triangle (Z = 100)
			vtx3d.push_back(cen[0]);	vtx3d.push_back(-cen[1]);		vtx3d.push_back(zFront);
			vtx3d.push_back(vtx2d[0]);	vtx3d.push_back(-vtx2d[1]);		vtx3d.push_back(zFront);
			vtx3d.push_back(vtx2d[i]);	vtx3d.push_back(-vtx2d[i+1]);	vtx3d.push_back(zFront);
			
			// Cache vertices excluding center in front vertices and use for filling sides.
			vtxFront.push_back(vtx2d[i]);	vtxFront.push_back(-vtx2d[i+1]);	vtxFront.push_back(zFront);
			vtxFront.push_back(vtx2d[0]);	vtxFront.push_back(-vtx2d[1]);		vtxFront.push_back(zFront);
			
			// Back triangle  (Z = -100)
			vtx3d.push_back(cen[0]);	vtx3d.push_back(-cen[1]);		vtx3d.push_back(zBack);
			vtx3d.push_back(vtx2d[i]);	vtx3d.push_back(-vtx2d[i+1]);	vtx3d.push_back(zBack);
			vtx3d.push_back(vtx2d[0]);	vtx3d.push_back(-vtx2d[1]);		vtx3d.push_back(zBack);

			// Cache vertices excluding center in back vertices and use for filling sides.
			vtxBack.push_back(vtx2d[i]);vtxBack.push_back(-vtx2d[i+1]);	vtxBack.push_back(zBack);
			vtxBack.push_back(vtx2d[0]);vtxBack.push_back(-vtx2d[1]);	vtxBack.push_back(zBack);
		}
		else
		{
			// Front triangle (Z = 100)
			vtx3d.push_back(cen[0]);	vtx3d.push_back(-cen[1]);		vtx3d.push_back(zFront);
			vtx3d.push_back(vtx2d[i+2]);vtx3d.push_back(-vtx2d[i+3]);	vtx3d.push_back(zFront);
			vtx3d.push_back(vtx2d[i]);	vtx3d.push_back(-vtx2d[i+1]);	vtx3d.push_back(zFront);
			

			// Cache vertices excluding center in front vertices and use for filling sides.
			vtxFront.push_back(vtx2d[i]);	vtxFront.push_back(-vtx2d[i+1]);	vtxFront.push_back(zFront);
			vtxFront.push_back(vtx2d[i+2]);	vtxFront.push_back(-vtx2d[i+3]);	vtxFront.push_back(zFront);
			
			// Back triangle  (Z = -100)
			vtx3d.push_back(cen[0]);		vtx3d.push_back(-cen[1]);		vtx3d.push_back(zBack);
			vtx3d.push_back(vtx2d[i]);		vtx3d.push_back(-vtx2d[i+1]);	vtx3d.push_back(zBack);
			vtx3d.push_back(vtx2d[i+2]);	vtx3d.push_back(-vtx2d[i+3]);	vtx3d.push_back(zBack);

			// Cache vertices excluding center in back vertices and use for filling sides.
			vtxBack.push_back(vtx2d[i]);	vtxBack.push_back(-vtx2d[i+1]);	vtxBack.push_back(zBack);
			vtxBack.push_back(vtx2d[i+2]);	vtxBack.push_back(-vtx2d[i+3]);	vtxBack.push_back(zBack);
		}

		// Both front and back faces set to Blue
		col3d.push_back(0);col3d.push_back(0);col3d.push_back(1);col3d.push_back(1);
		col3d.push_back(0);col3d.push_back(0);col3d.push_back(1);col3d.push_back(1);
		col3d.push_back(0);col3d.push_back(0);col3d.push_back(1);col3d.push_back(1);
		col3d.push_back(0);col3d.push_back(0);col3d.push_back(1);col3d.push_back(1);
		col3d.push_back(0);col3d.push_back(0);col3d.push_back(1);col3d.push_back(1);
		col3d.push_back(0);col3d.push_back(0);col3d.push_back(1);col3d.push_back(1);
	
	}

	// Make side faces between front and back. (Fill the Gap)

	int N = vtxFront.size(); 				// N = number of vertices(x,y,z) in polygon face.
	for(int i = 0; i+2 < N;i+=3)
	{
		if(i==N-3)
		{
			// Upper half triangle (One of the edges is from front face)
			vtx3d.push_back(vtxFront[i]);	vtx3d.push_back(vtxFront[i+1]);	vtx3d.push_back(vtxFront[i+2]);
			vtx3d.push_back(vtxFront[0]);	vtx3d.push_back(vtxFront[1]);	vtx3d.push_back(vtxFront[2]);
			vtx3d.push_back(vtxBack[i]);	vtx3d.push_back(vtxBack[i+1]);	vtx3d.push_back(vtxBack[i+2]);
			
			// Lower half triangle (One of the edges is from back face)
			vtx3d.push_back(vtxBack[i]);	vtx3d.push_back(vtxBack[i+1]);	vtx3d.push_back(vtxBack[i+2]);
			vtx3d.push_back(vtxFront[0]);	vtx3d.push_back(vtxFront[1]);	vtx3d.push_back(vtxFront[2]);
			vtx3d.push_back(vtxBack[0]);	vtx3d.push_back(vtxBack[1]);	vtx3d.push_back(vtxBack[2]);
			
		}
		else
		{
			// Upper half triangle (One of the edges is from front face)
			vtx3d.push_back(vtxFront[i]);	vtx3d.push_back(vtxFront[i+1]);	vtx3d.push_back(vtxFront[i+2]);
			vtx3d.push_back(vtxFront[i+3]);	vtx3d.push_back(vtxFront[i+4]);	vtx3d.push_back(vtxFront[i+5]);
			vtx3d.push_back(vtxBack[i]);	vtx3d.push_back(vtxBack[i+1]);	vtx3d.push_back(vtxBack[i+2]);
			
			// Lower half triangle (One of the edges is from back face)
			vtx3d.push_back(vtxBack[i]);	vtx3d.push_back(vtxBack[i+1]);	vtx3d.push_back(vtxBack[i+2]);
			vtx3d.push_back(vtxFront[i+3]);	vtx3d.push_back(vtxFront[i+4]);	vtx3d.push_back(vtxFront[i+5]);
			vtx3d.push_back(vtxBack[i+3]);	vtx3d.push_back(vtxBack[i+4]);	vtx3d.push_back(vtxBack[i+5]);
			
		}
		col3d.push_back(0);col3d.push_back(1);col3d.push_back(0);col3d.push_back(1);
		col3d.push_back(0);col3d.push_back(1);col3d.push_back(0);col3d.push_back(1);
		col3d.push_back(0);col3d.push_back(1);col3d.push_back(0);col3d.push_back(1);
		col3d.push_back(0);col3d.push_back(1);col3d.push_back(0);col3d.push_back(1);
		col3d.push_back(0);col3d.push_back(1);col3d.push_back(0);col3d.push_back(1);
		col3d.push_back(0);col3d.push_back(1);col3d.push_back(0);col3d.push_back(1);
		
	}

	// Replace with your code here <<

	CalculateNormal(); // Call this after you set triangles in vtx3d.
}
void ApplicationMain::ResetViewDistanceAndTarget(void)
{
	float bbx[2][3] , cen[3] = {0,0,0};
	if(3<=vtx3d.size())
	{
		// Your code here >>
		bbx[0][0] = vtx3d[0];		// min x
		bbx[0][1] = vtx3d[1];		// min y
		bbx[0][2] = vtx3d[2];		// min z
		bbx[1][0] = vtx3d[0];		// max x
		bbx[1][1] = vtx3d[1];		// max y
		bbx[1][2] = vtx3d[2];		// max z

		for(int i = 0; i< vtx3d.size()/3; ++i)
		{
			cen[0]+= vtx3d[i*3];		// center x sum
			cen[1]+= vtx3d[i*3+1];		// center y sum
			cen[2]+= vtx3d[i*3+2];		// center z sum
			bbx[0][0] = std::min(bbx[0][0],vtx3d[i*3]);
			bbx[0][1] = std::min(bbx[0][1],vtx3d[i*3+1]);
			bbx[0][2] = std::min(bbx[0][2],vtx3d[i*3+2]);
			bbx[1][0] = std::max(bbx[1][0],vtx3d[i*3]);
			bbx[1][1] = std::max(bbx[1][1],vtx3d[i*3+1]);
			bbx[1][2] = std::max(bbx[1][2],vtx3d[i*3+2]);
		}
		// # of vertices
		auto nVtx = vtx3d.size()/3;
		cen[0]/=(float)nVtx;							// center x = average of x
		cen[1]/=(float)nVtx;							// center y = average of y
		cen[2]/=(float)nVtx;							// center z = average of z
		viewTarget.Set(cen[0],cen[1],cen[2]);			// view target = center of object


		auto dx = bbx[1][0] - bbx[0][0];				// box size in x
		auto dy = bbx[1][1] - bbx[0][1];				// box size in y
		auto dz = bbx[1][2] - bbx[0][2];				// box size in z
		auto d = sqrt(dx*dx + dy*dy + dz*dz);			// box diagaonl distance
		viewDistance = (d/2.0) / sin(fovRadian/2.0);	// view distance from camera
// printf("view distance in ps6: %f\n",viewDistance);


		// Your code here <<
	}
}
void ApplicationMain::SaveBinaryStl(void)
{
	// Save the extruded shape in extruded.stl
	// Your code here >>

	uint32_t nTri = vtx3d.size()/9;
	// int nTri = vtx3d.size()/9;
	const char fName[] = "extruded.stl";
	char buffer[80] = 
	"This is the extruded shape of the click-drawing in STL Format.                 ";
	FILE *fp = fopen(fName,"wb");
							// Char takes 1 byte. 
							// Int and float takes 4 bytes

	fwrite(buffer,1,80,fp);	// writes 1 x 80 bytes
	fwrite(&nTri,1,4,fp);	// writes 4 byte for num triangles
	// printf("%d\n",nTri);

	char volumeId[2] ="0";
	for(int i = 0; i +8 < vtx3d.size(); i+=9)
	{
// printf("normals = %f,%f,%f\n",nom3d[i],nom3d[i+1],nom3d[i+2]);
// printf("first vertex in writing: %f,%f,%f\n",vtx3d[i],vtx3d[i+1],vtx3d[i+2]);
		float num[12] = {nom3d[i],nom3d[i+1],nom3d[i+2],
						 vtx3d[i],vtx3d[i+1],vtx3d[i+2],
						 vtx3d[i+3],vtx3d[i+4],vtx3d[i+5],
						 vtx3d[i+6],vtx3d[i+7],vtx3d[i+8]};
// printf("normals in float num[12] = %f,%f,%f\n",num[0],num[1],num[2]);
		
		fwrite(num,1,48,fp);
		
		fwrite(volumeId,1,2,fp);
	}

	fclose(fp);

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

// printf("normals in calculate normal: %f,%f,%f\n",nom3d[i],nom3d[i+1],nom3d[i+2]);
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
