#include <fssimplewindow.h>
#include "ysglfontdata.h"
#include <vector>
#include <chrono>
#include <ysclass.h>
#include <iostream>
#include <stdlib.h>

#include "mesh.h"
#include "glutil.h"
#include "cube.h"
#include <fstream>



class ApplicationMain
{
private:
	bool term=false;
    bool inBox = false;

	const double fovDeg=30.0;
	const double fovRad=YsPi/6.0;

	PolygonalMesh mesh;
	mutable std::vector <float> vtx3d,col3d,nom3d;

	std::vector <float> lineVtx,lineCol;
	PolygonalMesh::VertexHandle lastPickedVtHd;
	std::vector <float> neiVtx,neiVtxCol;
    
    ////////////////////////////////////

    std::vector <float> sameNomVtx,sameNomCol;
    YsVec3 pickedNom;

    ////////////////////////////////////

	double viewDistance=40.0;
    double originalDistance;
	YsMatrix3x3 viewRotation;
	YsVec3 viewTarget;
	decltype(std::chrono::high_resolution_clock::now()) lastT;

	void MouseToLine(YsVec3 line[2],int mx,int my) const;
	YsMatrix4x4 GetModelView(void) const;
	void GetNearFar(double &nearz,double &farz) const;

	PolygonalMesh::PolygonHandle PickedPlHd(int mx,int my) const;
	PolygonalMesh::VertexHandle PickedVtHd(int mx,int my) const;


    // Draw "Convert" button >>>>>>>>>>>>>>>>>>

    std::vector <float> vtx2d;	
    std::vector <float> col2d;
    std::vector <float> inCol2d;
    float x1,y1,x2,y2;

    // Draw "Convert" button <<<<<<<<<<<<<<<<<<

    // Make 3D cube at the Corner. >>>>>>>>>>>>>>>>>>
    Cube cube;
    
    std::vector <float> cubeVtx3d;
	std::vector <float> cubeNom3d;
    std::vector <float> cubeCol3d;
    // std::vector <float> boundNom3d;

    // Make 3D cube at the Corner. <<<<<<<<<<<<<<<<<<

public:
	ApplicationMain(int argc,char *argv[]);

	bool LoadSTL(const char fName[]);
    ///////////////////////////////////////////////////////////////

    bool OpenSTL(std::vector <float> &vtx,std::vector <float> &nom,const char fName[]);


    ///////////////////////////////////////////////////////////////
	void RemakeVertexArray(void);
	void WriteShapeToText(std::vector <float> twoDvtx);
	bool MustTerminate(void) const;
	void RunOneStep(void);
	void SetUpHeadLight(void) const;
	void Draw(void) const;

	//Addition for surface and outer edge extraction
	std::vector <float> mouse_nom, col3d, surface;
	void GetSameNormals(mutable std::vector <float> vtx3d, mutable std::vector <float> nom3d, 
		                mutable std::vector <float> col3d, PolygonalMesh::VertexHandle vtHd);
	bool Compare_Vectors(std::vector<float> vtx1, std::vector<float> vtx2, std::vector<float> surface, int NumTri, int Indx);
	void GetShape(std::vector <float> surface);
	//************************************************
};




void ApplicationMain::MouseToLine(YsVec3 line[2],int mx,int my) const
{
	int winWid,winHei;
	FsGetWindowSize(winWid,winHei);
	auto viewport=WindowToViewPort(winWid,winHei,mx,my);

	double aspect=(double)winWid/(double)winHei;

	auto projMat=MakePerspective(fovRad,aspect,viewDistance/10.0,viewDistance*10.0);
	projMat.Invert();

	line[0]=viewport;
	line[1]=viewport;

	line[0].SetZ(-1.0);
	line[1].SetZ( 1.0);

	line[0]=projMat*line[0];
	line[1]=projMat*line[1];

	auto modelView=GetModelView();
	modelView.Invert();

	line[0]=modelView*line[0];
	line[1]=modelView*line[1];
}

