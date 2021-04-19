#include <stdio.h>
#include <math.h>
#include "fssimplewindow.h"

const double YsPi=3.1415927;

class CameraObject
{
public:
    double x,y,z;
    double h,p,b;

    double fov,nearZ,farZ;

    CameraObject();
    void Initialize(void);
    void SetUpCameraProjection(void);
    void SetUpCameraTransformation(void);

    void GetForwardVector(double &vx,double &vy,double &vz);
    void GetUpVector(double &vx,double &vy,double &vz);
    void GetRightVector(double &vx,double &vy,double &vz);
};

CameraObject::CameraObject()
{
    Initialize();
}

void CameraObject::Initialize(void)
{
    x=0;
    y=0;
    z=0;
    h=0;
    p=0;
    b=0;

    fov=YsPi/6.0;  // 30 degree
    nearZ=0.1;
    farZ=200.0;
}

void CameraObject::SetUpCameraProjection(void)
{
    int wid,hei;
    double aspect;

    FsGetWindowSize(wid,hei);
    aspect=(double)wid/(double)hei;

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(fov*180.0/YsPi,aspect,nearZ,farZ);
}

void CameraObject::SetUpCameraTransformation(void)
{
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glRotated(-b*180.0/YsPi,0.0,0.0,1.0);  // Rotation about Z axis
    glRotated(-p*180.0/YsPi,1.0,0.0,0.0);  // Rotation about X axis
    glRotated(-h*180.0/YsPi,0.0,1.0,0.0);  // Rotation about Y axis
    glTranslated(-x,-y,-z);
}

void CameraObject::GetForwardVector(double &vx,double &vy,double &vz)
{
    vx=-cos(p)*sin(h);
    vy= sin(p);
    vz=-cos(p)*cos(h);
}

void CameraObject::GetUpVector(double &vx,double &vy,double &vz)
{
	const double ux0=0.0;
	const double uy0=1.0;
	const double uz0=0.0;

	const double ux1=cos(b)*ux0-sin(b)*uy0;
	const double uy1=sin(b)*ux0+cos(b)*uy0;
	const double uz1=uz0;

	const double ux2=ux1;
	const double uy2=cos(p)*uy1-sin(p)*uz1;
	const double uz2=sin(p)*uy1+cos(p)*uz1;

    vx=cos(-h)*ux2-sin(-h)*uz2;
    vy=uy2;
    vz=sin(-h)*ux2+cos(-h)*uz2;
}

void CameraObject::GetRightVector(double &vx,double &vy,double &vz)
{
	const double ux0=1.0;
	const double uy0=0.0;
	const double uz0=0.0;

	const double ux1=cos(b)*ux0-sin(b)*uy0;
	const double uy1=sin(b)*ux0+cos(b)*uy0;
	const double uz1=uz0;

	const double ux2=ux1;
	const double uy2=cos(p)*uy1-sin(p)*uz1;
	const double uz2=sin(p)*uy1+cos(p)*uz1;

    vx=cos(-h)*ux2-sin(-h)*uz2;
    vy=uy2;
    vz=sin(-h)*ux2+cos(-h)*uz2;
}


class ApplicationMain
{
public:
    int terminate=0;
    CameraObject camera;

	ApplicationMain();
	bool MustTerminate(void) const;
	void RunOneStep(void);
	void Draw(void) const;
};

ApplicationMain::ApplicationMain()
{
    camera.z=10.0;
    camera.y=5.0;
}
bool ApplicationMain::MustTerminate(void) const
{
	return terminate;
}
void ApplicationMain::RunOneStep(void)
{
    FsPollDevice();

    int wid,hei;
    FsGetWindowSize(wid,hei);

    int key=FsInkey();
    switch(key)
    {
    case FSKEY_ESC:
        terminate=1;
        break;
    }

    if(0!=FsGetKeyState(FSKEY_LEFT))
    {
        camera.h+=YsPi/180.0;
    }
    if(0!=FsGetKeyState(FSKEY_RIGHT))
    {
        camera.h-=YsPi/180.0;
    }
    if(0!=FsGetKeyState(FSKEY_UP))
    {
        camera.p+=YsPi/180.0;
    }
    if(0!=FsGetKeyState(FSKEY_DOWN))
    {
        camera.p-=YsPi/180.0;
    }
    if(0!=FsGetKeyState(FSKEY_F))
    {
        double vx,vy,vz;
        camera.GetForwardVector(vx,vy,vz);
        camera.x+=vx*0.5;
        camera.y+=vy*0.5;
        camera.z+=vz*0.5;
    }
    if(0!=FsGetKeyState(FSKEY_B))
    {
        double vx,vy,vz;
        camera.GetForwardVector(vx,vy,vz);
        camera.x-=vx*0.5;
        camera.y-=vy*0.5;
        camera.z-=vz*0.5;
    }

    // Set up 3D drawing
    // The following two functions can be:
    //   Put in here.
    //   Put in Draw function, and make Draw function a modifier.
    //   Put in Draw function, and make camera mutable.
    camera.SetUpCameraProjection();
    camera.SetUpCameraTransformation();

	FsSleep(25);
}
void ApplicationMain::Draw(void) const
{
    int wid,hei;
    FsGetWindowSize(wid,hei);

    glClear(GL_DEPTH_BUFFER_BIT|GL_COLOR_BUFFER_BIT);

    glViewport(0,0,wid,hei);

    glEnable(GL_DEPTH_TEST);
    glEnable(GL_POLYGON_OFFSET_FILL);
    glPolygonOffset(1,1);

    // 3D drawing from here
    glColor3ub(0,0,255);

    glBegin(GL_LINES);
    int x;
    for(x=-500; x<=500; x+=20)
    {
        glVertex3i(x,0,-500);
        glVertex3i(x,0, 500);
        glVertex3i(-500,0,x);
        glVertex3i( 500,0,x);
    }
    glEnd();

    // Set up 2D drawing
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0,(float)wid-1,(float)hei-1,0,-1,1);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    glDisable(GL_DEPTH_TEST);

    FsSwapBuffers();
}



int main(void)
{
    FsOpenWindow(16,16,800,600,1);

	ApplicationMain app;
    while(true!=app.MustTerminate())
    {
		app.RunOneStep();
		app.Draw();
    }

    return 0;
}
