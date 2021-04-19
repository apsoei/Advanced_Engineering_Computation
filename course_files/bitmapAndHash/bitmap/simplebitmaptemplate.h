#ifndef SIMPLEBITMAP_TEMPLATE_24783_IS_INCLUDED
#define SIMPLEBITMAP_TEMPLATE_24783_IS_INCLUDED

#include <algorithm>

template <class ComponentType,int NumComponentPerPixel>
class SimpleBitmapTemplate
{
private:
	SimpleBitmapTemplate(const SimpleBitmapTemplate<ComponentType,NumComponentPerPixel> &incoming);
	SimpleBitmapTemplate<ComponentType,NumComponentPerPixel> &operator=(const SimpleBitmapTemplate<ComponentType,NumComponentPerPixel> &incoming);

private:
	int nx,ny;
	ComponentType *bmpPtr;

protected:
	/*! Returns pointer to top of the horizontal line. 
	    It must be a pointer to the first component of pixel at (0,y);

		&bmpPtr[0]                          ->First line
		&bmpPtr[nx*NumComponentPerPixel]    ->3nd line
		&bmpPtr[2*nx*NumComponentPerPixel]  ->2nd line
		    :
		    :
	*/
	ComponentType *LineTop(int y)
	{
		return bmpPtr+y*NumComponentPerPixel*nx;
	}
	const ComponentType *LineTop(int y) const
	{
		return bmpPtr+y*NumComponentPerPixel*nx;
	}

public:
	SimpleBitmapTemplate()
	{
		nx=0;
		ny=0;
		bmpPtr=nullptr;
	}
	~SimpleBitmapTemplate()
	{
		CleanUp();
	}
	void CleanUp(void)
	{
		if(nullptr!=bmpPtr)
		{
			delete [] bmpPtr;
			bmpPtr=nullptr;
		}
		nx=0;
		ny=0;
	}

	/*! This function, you will populate in the assignment. 
	    This function cuts out part of the bitmap into destination bitmap.
	    The part on this bitmap is (thisX0,thisY0)-(thisX0+wid-1,thisY0+hei-1).
	    If a pixel coordinate in this bitmap that is to be copied to the destination is outside of
	    this bitmap, all components of the destination pixel must be clearColor.
	*/
	void CutOut(SimpleBitmapTemplate <ComponentType,NumComponentPerPixel> &destination,int thisX0,int thisY0,int wid,int hei,ComponentType clearColor) const
	{
		// Create and clear the destination bitmap.
		destination.Create(wid,hei);
		for(int i=0; i<destination.GetTotalNumComponent(); ++i)
		{
			destination.bmpPtr[i]=clearColor;
		}

		// Fill your code here.
	}

	/*! Returns the total number of components in the bitmap of given width and height.
	    If, the number of components per pixel is 4, (100x100) bitmap has 4x100x100 total number of components. */
	static int GetTotalNumComponent(int wid,int hei)
	{
		return NumComponentPerPixel*wid*hei;
	}

	/*! Returns the total number of components in this bitmap. */
	int GetTotalNumComponent(void) const
	{
		return NumComponentPerPixel*nx*ny;
	}

	/*! Returns the total number of components in one single line for the given width.
	    If the width of the bitmap is 100, and the total number of components per pixel is 4,
	    4x100 components per line. */
	static int GetNumComponentPerLine(int wid)
	{
		return NumComponentPerPixel*wid;
	}

	/*! Returns the total number of components in one single line for this bitmap. */
	int GetNumComponentPerLine(void) const
	{
		return NumComponentPerPixel*nx;
	}

	/*! Creates a bitmap. */
	bool Create(int wid,int hei)
	{
		CleanUp();
		if(0<wid*hei)
		{
			bmpPtr=new ComponentType [GetTotalNumComponent(wid,hei)];
			nx=wid;
			ny=hei;
		}
		return true;
	}

	/*! Make a copy of the incoming bitmap. */
	SimpleBitmapTemplate <ComponentType,NumComponentPerPixel> &CopyFrom(const SimpleBitmapTemplate <ComponentType,NumComponentPerPixel> &incoming)
	{
		if(this!=&incoming)
		{
			Create(incoming.nx,incoming.ny);
			for(unsigned int i=0; i<GetTotalNumComponent() ; ++i)
			{
				bmpPtr[i]=incoming.bmpPtr[i];
			}
		}
		return *this;
	}

	/*! Moves the incoming bitmap to this bitmap. */
	SimpleBitmapTemplate <ComponentType,NumComponentPerPixel> &MoveFrom(SimpleBitmapTemplate <ComponentType,NumComponentPerPixel> &incoming)
	{
		if(this!=&incoming)
		{
			CleanUp();

			this->bmpPtr=incoming.bmpPtr;
			this->nx=incoming.nx;
			this->ny=incoming.ny;

			incoming.bmpPtr=nullptr;
			incoming.nx=0;
			incoming.ny=0;
		}
		return *this;
	}
	// Postpone implementation at first.

	/*! Returns the width in the number of pixels. */
	int GetWidth(void) const
	{
		return nx;
	}

	/*! Returns the height in the number of pixels. */
	int GetHeight(void) const
	{
		return ny;
	}

	/*! Returns the pointer to the bitmap. */
	const ComponentType *GetBitmapPointer(void) const
	{
		return bmpPtr;
	}

	/*! Returns the pointer to the pixel. */
	const ComponentType *GetPixelPointer(int x,int y) const
	{
		return bmpPtr+NumComponentPerPixel*(y*nx+x);
	}

	/*! Returns the mutable pointer to the bitmap. */
	ComponentType *GetEditableBitmapPointer(void)
	{
		return bmpPtr;
	}

	/*! Returns the mutable pointer to the pixel. */
	ComponentType *GetEditablePixelPointer(int x,int y)
	{
		return bmpPtr+NumComponentPerPixel*(y*nx+x);
	}

	/*! Flips the image upside down.
	    May be frequently used because the origin in the .PNG data format is lower-left, and 
	    .BMP format is upper-left.
	    We can use either way, as long as we are consistent, but we may need to go back and forth
	    occasionally.
	*/
	void Invert(void)
	{
		for(int y=0; y<ny/2; ++y)
		{
			auto *line0=LineTop(y);
			auto *line1=LineTop(ny-y-1);
			for(int x=0; x<nx*NumComponentPerPixel; ++x)
			{
				std::swap(line0[x],line1[x]);
			}
		}
	}

	/*! Sets an array and width and height dirctory.
	    After this function, this class takes an ownership of incomingBmpPtr.
	    It must not be deleted outside of this class. */
	void SetDirect(int wid,int hei,ComponentType *incomingBmpPtr)
	{
		if(incomingBmpPtr!=bmpPtr)
		{
			CleanUp();
			nx=wid;
			ny=hei;
			bmpPtr=incomingBmpPtr;
		}
	}

	/*! Returns true if (x,y) is inside the bitmap. */
	bool IsInRange(int x,int y) const
	{
		return IsXInRange(x) && IsYInRange(y);
	}

	/*! Returns true if 0<=x && x<GetWidth(). */
	bool IsXInRange(int x) const
	{
		return 0<=x && x<nx;
	}

	/*! Returns true if 0<=y && y<GetHeight(). */
	bool IsYInRange(int y) const
	{
		return 0<=y && y<ny;
	}
};

#endif