YsMatrix4x4 ApplicationMain::GetModelView(void) const
{
	YsMatrix4x4 modelView;
	modelView.Translate(0.0,0.0,-viewDistance);
	modelView*=viewRotation;
	modelView.Translate(-viewTarget);
	return modelView;
}

void ApplicationMain::GetNearFar(double &nearz,double &farz) const
{
	nearz=viewDistance*0.1;
	farz=viewDistance*10.0;
}

PolygonalMesh::PolygonHandle ApplicationMain::PickedPlHd(int mx,int my) const
{
	PolygonalMesh::PolygonHandle picked=mesh.NullPolygon();
	double pickedZ=0.0,nearz,farz;

	YsVec3 line[2];
	MouseToLine(line,mx,my);
std::cout << "current mx = " << mx << std::endl;
std::cout << "current my = " << my << std::endl;

	auto modelView=GetModelView();
	GetNearFar(nearz,farz);

	for(auto plHd=mesh.FirstPolygon(); mesh.NullPolygon()!=plHd; mesh.MoveToNextPolygon(plHd))
	{
		std::vector <YsVec3> plVtPos;
		for(auto vtHd : mesh.GetPolygonVertex(plHd))
		{
			plVtPos.push_back(mesh.GetVertexPosition(vtHd));
		}

		YsPlane pln;
		if(YSOK==pln.MakeBestFitPlane(plVtPos.size(),plVtPos.data()))
		{
			YsVec3 itsc;
			if(YSOK==pln.GetPenetration(itsc,line[0],line[1]))
			{
				auto side=YsCheckInsidePolygon3(itsc,plVtPos.size(),plVtPos.data());
				if(YSBOUNDARY==side || YSINSIDE==side)
				{
					itsc=modelView*itsc;
					if(itsc.z()<=-nearz)
					{
						if(itsc.z()>pickedZ || picked==mesh.NullPolygon())
						{
							pickedZ=itsc.z();
							picked=plHd;
						}
					}
				}
			}
		}
        // pickedNom = picked.plgPtr->nom;
	}
    
	return picked;
}

PolygonalMesh::VertexHandle ApplicationMain::PickedVtHd(int mx,int my) const
{
	int winWid,winHei;
	FsGetWindowSize(winWid,winHei);

	PolygonalMesh::VertexHandle picked=mesh.NullVertex();

	double pickedZ=0.0,nearz,farz;
	auto modelView=GetModelView();

	GetNearFar(nearz,farz);

	double aspect=(double)winWid/(double)winHei;
	auto projection=MakePerspective(fovRad,aspect,nearz,farz);

	auto tfm=projection*modelView;

	for(auto vtHd=mesh.FirstVertex(); mesh.NullVertex()!=vtHd; mesh.MoveToNextVertex(vtHd))
	{
		auto vtPos=mesh.GetVertexPosition(vtHd);
		vtPos=tfm*vtPos;
		auto winPos=ViewPortToWindow(winWid,winHei,vtPos);

		int dx=winPos.x()-mx;
		int dy=winPos.y()-my;
		if(-8<=dx && dx<=8 && -8<=dy && dy<=8)
		{
			if(mesh.NullVertex()==picked || vtPos.z()<pickedZ)
			{
				pickedZ=vtPos.z();
				picked=vtHd;
			}
		}
	}

	return picked;
}

