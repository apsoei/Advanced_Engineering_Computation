#include <fssimplewindow.h>
#include "ysglfontdata.h"
#include "ysbintree.h"



class ApplicationMain
{
private:
	bool term=false;
	BinaryTree <int,int> tree;
	BinaryTree <int,int>::NodeHandle mouseOn;
	const int yStep=40;
public:
	ApplicationMain();
	bool MustTerminate(void) const;
	void RunOneStep(void);
	void Draw(void) const;
protected:
	void DrawNode(BinaryTree <int,int>::NodeHandle ndHd,int x0,int x1,int y0,int yStep,int fromX,int fromY) const;
	BinaryTree <int,int>::NodeHandle PickedNode(BinaryTree <int,int>::NodeHandle ndHd,int x0,int x1,int y0,int yStep,int mx,int my) const;
};

ApplicationMain::ApplicationMain()
{
	srand((int)time(nullptr));
	for(int i=0; i<60; ++i)
	{
		tree.Insert(rand()%20,0);
	}
	mouseOn=tree.Null();
}
bool ApplicationMain::MustTerminate(void) const
{
	return term;
}
void ApplicationMain::RunOneStep(void)
{
	auto key=FsInkey();
	if(FSKEY_ESC==key)
	{
		term=true;
	}

	int lb,mb,rb,mx,my;
	auto evt=FsGetMouseEvent(lb,mb,rb,mx,my);

	int wid,hei;
	FsGetWindowSize(wid,hei);
	mouseOn=PickedNode(tree.RootNode(),0,wid,0,yStep,mx,my);

	if(FSKEY_DEL==key && tree.Null()!=mouseOn)
	{
		tree.Delete(mouseOn);
		mouseOn=tree.Null();
	}
	if(FSKEY_INS==key)
	{
		tree.Insert(rand()%20,0);
	}
	if(FSKEY_L==key)
	{
		tree.RotateLeft(mouseOn);
	}
}
void ApplicationMain::Draw(void) const
{
	int wid,hei;
	FsGetWindowSize(wid,hei);

    glViewport(0,0,wid,hei);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0,(float)wid-1,(float)hei-1,0,-1,1);

	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
	DrawNode(tree.RootNode(),0,wid,0,yStep,wid/2,yStep/2);
	FsSwapBuffers();
}

void ApplicationMain::DrawNode(BinaryTree <int,int>::NodeHandle ndHd,int x0,int x1,int y0,int yStep,int fromX,int fromY) const
{
	if(tree.Null()!=ndHd)
	{
		int cx=(x0+x1)/2;
		int cy=y0+yStep/2;	

		if(ndHd==mouseOn)
		{
			glColor3ub(128,128,128);
			glBegin(GL_TRIANGLE_FAN);
			glVertex2i(x0,y0);
			glVertex2i(x1,y0);
			glVertex2i(x1,y0+yStep);
			glVertex2i(x0,y0+yStep);
			glEnd();
			glColor3ub(0,0,0);
		}

		glBegin(GL_LINES);
		glVertex2i(fromX,fromY);
		glVertex2i(cx,cy);
		glEnd();

		glRasterPos2i(cx,cy);
		char str[256];
		snprintf(str,255,"%d(%d)",tree.GetKey(ndHd),tree.GetHeight(ndHd));
		YsGlDrawFontBitmap12x16(str);

		DrawNode(tree.Left(ndHd),x0,cx,y0+yStep,yStep,cx,cy);
		DrawNode(tree.Right(ndHd),cx,x1,y0+yStep,yStep,cx,cy);
	}
}

typename BinaryTree<int,int>::NodeHandle ApplicationMain::PickedNode(BinaryTree <int,int>::NodeHandle ndHd,int x0,int x1,int y0,int yStep,int mx,int my) const
{
	if(tree.Null()!=ndHd)
	{
		if(x0<=mx && mx<x1 && y0<=my && my<y0+yStep)
		{
			return ndHd;
		}

		int cx=(x0+x1)/2;
		auto pick=PickedNode(tree.Left(ndHd),x0,cx,y0+yStep,yStep,mx,my);
		if(tree.Null()!=pick)
		{
			return pick;
		}
		pick=PickedNode(tree.Right(ndHd),cx,x1,y0+yStep,yStep,mx,my);
		if(tree.Null()!=pick)
		{
			return pick;
		}
	}
	return tree.Null();
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
