#include "mmlplayer.h"
#include <iostream>
#include "fssimplewindow.h"
#include "yssimplesound.h"

#include "simplebitmap.h"
#include "yshash.h"



template <>
struct ysHash <SimpleBitmap>
{
	std::size_t operator()(const SimpleBitmap &key) const
	{
		auto rgba=key.GetBitmapPointer();
		const unsigned int coeff[5]=
		{
			2,3,5,7,11
		};
		std::size_t code=0;
		for(int i=0; i<key.GetTotalNumComponent(); ++i)
		{
			code+=coeff[i%5]*(unsigned int)rgba[i];
		}
		return code;
	}
};



class ApplicationMain
{
protected:
	bool term=false;

	SimpleBitmap sourceBmp;
	ysHashTable <SimpleBitmap,int> bmpToId;

	// >> for bonus problem 1
	int mode; // 0:showing found blocks    1:Showing pure map
	SimpleBitmapTemplate <int,1> codedMap;
	int sx,sy;
	std::vector <SimpleBitmap> blockCodeToBmp;

	std::vector <SimpleBitmap> backgroundBlockBmp;
	bool BitmapConsistsOfBlueAndYellowOnly(const SimpleBitmap &bmp) const;
	int CompareBlueAndYellow(const SimpleBitmap &bmp1,const SimpleBitmap &bmp2) const;
	// << for bonus problem 1

	// >> for bonus problem 2
	YsSoundPlayer player;
	YsSoundPlayer::SoundData nextWave;
	YsSoundPlayer::Stream waveStream;
	MMLSegmentPlayer mml;
	// << for bonus problem 2

public:
	ApplicationMain(int ac,char *av[]);
	~ApplicationMain();
	bool MustTerminate(void) const;
	void RunOneStep(void);
	void Draw(void) const;
};

bool ApplicationMain::BitmapConsistsOfBlueAndYellowOnly(const SimpleBitmap &bmp) const
{
	auto rgba=bmp.GetBitmapPointer();
	auto numPix=bmp.GetWidth()*bmp.GetHeight();
	for(int i=0; i<numPix; ++i)
	{
		if((rgba[i*4]==255 && rgba[i*4+1]==255 && rgba[i*4+2]==0) || // Yellow=R+G
		   (rgba[i*4]==0   && rgba[i*4+1]==0   && rgba[i*4+2]==255)) // Blue
		{
			continue;
		}
		return false;
	}
	return true;
}
int ApplicationMain::CompareBlueAndYellow(const SimpleBitmap &bmp1,const SimpleBitmap &bmp2) const
{
	if(40!=bmp1.GetWidth() || 40!=bmp1.GetHeight() ||
	   40!=bmp2.GetWidth() || 40!=bmp2.GetWidth())
	{
		return 10000;
	}

	int nErr=0;
	auto rgba1=bmp1.GetBitmapPointer();
	auto rgba2=bmp2.GetBitmapPointer();
	auto numPix=bmp1.GetWidth()*bmp1.GetHeight();
	for(int i=0; i<numPix; ++i)
	{
		if(((rgba1[i*4]==255 && rgba1[i*4+1]==255 && rgba1[i*4+2]==0) ||     // Yellow=R+G
		    (rgba1[i*4]==0   && rgba1[i*4+1]==0   && rgba1[i*4+2]==255)) &&  // Blue
		   ((rgba2[i*4]==255 && rgba2[i*4+1]==255 && rgba2[i*4+2]==0) ||     // Yellow=R+G
		    (rgba2[i*4]==0   && rgba2[i*4+1]==0   && rgba2[i*4+2]==255)))
		{
			if(rgba1[i*4  ]!=rgba2[i*4  ] ||
			   rgba1[i*4+1]!=rgba2[i*4+1] ||
			   rgba1[i*4+2]!=rgba2[i*4+2])
			{
				++nErr;
			}
		}
	}
	return nErr;
}