ApplicationMain::ApplicationMain(int argc,char *argv[])
{
    
	viewTarget.Set(0.0,0.0,0.0);
	lastPickedVtHd=mesh.NullVertex();
	if(2<=argc)
	{
		// LoadSTL(argv[1]);
        OpenSTL(vtx3d,nom3d,argv[1]);

	}


    // Draw "Convert" button >>>>>>>>>>>>>>>>>>
    int wid,hei;
    FsGetWindowSize(wid,hei);
    float w = 100.0, h = 50.0;
    x1 = wid - w - 40.0;
    x2 = wid - 40.0;
    y1 = hei - h - 40.0;
    y2 = hei - 40.0;

    vtx2d.push_back(x1);vtx2d.push_back(y1);
    vtx2d.push_back(x2);vtx2d.push_back(y1);
    vtx2d.push_back(x2);vtx2d.push_back(y2);
    vtx2d.push_back(x1);vtx2d.push_back(y2);

    // color when mouse is NOT inside the "convert" box
    col2d.push_back(0);col2d.push_back(0);col2d.push_back(0);col2d.push_back(1);
    col2d.push_back(0);col2d.push_back(0);col2d.push_back(0);col2d.push_back(1);

    col2d.push_back(0);col2d.push_back(0);col2d.push_back(0);col2d.push_back(1);
    col2d.push_back(0);col2d.push_back(0);col2d.push_back(0);col2d.push_back(1);

    // color when mouse is inside the "convert" box
    inCol2d.push_back(1);inCol2d.push_back(0);inCol2d.push_back(0);inCol2d.push_back(1);
    inCol2d.push_back(0);inCol2d.push_back(1);inCol2d.push_back(0);inCol2d.push_back(1);
    inCol2d.push_back(0);inCol2d.push_back(0);inCol2d.push_back(1);inCol2d.push_back(1);
    inCol2d.push_back(1);inCol2d.push_back(1);inCol2d.push_back(0);inCol2d.push_back(1);

    // Draw "Convert" button <<<<<<<<<<<<<<<<<<

	// Make 3D cube >>>>>>

	cube.MakeBlock(cubeVtx3d,cubeNom3d,cubeCol3d,-0.5f,-0.5f,-0.5f,0.5f,0.5f,0.5f);

	// Make 3D cube <<<<<<
}

bool ApplicationMain::LoadSTL(const char fName[])
{
	if(true==mesh.LoadBinSTL(fName))
	{
		auto cen=mesh.GetCenter();
		YsVec3 bbx[2];
		mesh.GetBoundingBox(bbx);

		viewTarget=cen;
		auto d=(bbx[1]-bbx[0]).GetLength();
		viewDistance=(d/2.0)/sin(fovRad/2.0);
        originalDistance = viewDistance;
		RemakeVertexArray();

		return true;
	}
	return false;
}

bool ApplicationMain::OpenSTL(std::vector <float> &vtx,std::vector <float> &nom,const char fName[])
{
    if(true==mesh.OpenSTL(vtx3d,nom3d,fName))
	{
		auto cen=mesh.GetCenter();
		YsVec3 bbx[2];
		mesh.GetBoundingBox(bbx);

		viewTarget=cen;
		auto d=(bbx[1]-bbx[0]).GetLength();
		viewDistance=(d/2.0)/sin(fovRad/2.0);
        originalDistance = viewDistance;
		RemakeVertexArray();

		return true;
	}
	return false;
}

void ApplicationMain::RemakeVertexArray(void)
{
	vtx3d.clear();
	col3d.clear();
	nom3d.clear();
	for(auto plHd=mesh.FirstPolygon(); mesh.NullPolygon()!=plHd; mesh.MoveToNextPolygon(plHd))
	{
		auto plVtHd=mesh.GetPolygonVertex(plHd);
		if(3<=plVtHd.size())
		{
			auto nom=mesh.GetNormal(plHd);
			const YsVec3 tri[3]=
			{
				mesh.GetVertexPosition(plVtHd[0]),
				mesh.GetVertexPosition(plVtHd[1]),
				mesh.GetVertexPosition(plVtHd[2]),
			};

			vtx3d.push_back(tri[0].xf());vtx3d.push_back(tri[0].yf());vtx3d.push_back(tri[0].zf());
			vtx3d.push_back(tri[1].xf());vtx3d.push_back(tri[1].yf());vtx3d.push_back(tri[1].zf());
			vtx3d.push_back(tri[2].xf());vtx3d.push_back(tri[2].yf());vtx3d.push_back(tri[2].zf());

			nom3d.push_back(nom.xf());nom3d.push_back(nom.yf());nom3d.push_back(nom.zf());
			nom3d.push_back(nom.xf());nom3d.push_back(nom.yf());nom3d.push_back(nom.zf());
			nom3d.push_back(nom.xf());nom3d.push_back(nom.yf());nom3d.push_back(nom.zf());

			float col[4];
			mesh.GetPolygonColor(col,plHd);
			col3d.push_back(col[0]);col3d.push_back(col[1]);col3d.push_back(col[2]);col3d.push_back(col[3]);
			col3d.push_back(col[0]);col3d.push_back(col[1]);col3d.push_back(col[2]);col3d.push_back(col[3]);
			col3d.push_back(col[0]);col3d.push_back(col[1]);col3d.push_back(col[2]);col3d.push_back(col[3]);
		}
	}
}

