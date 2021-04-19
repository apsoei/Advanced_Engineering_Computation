#include <fssimplewindow.h>
#include "ysglfontdata.h"



class ApplicationMain
{
private:
	bool term=false;
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

}
void ApplicationMain::Draw(void) const
{
	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
	glShadeModel(GL_SMOOTH);

	const GLfloat vtx[]={0,0,  600.0f,0,  600.0f,600.0f,  0,600.0f};
	const GLfloat col[]={1,0,0,1,  0,1,0,1,  0,0,1,1,  1,1,0,1};

	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_COLOR_ARRAY);
	glColorPointer(4,GL_FLOAT,0,col);
	glVertexPointer(2,GL_FLOAT,0,vtx);
	glDrawArrays(GL_QUADS,0,4);
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
