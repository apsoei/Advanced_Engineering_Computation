#include "simplebitmap.h"
#include "yspng.h"
#include "yspngenc.h"


/* Usage example:
{
	SimpleBitmap a;
	(You do create or load into a)

	SimpleBitmap b=a;
}
*/
SimpleBitmap::SimpleBitmap(const SimpleBitmap &incoming)
{
	this->CopyFrom(incoming);
}

/* Usage example:
{
	SimpleBitmap a,b;
	(You do create or load into a)

	b=a;
}
*/
SimpleBitmap &SimpleBitmap::operator=(const SimpleBitmap &from)
{
	this->CopyFrom(from);
	return *this;
}

SimpleBitmap::SimpleBitmap(SimpleBitmap &&incoming)
{
	this->MoveFrom(incoming);
}
SimpleBitmap &SimpleBitmap::operator=(SimpleBitmap &&incoming)
{
	this->MoveFrom(incoming);
	return *this;
}

bool SimpleBitmap::LoadPng(const char fn[])
{
	YsRawPngDecoder decoder;
	decoder.Decode(fn);
	if(0<decoder.wid && 0<decoder.hei)
	{
		MoveFrom(decoder);
		return true;
	}
	return false;
}

bool SimpleBitmap::LoadPng(FILE *fp)
{
	YsRawPngDecoder decoder;
	decoder.Decode(fp);
	if(0<decoder.wid && 0<decoder.hei)
	{
		MoveFrom(decoder);
		return true;
	}
	return false;
}

SimpleBitmap &SimpleBitmap::MoveFrom(class YsRawPngDecoder &decoder)
{
	this->SetDirect(decoder.wid,decoder.hei,decoder.rgba);
	decoder.rgba=nullptr;
	return *this;
}

SimpleBitmap SimpleBitmap::CutOut(int x0,int y0,int wid,int hei) const
{
	SimpleBitmap cutout;
	SimpleBitmapTemplate <unsigned char,4>::CutOut(cutout,x0,y0,wid,hei,0);
	return cutout;
}

void SimpleBitmap::Clear(unsigned char r,unsigned char g,unsigned char b,unsigned char a)
{
	auto bmpPtr=GetEditableBitmapPointer();
	for(unsigned int i=0; i<GetWidth()*GetHeight(); ++i)
	{
		bmpPtr[i*4  ]=r;
		bmpPtr[i*4+1]=g;
		bmpPtr[i*4+2]=b;
		bmpPtr[i*4+3]=a;
	}
}

bool SimpleBitmap::SavePng(FILE *fp) const
{
	YsRawPngEncoder encoder;
	return 0==encoder.EncodeToFile(fp,GetWidth(),GetHeight(),8,6,GetBitmapPointer());

}
bool SimpleBitmap::operator==(const SimpleBitmap &bitmapB) const
{
	return Compare(bitmapB);
}
bool SimpleBitmap::operator!=(const SimpleBitmap &bitmapB) const
{
	return true!=Compare(bitmapB);
}
bool SimpleBitmap::Compare(const SimpleBitmap &bitmapB) const
{
	if(this==&bitmapB)
	{
		return true;
	}
	if(GetWidth()==bitmapB.GetWidth() && GetHeight()==bitmapB.GetHeight())
	{
		auto a=GetBitmapPointer();
		auto b=bitmapB.GetBitmapPointer();
		for(unsigned int i=0; i<GetTotalNumComponent(); ++i)
		{
			if(a[i]!=b[i])
			{
				return false;
			}
		}
		return true;
	}
	return false;
}