void ApplicationMain::WriteShapeToText(std::vector <float> twoDvtx)
{
	// Shape vector is (x1, y1, z1, x2, y2, z2, x2, y2, z2, x3, y3, z3 ...etc) points are double listed
	// Should add user input for filename
	// Should add file check to prevent overwrite
	std::ofstream f("Matlab_output.txt");
	int count = 1;

	for (const auto& coord : twoDvtx)
	{
		f << coord << " ";
		if (count % 6 == 0)
			f << std::endl;
		count++;
	}

	f.close();
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
	if(FSKEY_X==key && mesh.NullVertex()!=lastPickedVtHd)
	{
		auto vtPos=mesh.GetVertexPosition(lastPickedVtHd);
		vtPos.AddX(1.0);
		mesh.SetVertexPosition(lastPickedVtHd,vtPos);
		RemakeVertexArray();
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
    if(FsGetKeyState(FSKEY_I))
    {
        viewDistance-=0.02*viewDistance;
    }
    if(FsGetKeyState(FSKEY_O))
    {
        viewDistance+=0.02*viewDistance;
    }
    if(FsGetKeyState(FSKEY_SPACE))
    {
        viewDistance = originalDistance;
    }
    

	int lb,mb,rb,mx,my;
	auto evt=FsGetMouseEvent(lb,mb,rb,mx,my);
	if(FSMOUSEEVENT_LBUTTONDOWN==evt)
	{
		// YsVec3 line[2];
		// MouseToLine(line,mx,my);


		// lineVtx.clear();
		// lineCol.clear();

		// lineVtx.push_back(line[0].x());
		// lineVtx.push_back(line[0].y());
		// lineVtx.push_back(line[0].z());
		// lineVtx.push_back(line[1].x());
		// lineVtx.push_back(line[1].y());
		// lineVtx.push_back(line[1].z());
		// lineCol.push_back(1);lineCol.push_back(0);lineCol.push_back(0);lineCol.push_back(1);
		// lineCol.push_back(1);lineCol.push_back(0);lineCol.push_back(0);lineCol.push_back(1);

		auto picked=PickedPlHd(mx,my);
		std::cout << "P " << mesh.GetSearchKey(picked) << std::endl;

		lastPickedVtHd=PickedVtHd(mx,my);
		std::cout << "V " << mesh.GetSearchKey(lastPickedVtHd) << std::endl;

		if(mesh.NullVertex()!=lastPickedVtHd)
		{
			neiVtx.clear();
			neiVtxCol.clear();

			auto vtPos=mesh.GetVertexPosition(lastPickedVtHd);
			neiVtx.push_back(vtPos.xf());
			neiVtx.push_back(vtPos.yf());
			neiVtx.push_back(vtPos.zf());

			neiVtxCol.push_back(0); neiVtxCol.push_back(1); neiVtxCol.push_back(1); neiVtxCol.push_back(1);

			for(auto vtHd : mesh.GetConnectedVertex(lastPickedVtHd))
			{
				auto vtPos=mesh.GetVertexPosition(vtHd);
				neiVtx.push_back(vtPos.xf());
				neiVtx.push_back(vtPos.yf());
				neiVtx.push_back(vtPos.zf());

				neiVtxCol.push_back(0); neiVtxCol.push_back(1); neiVtxCol.push_back(1); neiVtxCol.push_back(1);
			}
            
		}

		float red[4]={1,0,0,1};
		mesh.SetPolygonColor(picked,red);
		RemakeVertexArray();
	}
    if(mx>x1 && mx < x2 &&my >y1 &&my <y2)
    {
        inBox = true;
		//WriteShapeToText(testShape) //need to make test case
    }
    else inBox = false;
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

	double glMat[16];
	int wid,hei;
	FsGetWindowSize(wid,hei);
	double aspect=(double)wid/(double)hei;

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	double nearz,farz;
	GetNearFar(nearz,farz);
	auto projMat=MakePerspective(fovRad,aspect,nearz,farz);
	projMat.GetOpenGlCompatibleMatrix(glMat);
	glMultMatrixd(glMat);


	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	SetUpHeadLight();

	/* In a traditional OpenGL it could be:
	glTranslated(0.0,0.0,-40.0);
	glRotated ....
	glTranslated(centerize the object);
	*/

	auto modelView=GetModelView();

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

	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_COLOR_ARRAY);
	glVertexPointer(3,GL_FLOAT,0,lineVtx.data());
	glColorPointer(4,GL_FLOAT,0,lineCol.data());
	glDrawArrays(GL_LINES,0,lineVtx.size()/3);

	glVertexPointer(3,GL_FLOAT,0,neiVtx.data());
	glColorPointer(4,GL_FLOAT,0,neiVtxCol.data());
	glPointSize(8.0);
	glDrawArrays(GL_POINTS,0,neiVtx.size()/3);

	glDisableClientState(GL_VERTEX_ARRAY);
	glDisableClientState(GL_COLOR_ARRAY);

	// 3D cube at the Corner.>>>>>
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	// double nearz,farz;
	// GetNearFar(nearz,farz);
	auto proj = MakeOrthogonal(-10,1,-11,2,-2,2);
	proj.GetOpenGlCompatibleMatrix(glMat);
	glMultMatrixd(glMat);


	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	SetUpHeadLight();

	viewRotation.GetOpenGlCompatibleMatrix(glMat);
	glMultMatrixd(glMat);

	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_NORMAL_ARRAY);
	glEnableClientState(GL_COLOR_ARRAY);
	glColorPointer(4,GL_FLOAT,0,cubeCol3d.data());
	glVertexPointer(3,GL_FLOAT,0,cubeVtx3d.data());
	glNormalPointer(GL_FLOAT,0,cubeNom3d.data());
	glDrawArrays(GL_TRIANGLES,0,cubeVtx3d.size()/3);
	glDisableClientState(GL_VERTEX_ARRAY);
	glDisableClientState(GL_NORMAL_ARRAY);
	glDisableClientState(GL_COLOR_ARRAY);

	// 3D cube at the Corner. <<<<<<<<<<
	




    // Draw "Convert" button >>>>>>>>>>>>>>>>>>
    // glDisable(GL_DEPTH_TEST);
    glDisable(GL_DEPTH_TEST);
	// glEnable(GL_DEPTH_TEST);
    glShadeModel(GL_SMOOTH);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0,wid,hei,0,-1,1);
	
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

    glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_COLOR_ARRAY);
    if(false==inBox)
    {
        glColorPointer(4,GL_FLOAT,0,col2d.data());
    }
    else
    {
        glColorPointer(4,GL_FLOAT,0,inCol2d.data());
    }
	
	glVertexPointer(2,GL_FLOAT,0,vtx2d.data());
	glDrawArrays(GL_LINE_LOOP,0,vtx2d.size()/2); 
	glDisableClientState(GL_VERTEX_ARRAY);
	glDisableClientState(GL_COLOR_ARRAY);

    glRasterPos2i(x1+8,y1+30);
    char str[256];
    sprintf(str,"CONVERT");
    YsGlDrawFontBitmap12x16(str);
    // Draw "Convert" button <<<<<<<<<<<<<<<<<<



    // Draw "instructions" >>>>>>>>>>>>>>>>>>>>

    glRasterPos2i(14,25);
    char instructions[256];
    sprintf(instructions,"ESC: exit | arrow keys: rotate | I: zoom + | O: zoom - | Space: original");
    YsGlDrawFontBitmap12x16(instructions);

    // Draw "instructions" <<<<<<<<<<<<<<<<<<<<
	FsSwapBuffers();
}




