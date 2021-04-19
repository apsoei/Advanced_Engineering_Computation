#include <stdio.h>
#include "fssimplewindow.h"
#include "simplebitmap.h"

int main(int argc,char *argv[])
{
	if(argc<2)
	{
		printf("Usage: pngviewer filename.png\n");
		return 1;
	}

	SimpleBitmap bmp;
	if(true!=bmp.LoadPng(argv[1]))
	{
		printf("Failed to load %s\n",argv[1]);
		return 1;
	}

	bmp.Invert();


	FsOpenWindow(0,0,1200,800,1);
	for(;;)
	{
		FsPollDevice();
		auto key=FsInkey();
		if(FSKEY_ESC==key)
		{
			break;
		}

		int wid,hei;
		FsGetWindowSize(wid,hei);

		glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
		glRasterPos2i(0,hei-1);
		glDrawPixels(bmp.GetWidth(),bmp.GetHeight(),GL_RGBA,GL_UNSIGNED_BYTE,bmp.GetBitmapPointer());
		FsSwapBuffers();
	}
	return 0;
}