ApplicationMain::ApplicationMain(int argc,char *argv[])
{
	sx=0;
	sy=0;
	mode=0;

	if(2<=argc)
	{
		FILE *fp=fopen(argv[1],"rb");
		if(sourceBmp.LoadPng(fp))
		{
			printf("Loaded %dx%d\n",sourceBmp.GetWidth(),sourceBmp.GetHeight());

			int assignId=0;
			int numBlock=0;
			for(int y=0; y<sourceBmp.GetHeight(); y+=40)
			{
				for(int x=0; x<sourceBmp.GetWidth(); x+=40)
				{
					auto block=sourceBmp.CutOut(x,y,40,40);
					auto found=bmpToId.find(block);
					if(bmpToId.end()==found)
					{
						bmpToId.insert(block,assignId);
						// >> Bonus
						blockCodeToBmp.push_back(block);

						if(BitmapConsistsOfBlueAndYellowOnly(block))
						{
							backgroundBlockBmp.push_back(block);
						}
						// << Bonus
						printf("%c",' '+assignId);
						++assignId;
					}
					else
					{
						printf("%c",' '+found->second);
					}
					++numBlock;
				}
				printf("\n");
			}
			printf("Found %d block types in %d total blocks.\n",assignId,numBlock);
		}
		fclose(fp);
	}

	// >> for bonus problem 2
	player.Start();
	player.StartStreaming(waveStream);
	mml.AddSegment(
		"T180O4L4",
		"T180O4L4",
		"T180O4L4"
	);
	mml.AddSegment(
		"V12 O4C2O5C4      O4B2A-4    O4B2A-4   O4G2L16RA-GFL4",
		"V12 O4R4E-2       O4R4F2     O4R4G2    R4F2",
		"V12 O4C4.O3B8O4C4 O4D4.C#8D4 O4E4.D8E4 O4D4.C+8D4"
	);
	mml.AddSegment(
		"O4G2.      G2.      V14R4GF   DA-G",
		"O4R4E2     R4F2     V14O3B-A- BA-G",
		"O4C.O3BO4C O4D.C#8D V14O2EF   GA-B"
	);
	mml.AddSegment(
		"O4C2O5C     O4B2A- B2A-   G2L16RA-GFL4",
		"O3RE2       R4F2   R4G2   R4F2",
		"O3C.O2B8O3C D.C+8D E.D8E  D.C+8D"
	);
	mml.AddSegment(
		"O4G2.       G2.    G2.    R2.",
		"O3RE2       R4F2   R4G2   R2.",
		"O3C.O2B8O3C D.C+8D E.D8E  DA-G"
	);
	mml.AddSegment(
		"O4A-2A- G2G    A-2A- GO5CO4B-",
		"O3F.E8F E.D8E  F.E8F E.D8E",
		"O3C2R   O2B-2R O3C2R O2B-2R4"
	);
	mml.AddSegment(
		"A-2A-   G2G4   A-2A- RG2",
		"O3F.E8F E.D8E  F.E8F RB-2",
		"O3C2R   O2B-2R O3C2R RE2"
	);
	mml.AddSegment(
		"O4A-2A- G2G    A-2A- GO5CO4B-",
		"O3F.E8F E.D8E  F.E8F E.D8E",
		"O3C2R   O2B-2R O3C2R O2B-2R4"
	);
	mml.AddSegment(
		"A-2A-   G2G4   A-2A- T120GGG",
		"O3F.E8F E.D8E  F.E8F T120B-B-B-",
		"O3C2R   O2B-2R O3C2R T120EEE"
	);
	mml.AddSegment(
		"T180",
		"T180O3RE2        R4F2    R4G2   R4F2",
		"T180O3CC8O2B8O3C DD8C+8D EE8D8E DD8C+8D"
	);
	// << for bonus problem 2
}
ApplicationMain::~ApplicationMain()
{
	// >> for bonus problem 2
	// It is nicer if you stop the sound player in the destructor,
	// but if you don't no points will be taken off.
	player.End();
	// << for bonus problem 2
}