//Addition of function for surface and outer edge extraction ***********************************
void ApplicationMain::GetSameNormals(mutable std::vector <float> vtx3d, mutable std::vector <float> nom3d,
	mutable std::vector <float> col3d, PolygonalMesh::VertexHandle vtHd) //Input: Vertices, normals, and mouse clicked triangle normal 
{
	//reset color
	col3d.clear();
	surface.clear();

	//Find all triangles with same NX NY NZ
	int NumVtc = nom3d.size();
	//Initialize the vector to store all triangles with the same normal
	std::vector <float> surface;
	for (int i = 0; i < NumVtc; i += 9)//not the end of vector?
	{
		//Compare all normals to be less than epsilon value
		if (abs(mouse_nom[0] - nom[i]) < 0.01 && abs(mouse_nom[1] - nom[i + 1]) < 0.01 && abs(mouse_nom[2] - nom[i + 2]) < 0.01)
		{
			//store triangles vertices in surface vector 
			surface.push_back(vtx3d[i]); surface.push_back(vtx3d[i + 1]); surface.push_back(vtx3d[i + 2]);
			surface.push_back(vtx3d[i + 3]); surface.push_back(vtx3d[i + 4]); surface.push_back(vtx3d[i + 5]);
			surface.push_back(vtx3d[i + 6]); surface.push_back(vtx3d[i + 7]); surface.push_back(vtx3d[i + 8]);

			//****Set up color??************
			//give new color
			col3d.push_back(0); col3d.push_back(1); col3d.push_back(0);
			col3d.push_back(0); col3d.push_back(1); col3d.push_back(0);
			col3d.push_back(0); col3d.push_back(1); col3d.push_back(0);
		}
		else
		{
			//color for other normals
			col3d.push_back(0); col3d.push_back(0); col3d.push_back(1);
			col3d.push_back(0); col3d.push_back(0); col3d.push_back(1);
			col3d.push_back(0); col3d.push_back(0); col3d.push_back(1);
		}

	}
	printf("Surface vertices: \n");
	for (int i = 0; i < surface.size(); i += 3)
	{
		printf("(X,Y,Z) = (%f, %f, %f)\n", surface[i], surface[i + 1], surface[i + 2]);
	}
	printf("\n");
	GetShape(surface);

	//return surface;
}

