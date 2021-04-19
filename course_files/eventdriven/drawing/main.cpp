#include "fssimplewindow.h"
#include <vector>

class Vec2
{
public:
	int x,y;
};


class ApplicationMain
{
public:
    // State variables
	// One std::vector <Vec2> can represent a stroke.
	// std::vector of strokes can represent a drawing.
	std::vector <std::vector <Vec2> > strokes;
	bool term=false;

    bool MustTerminate(void) const
    {
		return term;
	}
    void RunOneStep(void)
    {
		FsPollDevice();

		auto key=FsInkey();
		if(FSKEY_ESC==key)
		{
			term=true;
			return;
		}

		int lb,mb,rb,mx,my;
		auto evt=FsGetMouseEvent(lb,mb,rb,mx,my);

		if(FSMOUSEEVENT_LBUTTONDOWN==evt)
		{
			std::vector <Vec2> single;
			Vec2 pnt;
			pnt.x=mx;
			pnt.y=my;
			single.push_back(pnt);
			strokes.push_back(single);
		}
		if(FSMOUSEEVENT_MOVE==evt && 0!=lb)
		{
			Vec2 pnt;
			pnt.x=mx;
			pnt.y=my;
			if(0<strokes.size())
			{
				// strokes.back() is the last stroke.
				// Add a point to the last stroke if the user moves the mouse while holding the button down.
				strokes.back().push_back(pnt);
			}
		}
	}
    void Draw(void) const
    {
		glClear(GL_COLOR_BUFFER_BIT);

		glColor3ub(0,0,255);
		for(auto &s : strokes)
		{
			glBegin(GL_LINE_STRIP);
			for(auto p : s)
			{
				glVertex2i(p.x,p.y);
			}
			glEnd();
		}

		FsSwapBuffers();
	}
};
int main(void)
{
    ApplicationMain app;
	FsOpenWindow(0,0,800,600,1);
    while(true!=app.MustTerminate())
    {
        app.RunOneStep();
        app.Draw();
    }
    return 0;
}
