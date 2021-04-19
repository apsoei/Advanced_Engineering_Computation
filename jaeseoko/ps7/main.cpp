#include <vector>
#include <thread>
#include <stdio.h>

#include <ysclass.h>
#include <ysshellext.h>
#include "meshlattice.h"

#include "fssimplewindow.h"

#include "glutil.h"
#include "ps7lib.h"

class ApplicationMain
{
protected:
	// Add necessary member variables

	enum STATE
	{
		STATE_NORMAL,
		STATE_SLICE,
		STATE_SCANNER
	};
	STATE state=STATE_NORMAL;

	bool term=false;

	YsMatrix4x4 Rc;
	double d;
	YsVec3 t;

	YsShellExt mesh;
	std::vector <float> vtx,nom,col;
	YsVec3 bbx[2];

	YsVec3 lineOfLastPick[2];
	YsShellExt::VertexHandle lastPickedVtHd;

	static void AddColor(std::vector <float> &col,float r,float g,float b,float a);
	static void AddVertex(std::vector <float> &vtx,float x,float y,float z);
	static void AddNormal(std::vector <float> &nom,float x,float y,float z);

	void RemakeVertexArray(void);
	YsMatrix4x4 GetProjection(void) const;
	YsMatrix4x4 GetModelView(void) const;
	YsShellExt::PolygonHandle PickedPlHd(int mx,int my) const;
	YsShellExt::VertexHandle PickedVtHd(int mx,int my,int pixRange) const;


	// FOR SLICE MODE
	std::vector <float> sliceVtx,sliceCol;

	// FOR SCANNER MODE
	std::vector <float> scannerVtx,scannerCol;
public:
	ApplicationMain(int argc,char *argv[]);
	void RunOneStep(void);
	void Draw(void) const;
	bool MustTerminate(void) const;
};

/* static */ void ApplicationMain::AddColor(std::vector <float> &col,float r,float g,float b,float a)
{
	col.push_back(r);
	col.push_back(g);
	col.push_back(b);
	col.push_back(a);
}
/* static */ void ApplicationMain::AddVertex(std::vector <float> &vtx,float x,float y,float z)
{
	vtx.push_back(x);
	vtx.push_back(y);
	vtx.push_back(z);
}
/* static */ void ApplicationMain::AddNormal(std::vector <float> &nom,float x,float y,float z)
{
	nom.push_back(x);
	nom.push_back(y);
	nom.push_back(z);
}

void ApplicationMain::RemakeVertexArray(void)
{
	vtx.clear();
	nom.clear();
	col.clear();

	for(auto plHd=mesh.NullPolygon(); true==mesh.MoveToNextPolygon(plHd); )
	{
		auto plVtHd=mesh.GetPolygonVertex(plHd);
		auto plCol=mesh.GetColor(plHd);
		auto plNom=mesh.GetNormal(plHd);

		// Let's assume every polygon is a triangle for now.
		if(3==plVtHd.size())
		{
			for(int i=0; i<3; ++i)
			{
				auto vtPos=mesh.GetVertexPosition(plVtHd[i]);
				vtx.push_back(vtPos.xf());
				vtx.push_back(vtPos.yf());
				vtx.push_back(vtPos.zf());
				nom.push_back(plNom.xf());
				nom.push_back(plNom.yf());
				nom.push_back(plNom.zf());
				col.push_back(plCol.Rf());
				col.push_back(plCol.Gf());
				col.push_back(plCol.Bf());
				col.push_back(plCol.Af());
			}
		}
	}
}

YsMatrix4x4 ApplicationMain::GetProjection(void) const
{
	int wid,hei;
	FsGetWindowSize(wid,hei);
	auto aspect=(double)wid/(double)hei;
	return MakePerspective(45.0,aspect,d/10.0,d*2.0);
}

YsMatrix4x4 ApplicationMain::GetModelView(void) const
{
	YsMatrix4x4 globalToCamera=Rc;
	globalToCamera.Invert();

	YsMatrix4x4 modelView;
	modelView.Translate(0,0,-d);
	modelView*=globalToCamera;
	modelView.Translate(-t);
	return modelView;
}

YsShellExt::PolygonHandle ApplicationMain::PickedPlHd(int mx,int my) const
{
	int wid,hei;
	FsGetWindowSize(wid,hei);
	auto vp=WindowToViewPort(wid,hei,mx,my);

	auto perspective=GetProjection();
	auto modelView=GetModelView();

	YsMatrix4x4 all=perspective*modelView;
	all.Invert();

	auto nearPos=vp,farPos=vp;
	nearPos.SetZ(-1.0);
	farPos.SetZ(1.0);

	YsVec3 ln[2];
	all.Mul(ln[0],nearPos,1.0);
	all.Mul(ln[1],farPos,1.0);

	YsShellExt::PolygonHandle pickedPlHd=mesh.NullPolygon();
	double pickedZ=0.0;
	for(auto plHd=mesh.NullPolygon(); true==mesh.MoveToNextPolygon(plHd); )
	{
		std::vector <YsVec3> plVtPos;
		for(auto vtHd : mesh.GetPolygonVertex(plHd))
		{
			plVtPos.push_back(mesh.GetVertexPosition(vtHd));
		}
		YsPlane pln;
		YsVec3 crs;
		if(YSOK==pln.MakeBestFitPlane(plVtPos) &&
		   YSOK==pln.GetPenetration(crs,ln[0],ln[1]) &&
		   YSINSIDE==YsCheckInsidePolygon3(crs,plVtPos))
		{
			crs=modelView*crs;
			if(mesh.NullPolygon()==pickedPlHd || crs.z()>pickedZ)
			{
				pickedPlHd=plHd;
				pickedZ=crs.z();
			}
		}
	}

	return pickedPlHd;
}

