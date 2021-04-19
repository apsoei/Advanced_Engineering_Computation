#include "simplebitmaptemplate.h"
#include "simplebitmap.h"
#include "yspng.h"
#include "yspngenc.h"

#include "fssimplewindow.h"

#include <stdio.h>
#include <iostream>
#include <cstdio>


int main(int argc,char *argv[])
{

	// int test[4] = {4,4,4,2};
	if(argc<2)
	{
		printf("Usage: ps4_1 pngFile-Name.png\n");
		return 1;
	}

	SimpleBitmap bmp;
	if(true!=bmp.LoadPng(argv[1] ) )
	{
		printf("Error: Failed to read a .PNG file %s\n",argv[1]);
		return 1;
	}
	
	
	
	// bmp.Invert();
	
	int bmpWid = bmp.GetWidth();
	int bmpHei = bmp.GetHeight();
// std::cout << bmpWid << ", " << bmpHei <<std::endl;

	SimpleBitmap temp;

	temp = bmp.CutOut(0,0,40,40);

	

	FILE *fp;
	

	bool printed = false;
	int startX = 0, startY = 0, w = 40,h = 40;
	int nameNum = 0;
	char text[80];

	for(int y = startY; y < bmpHei;y+=h)
	{

		if(nameNum>199) break;
		for(int x = startX; x<bmpWid;x+=w)
		{
			if(x>bmpWid) 
			{
				x = startX;
			}
			temp = bmp.CutOut(x,y,w,h);
			// temp.Invert();
			sprintf(text,"%d.png", nameNum);
			fp = fopen(text,"wb");
			temp.SavePng(fp);
			
			// std::cout << text << std::endl;
			nameNum+=1;
			// fp = nullptr;
			if(nameNum>199) 
			{
				break;
			}
		}	
		y+=h;
	}


	// FsOpenWindow(0,0,1200,800,1);
	// for(;;)
	// {
	// 	if (true!=printed)
	// 	{
	// 		std::cout << "NumCompPerLine: " << bmp.GetNumComponentPerLine() << std::endl;
	// 		std::cout << "bmp widht: " << bmp.GetWidth() << std::endl;
	// 		std::cout << "bmp height: " << bmp.GetHeight() << std::endl;
			
	// 		std::cout << bmp.GetBitmapPointer()[3000,0] <<std::endl;
	// 		printed = true;
	// 	}

	// 	FsPollDevice();
	// 	auto key=FsInkey();
	// 	if(FSKEY_ESC==key)
	// 	{
	// 		break;
	// 	}
	// 	// if(startX<bmp.GetWidth()&&startY<bmp.GetHeight())
	// 	// {
	// 	// 	temp.CleanUp();
	// 	// 	temp = bmp.CutOut(startX,startY,40,40);
	// 	// }


	// 	int wid,hei;
	// 	FsGetWindowSize(wid,hei);

	// 	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
	// 	glRasterPos2i(0,hei-1);
	// 	// glRasterPos2i(wid/2,hei/2);
	// 	glDrawPixels(temp.GetWidth(),temp.GetHeight(),GL_RGBA,GL_UNSIGNED_BYTE,temp.GetBitmapPointer());
	// 	// glDrawPixels(bmp.GetWidth(),bmp.GetHeight(),GL_RGBA,GL_UNSIGNED_BYTE,bmp.GetBitmapPointer());
	// 	FsSwapBuffers();
	// 	// FsSleep(3000);
	// 	// startX+=40;
	// 	// if(startX>bmp.GetWidth()) startX = 0,startY+=40;
	// 	// if(startY>bmp.GetHeight() || count>200) break;
	// 	// count +=1;
	// }
	return 0;
}
