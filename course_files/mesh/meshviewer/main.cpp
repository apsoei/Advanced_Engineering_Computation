#include <fssimplewindow.h>
#include "ysglfontdata.h"
#include <vector>
#include <chrono>
#include <ysclass.h>
#include <iostream>

#include "mesh.h"
#include "glutil.h"



class ApplicationMain
{
private:
	enum
	{
		MODE_NORMAL,
		MODE_DUAL,
		MODE_DHA
	};

	bool term=false;
	int mode=MODE_NORMAL;

	const double fovDeg=30.0;
	const double fovRad=YsPi/6.0;

	PolygonalMesh mesh;
	mutable std::vector <float> vtx3d,col3d,nom3d;

	std::vector <float> dualVtx,dualCol;

	std::vector <float> lineVtx,lineCol;
	PolygonalMesh::VertexHandle lastPickedVtHd;
	std::vector <float> neiVtx,neiVtxCol;

	double viewDistance=40.0;
	YsMatrix3x3 viewRotation;
	YsVec3 viewTarget;
	decltype(std::chrono::high_resolution_clock::now()) lastT;

	void MouseToLine(YsVec3 line[2],int mx,int my) const;
	YsMatrix4x4 GetModelView(void) const;
	void GetNearFar(double &nearz,double &farz) const;

	PolygonalMesh::PolygonHandle PickedPlHd(int mx,int my) const;
	PolygonalMesh::VertexHandle PickedVtHd(int mx,int my) const;

public:
	ApplicationMain(int argc,char *argv[]);

	bool LoadSTL(const char fName[]);
	void RemakeVertexArray(void);
	void MakeDual(void);
	void MakeHighDHAEdge(void);

	bool MustTerminate(void) const;
	void RunOneStep(void);
	void SetUpHeadLight(void) const;
	void Draw(void) const;
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
		LoadSTL(argv[1]);
	}
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

void ApplicationMain::MakeDual(void)
{
	dualVtx.clear();
	dualCol.clear();
	for(auto plHd=mesh.FirstPolygon(); mesh.NullPolygon()!=plHd; mesh.MoveToNextPolygon(plHd))
	{
		auto plCen=mesh.GetCenter(plHd);
		for(int n=0; n<mesh.GetPolygonNumVertex(plHd); ++n)
		{
			auto neiPlHd=mesh.GetNeighborPolygon(plHd,n);
			if(mesh.NullPolygon()!=neiPlHd)
			{
				auto neiCen=mesh.GetCenter(neiPlHd);

				dualVtx.push_back(plCen.xf());dualVtx.push_back(plCen.yf());dualVtx.push_back(plCen.zf());
				dualVtx.push_back(neiCen.xf());dualVtx.push_back(neiCen.yf());dualVtx.push_back(neiCen.zf());

				dualCol.push_back(0);dualCol.push_back(0);dualCol.push_back(0);dualCol.push_back(1);
				dualCol.push_back(0);dualCol.push_back(0);dualCol.push_back(0);dualCol.push_back(1);
			}
		}
	}
}

void ApplicationMain::MakeHighDHAEdge(void)
{
	lineVtx.clear();
	lineCol.clear();
	for(auto plHd=mesh.FirstPolygon(); mesh.NullPolygon()!=plHd; mesh.MoveToNextPolygon(plHd))
	{
		auto nom0=mesh.GetNormal(plHd);
		auto plVtHd=mesh.GetPolygonVertex(plHd);
		for(int i=0; i<mesh.GetPolygonNumVertex(plHd); ++i)
		{
			auto neiPlHd=mesh.GetNeighborPolygon(plHd,i);
			if(mesh.NullPolygon()!=neiPlHd && mesh.GetSearchKey(plHd)<mesh.GetSearchKey(neiPlHd))
			{
				auto nom1=mesh.GetNormal(neiPlHd);
				if(nom0*nom1<cos(YsPi/3.0))
				{
					auto vtPos0=mesh.GetVertexPosition(plVtHd[i]);
					auto vtPos1=mesh.GetVertexPosition(plVtHd[(i+1)%plVtHd.size()]);
					lineVtx.push_back(vtPos0.x());lineVtx.push_back(vtPos0.y());lineVtx.push_back(vtPos0.z());
					lineVtx.push_back(vtPos1.x());lineVtx.push_back(vtPos1.y());lineVtx.push_back(vtPos1.z());
					lineCol.push_back(0);lineCol.push_back(0);lineCol.push_back(0);lineCol.push_back(1);
					lineCol.push_back(0);lineCol.push_back(0);lineCol.push_back(0);lineCol.push_back(1);
				}
			}
		}
	}
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
	if(FSKEY_D==key)
	{
		MakeDual();
		mode=MODE_DUAL;
	}
	if(FSKEY_N==key)
	{
		mode=MODE_NORMAL;
	}
	if(FSKEY_A==key)
	{
		MakeHighDHAEdge();
		mode=MODE_DHA;
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
		YsVec3 line[2];
		MouseToLine(line,mx,my);

		lineVtx.clear();
		lineCol.clear();

		lineVtx.push_back(line[0].x());
		lineVtx.push_back(line[0].y());
		lineVtx.push_back(line[0].z());
		lineVtx.push_back(line[1].x());
		lineVtx.push_back(line[1].y());
		lineVtx.push_back(line[1].z());
		lineCol.push_back(1);lineCol.push_back(0);lineCol.push_back(0);lineCol.push_back(1);
		lineCol.push_back(1);lineCol.push_back(0);lineCol.push_back(0);lineCol.push_back(1);

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

		if(mesh.NullPolygon()!=picked)
		{
			float red[4]={1,0,0,1};
			for(auto plHd : FindNNeighbor(mesh,picked,5))
			{
				mesh.SetPolygonColor(plHd,red);
			}
			RemakeVertexArray();
		}
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

	if(MODE_NORMAL==mode)
	{
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
	}
	else if(MODE_DUAL==mode)
	{
		glDisable(GL_LIGHTING);

		glEnableClientState(GL_VERTEX_ARRAY);
		glEnableClientState(GL_COLOR_ARRAY);
		glColorPointer(4,GL_FLOAT,0,dualCol.data());
		glVertexPointer(3,GL_FLOAT,0,dualVtx.data());
		glDrawArrays(GL_LINES,0,dualVtx.size()/3);
		glDisableClientState(GL_VERTEX_ARRAY);
		glDisableClientState(GL_COLOR_ARRAY);
	}
	else if(MODE_DHA==mode)
	{
		glDisable(GL_LIGHTING);

		glEnableClientState(GL_VERTEX_ARRAY);
		glEnableClientState(GL_COLOR_ARRAY);
		glColorPointer(4,GL_FLOAT,0,lineCol.data());
		glVertexPointer(3,GL_FLOAT,0,lineVtx.data());
		glDrawArrays(GL_LINES,0,lineVtx.size()/3);
		glDisableClientState(GL_VERTEX_ARRAY);
		glDisableClientState(GL_COLOR_ARRAY);
	}

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
