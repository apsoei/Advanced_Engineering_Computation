#include "meshlattice.h"

void MeshLatticeElem::CleanUp(void)
{
	vtHd.clear();
	plHd.clear();
}

MeshLattice::MeshLattice()
{
	meshPtr=nullptr;
}

void MeshLattice::SetDomain(const YsShellExt &mesh,int nx,int ny,int nz)
{
	meshPtr=&mesh;

	YsVec3 min,max;
	mesh.GetBoundingBox(min,max);
	auto dgn=max-min;
	auto lDgn=dgn.GetLength();
	min-=YsVec3(lDgn/100.0,lDgn/100.0,lDgn/100.0);
	max+=YsVec3(lDgn/100.0,lDgn/100.0,lDgn/100.0);
	Create(nx,ny,nz,min,max);
	for(auto &e : elem)
	{
		e.CleanUp();
	}
	for(auto vtHd=mesh.NullVertex(); true==mesh.MoveToNextVertex(vtHd); )
	{
		auto pos=mesh.GetVertexPosition(vtHd);
		auto idx=GetBlockIndex(pos);
		if(true==IsInRange(idx))
		{
			(*this)[idx].vtHd.push_back(vtHd);
		}
	}
	for(auto plHd=mesh.NullPolygon(); true==mesh.MoveToNextPolygon(plHd); )
	{
		YsBoundingBoxMaker3 mkBbx;
		for(auto vtHd : mesh.GetPolygonVertex(plHd))
		{
			mkBbx.Add(mesh.GetVertexPosition(vtHd));
		}
		YsVec3 bbx[2];
		mkBbx.Get(bbx);
		auto idxMin=GetBlockIndex(bbx[0]);
		auto idxMax=GetBlockIndex(bbx[1]);
		for(auto x=idxMin.x(); x<=idxMax.x(); ++x)
		{
			for(auto y=idxMin.y(); y<=idxMax.y(); ++y)
			{
				for(auto z=idxMin.z(); z<=idxMax.z(); ++z)
				{
					YsVec3i idx(x,y,z);
					if(true==IsInRange(idx))
					{
						(*this)[idx].plHd.push_back(plHd);
					}
				}
			}
		}
	}
}

std::vector <YsShellExt::VertexHandle> MeshLattice::FindVertex(const YsVec3 &min,const YsVec3 &max) const
{
	std::vector <YsShellExt::VertexHandle> found;
	auto idxMin=GetBlockIndex(min);
	auto idxMax=GetBlockIndex(max);
	for(auto x=idxMin.x(); x<=idxMax.x(); ++x)
	{
		for(auto y=idxMin.y(); y<=idxMax.y(); ++y)
		{
			for(auto z=idxMin.z(); z<=idxMax.z(); ++z)
			{
				YsVec3i idx(x,y,z);
				if(true==IsInRange(idx))
				{
					for(auto vtHd : (*this)[idx].vtHd)
					{
						auto pos=meshPtr->GetVertexPosition(vtHd);
						if(min.x()<=pos.x() && pos.x()<=max.x() &&
						   min.y()<=pos.y() && pos.y()<=max.y() &&
						   min.z()<=pos.z() && pos.z()<=max.z())
						{
							found.push_back(vtHd);
						}
					}
				}
			}
		}
	}
	return found;
}