bool ApplicationMain::Compare_Vectors(std::vector<float> vtx1, std::vector<float> vtx2,
	std::vector<float> surface, int NumTri, int Indx)
{
	printf("Vector from (%f, %f, %f) to (%f, %f, %f)\n", vtx1[0], vtx1[1], vtx1[2], vtx2[0], vtx2[1], vtx2[2]);
	float vctx = vtx1[0] - vtx2[0];
	float vcty = vtx1[1] - vtx2[1];
	float vctz = vtx1[2] - vtx2[2];
	float vct1_x, vct1_y, vct1_z, vct2_x, vct2_y, vct2_z, vct3_x, vct3_y, vct3_z;
	int count = 0;

	printf("vec_xyz = (%f, %f, %f)\n", vctx, vcty, vctz);


	for (int j = 0; j < NumTri; j += 9)
	{
		//add check to not compare the same triangle
		if (j != Indx)
		{
			//Create vectors with triangle vertices 
			vct1_x = surface[j] - surface[j + 3];
			vct1_y = surface[j + 1] - surface[j + 4];
			vct1_z = surface[j + 2] - surface[j + 5];

			vct2_x = surface[j + 3] - surface[j + 6];
			vct2_y = surface[j + 4] - surface[j + 7];
			vct2_z = surface[j + 5] - surface[j + 8];

			vct3_x = surface[j + 6] - surface[j];
			vct3_y = surface[j + 7] - surface[j + 1];
			vct3_z = surface[j + 8] - surface[j + 2];

			printf("vec_1 = (%f, %f, %f)\n", vct1_x, vct1_y, vct1_z);
			printf("vec_2 = (%f, %f, %f)\n", vct2_x, vct2_y, vct2_z);
			printf("vec_3 = (%f, %f, %f)\n", vct3_x, vct3_y, vct3_z);
			//Compare all triangle vectors with calculated vectors 
			if (vctx == vct1_x && vcty == vct1_y && vctz == vct1_z)
			{
				//If the same vector in equal or opposite direction exist return false
				if (vtx1[0] == surface[j] && vtx1[1] == surface[j + 1] && vtx1[2] == surface[j + 2])
				{
					printf("False on 1.1\n");
					return false;
				}
				if (vtx1[0] == surface[j + 3] && vtx1[1] == surface[j + 4] && vtx1[2] == surface[j + 5])
				{
					printf("False on 1.2\n");
					return false;
				}

			}
			else if (vctx == vct2_x && vcty == vct2_y && vctz == vct2_z)
			{
				//If the same vector in equal or opposite direction exist return false
				if (vtx1[0] == surface[j + 3] && vtx1[1] == surface[j + 4] && vtx1[2] == surface[j + 5])
				{
					printf("False on 2.1\n");
					return false;
				}
				if (vtx1[0] == surface[j + 6] && vtx1[1] == surface[j + 7] && vtx1[2] == surface[j + 8])
				{
					printf("False on 2.2\n");
					return false;
				}

			}
			else if (vctx == vct3_x && vcty == vct3_y && vctz == vct3_z)
			{
				//If the same vector in equal or opposite direction exist return false
				if (vtx1[0] == surface[j + 6] && vtx1[1] == surface[j + 7] && vtx1[2] == surface[j + 8])
				{
					printf("False on 3.1\n");
					return false;
				}
				if (vtx1[0] == surface[j + 0] && vtx1[1] == surface[j + 1] && vtx1[2] == surface[j + 2])
				{
					printf("False on 3.2\n");
					return false;
				}

			}
			else if (vctx == -vct1_x && vcty == -vct1_y && vctz == -vct1_z)
			{
				//If the same vector in equal or opposite direction exist return false

				if (vtx1[0] == surface[j] && vtx1[1] == surface[j + 1] && vtx1[2] == surface[j + 2])
				{
					printf("False on 4.1\n");
					return false;
				}
				if (vtx1[0] == surface[j + 3] && vtx1[1] == surface[j + 4] && vtx1[2] == surface[j + 5])
				{
					printf("False on 4.2\n");
					return false;
				}


			}
			else if (vctx == -vct2_x && vcty == -vct2_y && vctz == -vct2_z)
			{
				//If the same vector in equal or opposite direction exist return false
				if (vtx1[0] == surface[j + 3] && vtx1[1] == surface[j + 4] && vtx1[2] == surface[j + 5])
				{
					printf("False on 5.1\n");
					return false;
				}
				if (vtx1[0] == surface[j + 6] && vtx1[1] == surface[j + 7] && vtx1[2] == surface[j + 8])
				{
					printf("False on 5.2\n");
					return false;
				}

			}
			else if (vctx == -vct3_x && vcty == -vct3_y && vctz == -vct3_z)
			{
				//If the same vector in equal or opposite direction exist return false
				if (vtx1[0] == surface[j + 6] && vtx1[1] == surface[j + 7] && vtx1[2] == surface[j + 8])
				{
					printf("False on 6.1\n");
					return false;
				}
				if (vtx1[0] == surface[j + 0] && vtx1[1] == surface[j + 1] && vtx1[2] == surface[j + 2])
				{
					printf("False on 6.2\n");
					return false;
				}

			}
		}
	}

	return true;//Return true if the given vertices create a unique vector on the surface
}