void ApplicationMain::RunOneStep(void)
{
	FsPollDevice();

	auto key=FsInkey();
	if(FSKEY_ESC==key)
	{
		term=true;
	}

	// for bonus problem 2>> 
	player.KeepPlaying();  // Needed for supporting Linux.
	if(player.StreamPlayerReadyToAcceptNextSegment(waveStream,nextWave))
	{
		player.AddNextStreamingSegment(waveStream,nextWave);
		auto rawWave=mml.GenerateWave(100);
		nextWave.CreateFromSigned16bitStereo(YM2612::WAVE_SAMPLING_RATE,rawWave);

		// Error check is optional for the bonus point.
		if(0!=mml.GetLastErrorCode())
		{
			for(auto msg : mml.GetLastError().Format())
			{
				std::cout << msg << std::endl;
			}
		}
	}
	// for bonus problem 2<<

	// Bonus >>
	if(FSKEY_SPACE==key && 0==mode)
	{
		codedMap.Create(sourceBmp.GetWidth()/40,sourceBmp.GetHeight()/40);
		for(int y=0; y<codedMap.GetHeight(); ++y)
		{
			for(int x=0; x<codedMap.GetWidth(); ++x)
			{
				auto block=sourceBmp.CutOut(x*40,y*40,40,40);
				auto found=bmpToId.find(block);
				if(bmpToId.end()!=found)
				{
					(*codedMap.GetEditablePixelPointer(x,y))=found->second;
				}
				else
				{
					(*codedMap.GetEditablePixelPointer(x,y))=-1;
				}
			}
		}
		mode=1;
	}
	else if(FSKEY_SPACE==key && 1==mode)
	{
		codedMap.Create(sourceBmp.GetWidth()/40,sourceBmp.GetHeight()/40);
		for(int y=0; y<codedMap.GetHeight(); ++y)
		{
			for(int x=0; x<codedMap.GetWidth(); ++x)
			{
				auto block=sourceBmp.CutOut(x*40,y*40,40,40);
				std::vector <const SimpleBitmap *> matchBmp;
				if(!BitmapConsistsOfBlueAndYellowOnly(block))
				{
					for(auto &bgBmp : backgroundBlockBmp)
					{
						if(0==CompareBlueAndYellow(bgBmp,block))
						{
							matchBmp.push_back(&bgBmp);
						}
					}
					if(1==matchBmp.size())
					{
						block=*matchBmp[0];
					}
					else if(0==matchBmp.size())
					{
						printf("No match.\n");
					}
					else
					{
						printf("More than one match (%d). Take one of them.\n",(int)matchBmp.size());
						block=*matchBmp[0];
					}
				}

				auto found=bmpToId.find(block);
				if(found!=bmpToId.end())
				{
					(*codedMap.GetEditablePixelPointer(x,y))=found->second;
				}
				else
				{
					(*codedMap.GetEditablePixelPointer(x,y))=-1;
				}
			}
		}
		mode=1;
	}

	if(FSKEY_LEFT==key && 1==mode)
	{
		sx++;
	}
	if(FSKEY_RIGHT==key && 1==mode)
	{
		sx--;
	}
	if(FSKEY_UP==key && 1==mode)
	{
		sy++;
	}
	if(FSKEY_DOWN==key && 1==mode)
	{
		sy--;
	}
	// Bonus <<
}
void ApplicationMain::Draw(void) const
{
	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);

	if(0==mode)
	{
		int x=0,y=40;
		for(auto &elem : bmpToId)
		{
			auto key=elem.first; // First is bitmap.  Second is an assigned ID.
			key.Invert();
			glRasterPos2i(x,y);
			glDrawPixels(40,40,GL_RGBA,GL_UNSIGNED_BYTE,key.GetBitmapPointer());
			x+=40;
			if(1200<=x)
			{
				y+=40;
				x=0;
			}
		}
	}
	// Bonus >>
	else if(1==mode)
	{
		for(int y=0; y*40<800; ++y)
		{
			for(int x=0; x*40<1200; ++x)
			{
				if(codedMap.IsInRange(x+sx,y+sy))
				{
					auto code=*codedMap.GetPixelPointer(x+sx,y+sy);
					if(0<=code && code<blockCodeToBmp.size())
					{
						auto bmp=blockCodeToBmp[code];
						bmp.Invert();
						glRasterPos2i(x*40,y*40+40);
						glDrawPixels(40,40,GL_RGBA,GL_UNSIGNED_BYTE,bmp.GetBitmapPointer());
					}
				}
			}
		}
	}
	// Bonus <<
	FsSwapBuffers();
}
bool ApplicationMain::MustTerminate(void) const
{
	return term;
}


int main(int ac,char *av[])
{
	FsOpenWindow(0,0,1200,800,1);
	ApplicationMain app(ac,av);

	// Programming style can be polling-based or event-driven-ish.
	// No points are taken off for writing in polling-based style.
	while(true!=app.MustTerminate())
	{
		app.RunOneStep();
		app.Draw();
	}

	return 0;
}
