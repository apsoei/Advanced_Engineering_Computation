#include <vector>
#include <stdio.h>
#include <iostream>
#include <cstdio>
#include <iostream>
#include <string>

#include "mmlplayer.h"
#include "yssimplesound.h"
#include "fssimplewindow.h"

#include "simplebitmaptemplate.h"
#include "simplebitmap.h"

#include "yspng.h"
#include "yspngenc.h"
#include "yshash.h"



// La Valse Pour Xanadu - b's A,B,E
void SetUpMML(MMLSegmentPlayer &mmlplayer)
{
	mmlplayer.AddSegment
	(
		"@2T90L12V12",
		// "@2T90L2S0M6000",
		"@2T90L12V12",
		"@2T90L12V12",
		"","",""
	);
	mmlplayer.AddSegment
	(
		"O4C E O5C","","O4C O3B O4C ",
		"","",""
	);
	mmlplayer.AddSegment
	(
		"O3B F A-","","O4D C+ D",
		"","",""
	);
	mmlplayer.AddSegment
	(
		"O3B O4G O3A- ","","O4E- R  D E-",
		"","",""
	);
	mmlplayer.AddSegment
	(
		"O4G F  L8O3A-GF","","O4D R C+ D",
		"","",""
	);
	mmlplayer.AddSegment
	(
		"O4G E-  ","","O4C R O4B- C",
		"","",""
	);
	mmlplayer.AddSegment
	(
		"O4G F  ","","O4D R C+ D",
		"","",""
	);
	mmlplayer.AddSegment
	(
		"O4G F  ","O3B- A-","O2E- F",
		"","",""
	);
	mmlplayer.AddSegment
	(
		"O4D A- G","O3B A- G","O2G A- B",
		"","",""
	);
	mmlplayer.AddSegment
	(
		"O4C R O5C","O3C  E-","R R O2B O3C",
		"","",""
	);
	mmlplayer.AddSegment
	(
		"O4B R R A-","O3D  F","R R O3C+ D",
		"","",""
	);
	mmlplayer.AddSegment
	(
		"O4B R R A-","O3E-  G","R R O3D E-",
		"","",""
	);
	mmlplayer.AddSegment
	(
		"O4G R R L8A-GF","O3D  F","R R O3C+ D",
		"","",""
	);
	mmlplayer.AddSegment
	(
		"O4G","O3C  E-","R R O2B O3C",
		"","",""
	);
	mmlplayer.AddSegment
	(
		"O4G","O3D  F","R R O3C+ D",
		"","",""
	);
	mmlplayer.AddSegment
	(
		"O4G","O3E  G D","R R F",
		"","",""
	);
	mmlplayer.AddSegment
	(
		"O3D A- G","","",
		"","",""
	);
	mmlplayer.AddSegment
	(
		"O4A- R R A-","O3F R R F","O3C R E",
		"","",""
	);
	mmlplayer.AddSegment
	(
		"O4G R R G","O3E- R D E-","O2B-",
		"","",""
	);
	mmlplayer.AddSegment
	(
		"O4A- R R A-","O3F R E- F","O3C",
		"","",""
	);
	mmlplayer.AddSegment
	(
		"O4G C O3B-","O3E- R D E-","O2B-",
		"","",""
	);
	mmlplayer.AddSegment
	(
		"O4A- R R  A-","O3F R E F","O3C",
		"","",""
	);
	mmlplayer.AddSegment
	(
		"O4G R R  G","O3E- R D E-","O2B-",
		"","",""
	);
	mmlplayer.AddSegment
	(
		"O4A- R R  A-","O3F R E F","O3C",
		"","",""
	);
	mmlplayer.AddSegment
	(
		"R O4G R ","R O3B- R","R O3E- R",
		"","",""
	);
	mmlplayer.AddSegment
	(
		"O4A- R R  A-","O3F R E F","O3C",
		"","",""
	);
	mmlplayer.AddSegment
	(
		"O4G R R  G","O3E- R D E-","O2B-",
		"","",""
	);
	mmlplayer.AddSegment
	(
		"O4A- R R  A-","O3F R E- F","O3C",
		"","",""
	);
	mmlplayer.AddSegment
	(
		"O4G C O3B-","O3E- R D E-","O2B-",
		"","",""
	);
	mmlplayer.AddSegment
	(
		"O4A- R R  A-","O3F R E F","O3C",
		"","",""
	);
	mmlplayer.AddSegment
	(
		"O4G R R  G","O3E- R D E-","O2B-",
		"","",""
	);
	mmlplayer.AddSegment
	(
		"O4A- R R  A-","O3F R E- F","O3C",
		"","",""
	);
	mmlplayer.AddSegment
	(
		"O4G G G","O3B- B- B-","O3F F F",
		"","",""
	);
	mmlplayer.AddSegment
	(
		"O3C  L4CO2B O3C","","R O3E-",
		"","",""
	);
	mmlplayer.AddSegment
	(
		"O3D  L4DC+ O3D","","R O3F",
		"","",""
	);
	mmlplayer.AddSegment
	(
		"O3E-  L4E-D O3E","","R O3G",
		"","",""
	);
	mmlplayer.AddSegment
	(
		"O3D  L4DC+ O3D","","R O3F",
		"","",""
	);

}



