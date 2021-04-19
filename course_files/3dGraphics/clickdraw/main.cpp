#include <fssimplewindow.h>
#include "ysglfontdata.h"
#include <vector>



class ApplicationMain
{
private:
	bool term=false;

	std::vector <float> vtx,col;

public:
	ApplicationMain();
	bool MustTerminate(void) const;
	void RunOneStep(void);
	void Draw(void) const;
};

ApplicationMain::ApplicationMain()
{
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
	if(FSMOUSEEVENT_LBUTTONDOWN==evt)
	{
		vtx.push_back((float)mx);
		vtx.push_back((float)my);
		col.push_back(0);
		col.push_back(0);
		col.push_back(0);
		col.push_back(1);
	}
}
void ApplicationMain::Draw(void) const
{
	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
	glShadeModel(GL_SMOOTH);

	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_COLOR_ARRAY);
	glColorPointer(4,GL_FLOAT,0,col.data());
	glVertexPointer(2,GL_FLOAT,0,vtx.data());
	glDrawArrays(GL_LINE_STRIP,0,vtx.size()/2);
	glDisableClientState(GL_VERTEX_ARRAY);
	glDisableClientState(GL_COLOR_ARRAY);

	FsSwapBuffers();
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