YsShellExt::VertexHandle ApplicationMain::PickedVtHd(int mx,int my,int pixRange) const
{
	int wid,hei;
	FsGetWindowSize(wid,hei);
	auto vp=WindowToViewPort(wid,hei,mx,my);

	auto projection=GetProjection();
	auto modelView=GetModelView();

	double pickedZ=0.0;
	auto pickedVtHd=mesh.NullVertex();
	for(auto vtHd=mesh.NullVertex(); true==mesh.MoveToNextVertex(vtHd); )
	{
		auto vtPos=mesh.GetVertexPosition(vtHd);
		vtPos=projection*modelView*vtPos;
		auto winPos=ViewPortToWindow(wid,hei,vtPos);
		int dx=(mx-winPos.x()),dy=(my-winPos.y());
		if(-pixRange<=dx && dx<=pixRange && -pixRange<=dy && dy<=pixRange)
		{
			if(mesh.NullVertex()==pickedVtHd || vtPos.z()<pickedZ)
			{
				pickedVtHd=vtHd;
				pickedZ=vtPos.z();
			}
		}
	}

	return pickedVtHd;
}

ApplicationMain::ApplicationMain(int argc,char *argv[])
{
	d=10.0;
	t=YsVec3::Origin();

	lineOfLastPick[0]=YsVec3::Origin();
	lineOfLastPick[1]=YsVec3::Origin();
	lastPickedVtHd=mesh.NullVertex();

	mesh.EnableSearch();
	if(2<=argc && true==mesh.LoadStl(argv[1]))
	{
		for(auto plHd : mesh.AllPolygon())
		{
			mesh.SetPolygonColor(plHd,YsBlue());
		}

		RemakeVertexArray();
		mesh.GetBoundingBox(bbx[0],bbx[1]);

		t=(bbx[0]+bbx[1])/2.0;
		d=(bbx[1]-bbx[0]).GetLength()*1.2;

		printf("Target %s\n",t.Txt());
		printf("Diagonal %lf\n",d);
	}
}