template <>
struct ysHash<SimpleBitmap>
{
	std::size_t operator()(const SimpleBitmap &key) const
	{
		std::size_t code = 0;
		int wid = key.GetWidth();
		int hei = key.GetHeight();
		unsigned int prime[4] = {3,5,7,11};
		auto ptr = key.GetBitmapPointer();
		// int R =0, G=0, B=0;
		// for (unsigned int y = 0; y<hei; ++y)
		// {
		// 	for(unsigned int x = 0; x<wid; ++x)
		// 	{
		// 		R = ptr[4*(y*wid + x)];
		// 		G = ptr[4*(y*wid + x) +1];
		// 		B = ptr[4*(y*wid + x) +2];
		// 		code += R*prime[0] + G*prime[1] + B*prime[2];
		// 	}
		// }
		for(unsigned int i=0; i<wid*hei;)
		{	
			code += 2*ptr[i]+3*ptr[i+1]+5*ptr[i+2]+7*ptr[i+3]+11*ptr[i*4];
			i+=5;
		}
		return code;
	}
};


const SimpleBitmap& Id2Bitmap(int id,const ysHashTable <SimpleBitmap,int> &table)
{
	static SimpleBitmap dummy;
	// SimpleBitmap dummy;
	for(auto iter = table.begin(); iter!=table.end(); ++iter)
	{
		if(iter->value == id)
		{
// std::cout << "found value and returning bitmap" <<std::endl;
			return iter->key;
		}
	}
	return dummy;
std::cout<< "Id2Bitmap Failed " <<std::endl;
}

int findCharacterPixCount(const SimpleBitmap &tile)
{
	int pixCount = 0;
	int wid = tile.GetWidth();
	int hei = tile.GetHeight();
	int R=0,G=0,B=0,A=0;
	for(int y = 0; y<hei; ++y)
	{
		for(int x = 0; x<wid; ++x)
		{
			R = tile.GetPixelPointer(x,y)[0];
			G = tile.GetPixelPointer(x,y)[1];
			B = tile.GetPixelPointer(x,y)[2];
			A = tile.GetPixelPointer(x,y)[3];
			// Red, White, Black
			if((R==255&&G==0&&B==0) ||(R==255&&G==255&&B==255) ||(R==0&&G==0&&B==0))
			{
				pixCount++;
			}
		}
	}
// std::cout << "PIX COUNT : " <<pixCount <<std::endl;
	return pixCount;
	
}
const SimpleBitmap& GetSimilar(SimpleBitmap &tile,const ysHashTable <SimpleBitmap,int> &table)
{
	int pixCount = findCharacterPixCount(tile);
	int needToEqual = 40*40 - pixCount;
	int countEqual = 0;
	int wid = tile.GetWidth();
	int hei = tile.GetHeight();
	
	for(auto iter = table.begin(); iter!=table.end(); ++iter)
	{
		if(iter->key!=tile && findCharacterPixCount(iter->key)==0)
		{
			for(int y=0; y<hei; ++y)
			{
				for(int x=0; x<wid; ++x)
				{
					if(tile.GetPixelPointer(x,y)[0]==iter->key.GetPixelPointer(x,y)[0] &&
					   tile.GetPixelPointer(x,y)[1]==iter->key.GetPixelPointer(x,y)[1] &&
					   tile.GetPixelPointer(x,y)[2]==iter->key.GetPixelPointer(x,y)[2])
					{

						countEqual++;

					}
				}
			}
			if(countEqual==needToEqual)
			{

				return iter->key;
				break;
			}
			countEqual = 0;
		}
	}

	return tile;
}


