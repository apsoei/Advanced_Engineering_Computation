#ifndef LATTICE_H_IS_INCLUDED
#define LATTICE_H_IS_INCLUDED

#include <vector>

template <class T>
class Lattice3d
{
protected:
    unsigned int nx,ny,nz;
    std::vector <T> elem;
    YsVec3 min,max;
public:
    /*! Create a lattice with nx*ny*nz blocks.  To store nodal information, the length of the
        storage actually allocated will be (nx+1)*(ny+1)*(nz+1).  */
    void Create(unsigned int nx,unsigned int ny,unsigned int nz,const YsVec3 &min,const YsVec3 &max)
    {
		elem.resize((nx+1)*(ny+1)*(nz+1));
		this->min=min;
		this->max=max;
		this->nx=nx;
		this->ny=ny;
		this->nz=nz;
	}
    /*! Returns number of blocks in X,Y, and Z direction. */
    unsigned int Nx(void) const
    {
		return nx;
	}
    unsigned int Ny(void) const
    {
		return ny;
	}
    unsigned int Nz(void) const
    {
		return nz;
	}
    /*! Returns the dimension of one block. */
    YsVec3 GetBlockDimension(void) const
    {
		auto diagonal=max-min;
		diagonal.DivX((double)nx);
		diagonal.DivY((double)ny);
		diagonal.DivZ((double)nz);
		return diagonal;
	}
    /*! Returns the minimum (x,y,z) of the block at (bx,by,bz). */
    YsVec3 GetBlockPosition(int ix,int iy,int iz) const
    {
		auto blockDim=GetBlockDimension();
		blockDim.MulX((double)ix);
		blockDim.MulY((double)iy);
		blockDim.MulZ((double)iz);
		return min+blockDim;
	}
    /*! Returns the index of the block that encloses the given position. */
    YsVec3i GetBlockIndex(const YsVec3 &pos) const
    {
		auto d=pos-min;
		auto blockDim=GetBlockDimension();

		YsVec3i idx;
		idx.SetX((int)(d.x()/blockDim.x()));
		idx.SetY((int)(d.y()/blockDim.y()));
		idx.SetZ((int)(d.z()/blockDim.z()));

		return idx;
	}
    /*! Returns if the block index is within the valid range.
        The lattice elements can be nodal value or cell value.  To support the nodal values,
        this class allocates (nx+1)*(ny+1)*(nz+1) elems.  Therefore, the index is valid
        and this function returns true, if:
           0<=idx.x() && idx.x()<=nx && 0<=idx.y() && idx.y()<=ny && 0<=idx.z() && idx.z()<=nz. */
    bool IsInRange(const YsVec3i idx) const
    {
		return (0<=idx.x() && idx.x()<=nx &&
		        0<=idx.y() && idx.y()<=ny &&
		        0<=idx.z() && idx.z()<=nz);
	}
    /*! Returns a reference to the lattice element at the index. */
    T &operator[](const YsVec3i idx)
    {
		return elem[idx.z()*(nx+1)*(ny+1)+
		            idx.y()*(nx+1)+
		            idx.x()];
	}
    const T &operator[](const YsVec3i idx) const
    {
		return elem[idx.z()*(nx+1)*(ny+1)+
		            idx.y()*(nx+1)+
		            idx.x()];
	}
};

#endif