void ApplicationMain::GetShape(std::vector <float> surface)//Get unique vectors of Same Normals
{
	//Initialize 2D Shape Vector
	std::vector <float> twoDvtx;
	std::vector <float> vec1, vec2, vec3;
	vec1.push_back(0.0); vec1.push_back(0.0); vec1.push_back(0.0);
	vec2.push_back(0.0); vec2.push_back(0.0); vec2.push_back(0.0);
	vec3.push_back(0.0); vec3.push_back(0.0); vec3.push_back(0.0);
	//********Need to differetiate which 2D vectors to store here
	int NumTri = surface.size();

	//for all triangles

	for (int i = 0; i < NumTri; i += 9)
	{
		vec1[0] = surface[i];     vec1[1] = surface[i + 1]; vec1[2] = surface[i + 2];
		vec2[0] = surface[i + 3]; vec2[1] = surface[i + 4]; vec2[2] = surface[i + 5];
		vec3[0] = surface[i + 6]; vec3[1] = surface[i + 7]; vec3[2] = surface[i + 8];

		printf("vec1 = (%f, %f, %f)\n", vec1[0], vec1[1], vec1[2]);
		printf("vec2 = (%f, %f, %f)\n", vec2[0], vec2[1], vec2[2]);
		printf("vec3 = (%f, %f, %f)\n", vec3[0], vec3[1], vec3[2]);

		if (true == Compare_Vectors(vec1, vec2, surface, NumTri, i))
		{
			//store unique vector
			printf("True on first\n");
			twoDvtx.push_back(vec1[0]); twoDvtx.push_back(vec1[1]); twoDvtx.push_back(vec1[2]);
			twoDvtx.push_back(vec2[0]); twoDvtx.push_back(vec2[1]); twoDvtx.push_back(vec2[2]);

		}
		if (true == Compare_Vectors(vec2, vec3, surface, NumTri, i))
		{
			//store unique vector
			printf("True on second\n");
			twoDvtx.push_back(vec2[0]); twoDvtx.push_back(vec2[1]); twoDvtx.push_back(vec2[2]);
			twoDvtx.push_back(vec3[0]); twoDvtx.push_back(vec3[1]); twoDvtx.push_back(vec3[2]);
		}
		if (true == Compare_Vectors(vec1, vec3, surface, NumTri, i))
		{
			//store unique vector
			printf("True on third\n");
			twoDvtx.push_back(vec1[0]); twoDvtx.push_back(vec1[1]); twoDvtx.push_back(vec1[2]);
			twoDvtx.push_back(vec3[0]); twoDvtx.push_back(vec3[1]); twoDvtx.push_back(vec3[2]);
		}
	}

	printf("2D Vtx: Size = %d\n", twoDvtx.size());
	for (int i = 0; i < twoDvtx.size(); i += 3)
	{
		printf("(X,Y,Z) = (%f, %f, %f)\n", twoDvtx[i], twoDvtx[i + 1], twoDvtx[i + 2]);
	}
	printf("\n");
	//return twoDvtx;
}

//**********************************************************************************************



int main(int argc,char *argv[])
{
	FsOpenWindow(0,0,900,800,1);
	ApplicationMain app(argc,argv);
	while(true!=app.MustTerminate())
	{
		FsPollDevice();
		app.RunOneStep();
		app.Draw();
	}
	return 0;
}
