#ifndef MESHLATTICE_IS_INCLUDED
#define MESHLATTICE_IS_INCLUDED

#include <vector>
#include <ysshellext.h>
#include "lattice.h"

class MeshLatticeElem
{
public:
	std::vector <YsShellExt::VertexHandle> vtHd;
	std::vector <YsShellExt::PolygonHandle> plHd;
	void CleanUp(void);
};

class MeshLattice : public Lattice3d <MeshLatticeElem>
{
private:
	const YsShellExt *meshPtr;
public:
	MeshLattice();
	void SetDomain(const YsShellExt &mesh,int nx,int ny,int nz);
	std::vector <YsShellExt::VertexHandle> FindVertex(const YsVec3 &min,const YsVec3 &max) const;
};

#endif
