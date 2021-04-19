#ifndef LATTICE_IS_INCLUDED
#define LATTICE_IS_INCLUDED

#include <ysclass.h>

// DELETE LATER
// #include <iostream>
// DELETE LATER

template <class T>
class Lattice3d
{
protected:
	int nx,ny,nz;
	std::vector <T> elem;
	YsVec3 min,max;
public:
	/*! Create a lattice with nx*ny*nz blocks.  To store nodal information, the length of the
	    storage actually allocated will be (nx+1)*(ny+1)*(nz+1).
	*/
	void Create(int nx,int ny,int nz,const YsVec3 &min,const YsVec3 &max);

	/*! Returns number of blocks in X,Y, and Z direction. */
	YSSIZE_T Nx(void) const;
	YSSIZE_T Ny(void) const;
	YSSIZE_T Nz(void) const;

	/*! Returns the dimension of one block. */
	YsVec3 GetBlockDimension(void) const;

	/*! Returns the minimum (x,y,z) of the block at (bx,by,bz). */
	YsVec3 GetBlockPosition(int ix,int iy,int iz) const;

	/*! Returns the index of the block that encloses the given position. */
	YsVec3i GetBlockIndex(const YsVec3 &pos) const;

	/*! Returns if the block index is within the valid range.
	    The lattice elements can be nodal value or cell value.  To support the nodal values,
	    this class allocates (nx+1)*(ny+1)*(nz+1) elems.  Therefore, the index is valid
	    and this function returns true, if:
	       0<=idx.x() && idx.x()<=nx && 0<=idx.y() && idx.y()<=ny && 0<=idx.z() && idx.z()<=nz.
	*/
	bool IsInRange(const YsVec3i idx) const;

	/*! Returns a reference to the lattice element at the index. */
	T &operator[](const YsVec3i idx);
	const T &operator[](const YsVec3i idx) const;
};


template <class T>
void Lattice3d<T>::Create(int nx,int ny,int nz,const YsVec3 &min,const YsVec3 &max)
{
	if(nx<1)
	{
		nx=1;
	}
	if(ny<1)
	{
		ny=1;
	}
	if(nz<1)
	{
		nz=1;
	}
	elem.resize((nx+1)*(ny+1)*(nz+1));
	this->nx=nx;
	this->ny=ny;
	this->nz=nz;
	this->min=min;
	this->max=max;
}
template <class T>
YSSIZE_T Lattice3d<T>::Nx(void) const
{
	return nx;
}
template <class T>
YSSIZE_T Lattice3d<T>::Ny(void) const
{
	return ny;
}
template <class T>
YSSIZE_T Lattice3d<T>::Nz(void) const
{
	return nz;
}
template <class T>
YsVec3 Lattice3d<T>::GetBlockDimension(void) const
{
	YsVec3 dim=max-min;
	dim.DivX((double)nx);
	dim.DivY((double)ny);
	dim.DivZ((double)nz);
	return dim;
}
template <class T>
YsVec3 Lattice3d<T>::GetBlockPosition(int ix,int iy,int iz) const
{
	auto dim=GetBlockDimension();
	dim.MulX((double)ix);
	dim.MulY((double)iy);
	dim.MulZ((double)iz);
	return min+dim;
}
template <class T>
YsVec3i Lattice3d<T>::GetBlockIndex(const YsVec3 &pos) const
{
	auto offset=pos-min;
	auto blkDim=GetBlockDimension();
	int ix=(int)(offset.x()/blkDim.x());
	int iy=(int)(offset.y()/blkDim.y());
	int iz=(int)(offset.z()/blkDim.z());
	return YsVec3i(ix,iy,iz);
}
template <class T>
bool Lattice3d<T>::IsInRange(const YsVec3i idx) const
{
	if(0<=idx.x() && idx.x()<=nx &&
	   0<=idx.y() && idx.y()<=ny &&
	   0<=idx.z() && idx.z()<=nz)
	{
		return true;
	}
	return false;
}
template <class T>
T &Lattice3d<T>::operator[](const YsVec3i idx)
{
	return elem[idx.z()*(nx+1)*(ny+1)+idx.y()*(nx+1)+idx.x()];
}
template <class T>
const T &Lattice3d<T>::operator[](const YsVec3i idx) const
{
	return elem[idx.z()*(nx+1)*(ny+1)+idx.y()*(nx+1)+idx.x()];
}

#endif