int main(int argc,char *argv[])
{
	


	ysHashTable <SimpleBitmap,int> table;
	
	
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
	
	int bmpWid = bmp.GetWidth();
	int bmpHei = bmp.GetHeight();

	

	SimpleBitmap temp;
	
	
	int startX = 0, startY = 0, w = 40,h = 40;
	int nameNum = 0;
	char text[80];


	std::vector<std::size_t> uniques {};
	std::vector<std::vector<int>> idMap {};
	std::vector<int> idOneRow {};
	int mapRow = 0;
	int tableRow = 0;
	int tableCol = 0;
	int IDvalue = 0;
	int currentRow = 0;
	int currentVal = 0;
	// bitmap temp is key, int IDvalue is value(0,1,2,3, ... )
	bool printed = false;
	int insertCount = 0;
	for(int y = startY; y < bmpHei;y+=h)
	{	
		for(int x = startX; x<bmpWid;x+=w)
		{
			temp = bmp.CutOut(x,y,w,h);
			if(table.end()==table.find(temp))
			{
				table.insert(temp,IDvalue);
				idOneRow.push_back(IDvalue);
				printf("\%c",' '+IDvalue);

				insertCount++;
				IDvalue++;
			}
			else
			{
				idOneRow.push_back(table.find(temp)->value);
				printf("\%c",' '+table.find(temp)->value);
			}
// std::cout<<"current table size: " << table.len <<std::endl;	
		}
		printf("\n");
		idMap.push_back(idOneRow);
		idOneRow.clear();
// std::cout<< "wid, hei of original bitmap: " <<bmpWid <<"," <<bmpHei <<std::endl;
	}	
	
	std::vector<std::vector<int>> idMapBonus2;
	idMapBonus2 = idMap;
	for(int row = 0; row <idMap.size(); ++row)
	{
		for(int col = 0; col<idMap[0].size(); ++col)
		{
			SimpleBitmap bonus2 = Id2Bitmap(idMap[row][col],table);
			if(0!=findCharacterPixCount(bonus2) && bonus2!=GetSimilar(bonus2,table))
			{

				bonus2 = GetSimilar(bonus2,table);
				idMapBonus2[row][col] = table.find(bonus2)->value;
			}

		}
	}



	FsOpenWindow(0,0,1200,800,1);
	int drawX, drawY;
	int count = 0;
	int r = 0,c = 0;
	int upperR, upperC;

	MMLSegmentPlayer mmlplayer;
	SetUpMML(mmlplayer);
	YsSoundPlayer player;
	player.Start();	
	YsSoundPlayer::Stream stream;
	player.StartStreaming(stream);
	YsSoundPlayer::SoundData nextWave;
	
	for(;;)
	{
		FsPollDevice();
		// FOR MUSIC >>
		
		player.KeepPlaying();  // <- This line is only needed for Linux ALSA.
		if(YSTRUE==player.StreamPlayerReadyToAcceptNextSegment(stream,nextWave))
		{
			player.AddNextStreamingSegment(stream,nextWave);
			auto rawWave=mmlplayer.GenerateWave(1000);  // Create for next 100ms
			nextWave.CreateFromSigned16bitStereo(YM2612::WAVE_SAMPLING_RATE,rawWave);
			if(0!=mmlplayer.GetLastErrorCode())
			{
				for(auto msg : mmlplayer.GetLastError().Format())
				{
					std::cout << msg << std::endl;
				}
			}
		}

		// << FOR MUSIC 

		auto key=FsInkey();
		if(FSKEY_ESC==key)
		{
			break;
		}
		
		int wid,hei;
		FsGetWindowSize(wid,hei);

		if(idMap.size()> hei/40) upperR = idMap.size() - (hei/40);
		else upperR = hei/40;
		if(idMap[0].size()>wid/40) upperC = idMap[0].size() - (wid/40);
		else upperC = wid/40;

		glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
		drawX = 0, drawY = 40;

		if(FSKEY_SPACE==key) count++;
		if(count%3==1)
		{
			for(int row = r; row<(hei/40 + r -1); ++row)
			{
				for(int col = c; col<(wid/40 + c); ++col)
				{
					glRasterPos2i(drawX,drawY);

					SimpleBitmap bonus1 = Id2Bitmap(idMap[row][col],table);

					bonus1.Invert();
					glDrawPixels(bonus1.GetWidth(),bonus1.GetHeight(),
								 GL_RGBA,GL_UNSIGNED_BYTE,bonus1.GetBitmapPointer());

					drawX+=40;
				}

				drawX=0;
				drawY+=40;		
			}		

			FsSwapBuffers();
		}
		if(FSKEY_RIGHT==key && c < upperC) 
		{
			c++;
		}
		if(FSKEY_LEFT==key && c >0) 
		{
			c--;
		}
		if(FSKEY_UP==key && r >0) 
		{
			r--;
		}
		if(FSKEY_DOWN==key&& r <= upperR)
		{
			r++;
		}
		
		if(count%3==2)
		{

			for(int row = r; row<(hei/40 + r); ++row)
			// for(int row = r; row<idMap.size(); ++row)
			{

				for(int col = c; col<(wid/40 + c); ++col)
				// for(int col = c; col<idMap[0].size(); ++col)	
				{

					glRasterPos2i(drawX,drawY);
					SimpleBitmap bonus2 = Id2Bitmap(idMapBonus2[row][col],table);
				
					bonus2.Invert();
					glDrawPixels(bonus2.GetWidth(),bonus2.GetHeight(),
								 GL_RGBA,GL_UNSIGNED_BYTE,bonus2.GetBitmapPointer());

					drawX+=40;
				}

				drawX=0;
				drawY+=40;		
			}			
			FsSwapBuffers();
		}
		if(count==0)
		{
			drawX = 0, drawY = 40;
			for(auto iter=table.begin(); iter!=table.end(); ++iter)
			{
				uniques.push_back(iter->code);
				glRasterPos2i(drawX,drawY);
				SimpleBitmap Draw = iter->key;
				Draw.Invert();
				glDrawPixels(Draw.GetWidth(),Draw.GetHeight(),GL_RGBA,GL_UNSIGNED_BYTE,Draw.GetBitmapPointer());
				
				drawX+=40;
				if((wid-drawX) < 40)
				{
					drawX=0;
					drawY+=40;
				}
				
			}
			FsSwapBuffers();
		}
		
		if(count>2) count = 0;
		
	}
	player.End();

	return 0;
}