void ApplicationMain::RunOneStep(void)
{
	auto key=FsInkey();

	if(FsGetKeyState(FSKEY_LEFT))
	{
		Rc.RotateXZ(YsPi/60.0);
	}
	if(FsGetKeyState(FSKEY_RIGHT))
	{
		Rc.RotateXZ(-YsPi/60.0);
	}
	if(FsGetKeyState(FSKEY_UP))
	{
		Rc.RotateYZ(YsPi/60.0);
	}
	if(FsGetKeyState(FSKEY_DOWN))
	{
		Rc.RotateYZ(-YsPi/60.0);
	}


	int mx,my,lb,mb,rb;
	int evt=FsGetMouseEvent(lb,mb,rb,mx,my);
	int wid,hei;
	FsGetWindowSize(wid,hei);

	if(evt==FSMOUSEEVENT_LBUTTONDOWN)
	{
		auto plHd=PickedPlHd(mx,my);
		if(nullptr!=plHd)
		{
			Paint(mesh,plHd,YsPi/9.0);  // PI/9=20 degree
			RemakeVertexArray();
		}
	}
	

	if(FSKEY_ESC==key)
	{
		term=true;
	}
	// Write key response to S, L, and N keys here >>
	
	if(FSKEY_N==key)
	{
		state = STATE_NORMAL;
	}
	if(FSKEY_S==key)
	{
		state = STATE_SLICE;
		sliceVtx.clear();
		sliceCol.clear();
		sliceVtx = MakeSliceVertexArray(mesh);
		for(int i =0; i<sliceVtx.size()/3;++i)
		{
			sliceCol.push_back(0);sliceCol.push_back(0);sliceCol.push_back(0);sliceCol.push_back(1);
		}
	}
	if(FSKEY_L==key)
	{
		state = STATE_SCANNER;
		scannerVtx = MakeRayIntersectionVertexArray(mesh);
		for(int i = 0; i<scannerVtx.size()/3;++i)
		{
			scannerCol.push_back(0);scannerCol.push_back(0);scannerCol.push_back(0);scannerCol.push_back(1);
		}
	}
	// Write key response to S, L, and N keys here <<

	std::this_thread::sleep_for(std::chrono::milliseconds(10));
}
void ApplicationMain::Draw(void) const
{
	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
	glEnable(GL_DEPTH_TEST);

	int wid,hei;
	FsGetWindowSize(wid,hei);
	auto aspect=(double)wid/(double)hei;
	glViewport(0,0,wid,hei);

	YsMatrix4x4 projection=GetProjection();
	GLfloat projectionGl[16];
	projection.GetOpenGlCompatibleMatrix(projectionGl);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glMultMatrixf(projectionGl);

	YsMatrix4x4 globalToCamera=Rc;
	globalToCamera.Invert();

	YsMatrix4x4 modelView=GetModelView();

	GLfloat modelViewGl[16];
	modelView.GetOpenGlCompatibleMatrix(modelViewGl);

	glShadeModel(GL_SMOOTH);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	GLfloat lightDir[]={0,1.0f/(float)sqrt(2.0f),1.0f/(float)sqrt(2.0f),0};
	glLightfv(GL_LIGHT0,GL_POSITION,lightDir);

	glMultMatrixf(modelViewGl);

	if(STATE_NORMAL==state)
	{
		glEnable(GL_COLOR_MATERIAL);
		glEnable(GL_LIGHTING);
		glEnable(GL_LIGHT0);

		glEnableClientState(GL_VERTEX_ARRAY);
		glEnableClientState(GL_NORMAL_ARRAY);
		glEnableClientState(GL_COLOR_ARRAY);
		glColorPointer(4,GL_FLOAT,0,col.data());
		glNormalPointer(GL_FLOAT,0,nom.data());
		glVertexPointer(3,GL_FLOAT,0,vtx.data());
		glDrawArrays(GL_TRIANGLES,0,vtx.size()/3);
		glDisableClientState(GL_VERTEX_ARRAY);
		glDisableClientState(GL_NORMAL_ARRAY);
		glDisableClientState(GL_COLOR_ARRAY);
	}
	else if(STATE_SLICE==state)
	{
		// Write your code here >>
		glEnableClientState(GL_VERTEX_ARRAY);
		glEnableClientState(GL_COLOR_ARRAY);
		glColorPointer(4,GL_FLOAT,0,sliceCol.data());
		glVertexPointer(3,GL_FLOAT,0,sliceVtx.data());
		glDrawArrays(GL_LINES,0,sliceVtx.size()/3);
		glDisableClientState(GL_VERTEX_ARRAY);
		glDisableClientState(GL_COLOR_ARRAY);

		// Write your code here <<
	}
	else if(STATE_SCANNER==state)
	{
		// Write your code here >>
		glEnableClientState(GL_VERTEX_ARRAY);
		glEnableClientState(GL_COLOR_ARRAY);
		glColorPointer(4,GL_FLOAT,0,scannerCol.data());
		glVertexPointer(3,GL_FLOAT,0,scannerVtx.data());
		glPointSize(2.0);
		glDrawArrays(GL_POINTS,0,scannerVtx.size()/3);
		
		// glDrawArrays(GL_LINES,0,scannerVtx.size()/3);
		glDisableClientState(GL_VERTEX_ARRAY);
		glDisableClientState(GL_COLOR_ARRAY);
		// Write your code here <<
	}


	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_COLOR_ARRAY);
	const GLfloat lineVtx[6]=
	{
		lineOfLastPick[0].xf(),lineOfLastPick[0].yf(),lineOfLastPick[0].zf(),
		lineOfLastPick[1].xf(),lineOfLastPick[1].yf(),lineOfLastPick[1].zf(),
	};
	const GLfloat lineCol[8]=
	{
		1,0,0,1,0,0,1,1
	};
	glColorPointer(4,GL_FLOAT,0,lineCol);
	glVertexPointer(3,GL_FLOAT,0,lineVtx);
	glDrawArrays(GL_LINES,0,2);
	glDisableClientState(GL_VERTEX_ARRAY);
	glDisableClientState(GL_COLOR_ARRAY);


	if(mesh.NullVertex()!=lastPickedVtHd)
	{
		auto vtPos=mesh.GetVertexPosition(lastPickedVtHd);
		GLfloat pointPos[3]={vtPos.xf(),vtPos.yf(),vtPos.zf()};
		GLfloat pointCol[4]={1.0f,0.0f,1.0f,1.0f};

		glDisable(GL_LIGHTING);
		glEnableClientState(GL_VERTEX_ARRAY);
		glEnableClientState(GL_COLOR_ARRAY);
		glPointSize(4);
		glVertexPointer(3,GL_FLOAT,0,pointPos);
		glColorPointer(4,GL_FLOAT,0,pointCol);
		glDrawArrays(GL_POINTS,0,1);
		glDisableClientState(GL_VERTEX_ARRAY);
		glDisableClientState(GL_COLOR_ARRAY);
	}

	FsSwapBuffers();
}
bool ApplicationMain::MustTerminate(void) const
{
	return term;
}



int main(int argc,char *argv[])
{
	FsOpenWindow(0,0,1024,768,1);
	ApplicationMain app(argc,argv);
	while(true!=app.MustTerminate())
	{
		FsPollDevice();
		app.RunOneStep();
		app.Draw();
	}
	return 0;
}
