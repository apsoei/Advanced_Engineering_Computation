#include <iostream>
#include <fstream>
#include <map>
#include "mesh.h"
#include "lattice.h"



PolygonalMesh::VertexHandle PolygonalMesh::AddVertex(const YsVec3 &pos)
{
	VertexHandle vtHd;

	Vertex vtx;
	vtx.pos=pos;
	vtx.searchKey=searchKeySeed++;
	vtxList.push_back(vtx);

	vtHd.vtxPtr=vtxList.end();
	--vtHd.vtxPtr;

	return vtHd;
}

YsVec3 PolygonalMesh::GetVertexPosition(VertexHandle vtHd) const
{
	return vtHd.vtxPtr->pos;
}

unsigned int PolygonalMesh::GetSearchKey(VertexHandle vtHd) const
{
	if(NullVertex()!=vtHd)
	{
		return vtHd.vtxPtr->searchKey;
	}
	return NullSearchKey;
}

long long int PolygonalMesh::GetNumVertex(void) const
{
	return vtxList.size();
}
PolygonalMesh::VertexHandle PolygonalMesh::FirstVertex(void) const
{
	VertexHandle vtHd;
	vtHd.vtxPtr=vtxList.begin();
	return vtHd;
}
bool PolygonalMesh::MoveToNextVertex(VertexHandle &vtHd) const
{
	if(vtxList.end()!=vtHd.vtxPtr)
	{
		++vtHd.vtxPtr;
	}
	else
	{
		vtHd.vtxPtr=vtxList.begin();
	}
	return true;
}

void PolygonalMesh::SetVertexPosition(VertexHandle vtHd,const YsVec3 pos) const
{
	if(NullVertex()!=vtHd)
	{
		vtHd.vtxPtr->pos=pos;
	}
}

void PolygonalMesh::DeleteVertex(VertexHandle vtHd)
{
	if(NullVertex()!=vtHd)
	{
		vtxList.erase(vtHd.vtxPtr);
	}
}

PolygonalMesh::PolygonHandle PolygonalMesh::AddPolygon(int nPlVt,const VertexHandle plVtHd[])
{
	Polygon plg;
	plgList.push_back(plg);

	plgList.back().vtHd.resize(nPlVt);
	for(int i=0; i<nPlVt; ++i)
	{
		plgList.back().vtHd[i]=plVtHd[i];
	}
	plgList.back().searchKey=searchKeySeed++;

	PolygonHandle plHd;
	plHd.plgPtr=plgList.end();
	--plHd.plgPtr;

	RegisterPolygon(plHd);

	return plHd;
}
PolygonalMesh::PolygonHandle PolygonalMesh::AddPolygon(const std::vector <VertexHandle> &plVtHd)
{
	return AddPolygon((int)plVtHd.size(),plVtHd.data());
}

void PolygonalMesh::SetPolygonNormal(PolygonHandle plHd,const YsVec3 &nom)
{
	if(NullPolygon()!=plHd)
	{
		plHd.plgPtr->nom=nom;
	}
}

const std::vector <PolygonalMesh::VertexHandle> PolygonalMesh::GetPolygonVertex(PolygonHandle plHd) const
{
	if(NullPolygon()!=plHd)
	{
		return plHd.plgPtr->vtHd;
	}
	std::vector <VertexHandle> empty;
	return empty;
}

YsVec3 PolygonalMesh::GetNormal(PolygonHandle plHd) const
{
	if(NullPolygon()!=plHd)
	{
		return plHd.plgPtr->nom;
	}
	return YsVec3::Origin();
}

YsVec3 PolygonalMesh::GetCenter(PolygonHandle plHd) const
{
	YsVec3 cen=YsVec3::Origin();
	for(auto vtHd : GetPolygonVertex(plHd))
	{
		cen+=GetVertexPosition(vtHd);
	}
	if(0<plHd.plgPtr->vtHd.size())
	{
		cen/=(double)plHd.plgPtr->vtHd.size();
	}
	return cen;
}

unsigned int PolygonalMesh::GetPolygonNumVertex(PolygonHandle plHd) const
{
	return plHd.plgPtr->vtHd.size();
}

void PolygonalMesh::SetPolygonColor(PolygonHandle plHd,const float col[4])
{
	if(NullPolygon()!=plHd)
	{
		plHd.plgPtr->col[0]=col[0];
		plHd.plgPtr->col[1]=col[1];
		plHd.plgPtr->col[2]=col[2];
		plHd.plgPtr->col[3]=col[3];
	}
}
void PolygonalMesh::GetPolygonColor(float col[4],PolygonHandle plHd) const
{
	if(NullPolygon()!=plHd)
	{
		col[0]=plHd.plgPtr->col[0];
		col[1]=plHd.plgPtr->col[1];
		col[2]=plHd.plgPtr->col[2];
		col[3]=plHd.plgPtr->col[3];
	}
	else
	{
		col[0]=0;
		col[1]=0;
		col[2]=0;
		col[3]=0;
	}
}

void PolygonalMesh::SetPolygonVertex(PolygonHandle plHd,int nPlVt,const VertexHandle plVtHd[])
{
	UnregisterPolygon(plHd);
	plHd.plgPtr->vtHd.resize(nPlVt);
	for(int i=0; i<nPlVt; ++i)
	{
		plHd.plgPtr->vtHd[i]=plVtHd[i];
	}
	RegisterPolygon(plHd);
}
void PolygonalMesh::SetPolygonVertex(PolygonHandle plHd,const std::vector <VertexHandle> &plVtHd)
{
	SetPolygonVertex(plHd,(int)plVtHd.size(),plVtHd.data());
}

unsigned int PolygonalMesh::GetSearchKey(PolygonHandle plHd) const
{
	if(NullPolygon()!=plHd)
	{
		return plHd.plgPtr->searchKey;
	}
	return NullSearchKey;
}

long long int PolygonalMesh::GetNumPolygon(void) const
{
	return plgList.size();
}
PolygonalMesh::PolygonHandle PolygonalMesh::FirstPolygon(void) const
{
	PolygonHandle plHd;
	plHd.plgPtr=plgList.begin();
	return plHd;
}
bool PolygonalMesh::MoveToNextPolygon(PolygonHandle &plHd) const
{
	if(plgList.end()!=plHd.plgPtr)
	{
		++plHd.plgPtr;
	}
	else
	{
		plHd.plgPtr=plgList.begin();
	}
	return true;
}


std::vector <PolygonalMesh::PolygonHandle> PolygonalMesh::FindPolygonFromVertex(VertexHandle vtHd) const
{
	if(NullVertex()!=vtHd)
	{
		auto found=vtxToPlg.find(vtHd.vtxPtr->searchKey);
		if(vtxToPlg.end()!=found)
		{
			return found->second;
		}
	}
	std::vector <PolygonHandle> empty;
	return empty;
}

std::vector <PolygonalMesh::PolygonHandle> PolygonalMesh::FindPolygonFromEdgePiece(VertexHandle edVtHd0,VertexHandle edVtHd1) const
{
	EdgeKey edKey;
	edKey.edVtKey[0]=GetSearchKey(edVtHd0);
	edKey.edVtKey[1]=GetSearchKey(edVtHd1);
	auto found=edgeToPlg.find(edKey);
	if(edgeToPlg.end()!=found)
	{
		return found->second;
	}
	std::vector <PolygonalMesh::PolygonHandle> empty;
	return empty;
}
PolygonalMesh::PolygonHandle PolygonalMesh::GetNeighborPolygon(PolygonHandle plHd,int n) const
{
	auto plVtHd=GetPolygonVertex(plHd);
	if(n<plVtHd.size())
	{
		auto found=FindPolygonFromEdgePiece(plVtHd[n],plVtHd[(n+1)%plVtHd.size()]);
		if(2==found.size())
		{
			if(found[0]==plHd)
			{
				return found[1];
			}
			else if(found[1]==plHd)
			{
				return found[0];
			}
			else
			{
				std::cout << "Topological information corrupted." << std::endl;
			}
		}
	}
	return NullPolygon();
}

void PolygonalMesh::RegisterPolygon(PolygonHandle plHd)
{
	auto &plVtHd=plHd.plgPtr->vtHd;
	for(auto vtHd : plVtHd)
	{
		vtxToPlg[GetSearchKey(vtHd)].push_back(plHd);
	}
	for(int i=0; i<plVtHd.size(); ++i)
	{
		EdgeKey edKey;
		edKey.edVtKey[0]=GetSearchKey(plVtHd[i]);
		edKey.edVtKey[1]=GetSearchKey(plVtHd[(i+1)%plVtHd.size()]);
		edgeToPlg[edKey].push_back(plHd);
	}
}
void PolygonalMesh::UnregisterPolygon(PolygonHandle plHd)
{
	auto &plVtHd=plHd.plgPtr->vtHd;
	for(auto vtHd : plVtHd)
	{
		auto found=vtxToPlg.find(GetSearchKey(vtHd));
		if(vtxToPlg.end()!=found)
		{
			auto &plHdArray=found->second;
			for(auto i=plHdArray.size()-1; 0<=i && i<plHdArray.size(); --i)
			{
				if(plHdArray[i]==plHd)
				{
					plHdArray[i]=plHdArray.back();
					plHdArray.pop_back();
				}
			}
		}
		else
		{
			std::cout << "VtxToPlg Table Broken." << std::endl;
		}
	}
	for(int i=0; i<plVtHd.size(); ++i)
	{
		EdgeKey edKey;
		edKey.edVtKey[0]=GetSearchKey(plVtHd[i]);
		edKey.edVtKey[1]=GetSearchKey(plVtHd[(i+1)%plVtHd.size()]);
		for(auto j=edgeToPlg[edKey].size()-1; 0<=j && j<edgeToPlg[edKey].size(); --j)
		{
			if(edgeToPlg[edKey][j]==plHd)
			{
				edgeToPlg[edKey][j]=edgeToPlg[edKey].back();
				edgeToPlg[edKey].pop_back();
			}
		}
	}
}


bool PolygonalMesh::LoadBinSTL(const char fName[])
{
	char buf[80];

	std::ifstream ifp(fName,std::ios::binary);
	if(true==ifp.is_open())
	{
		ifp.read(buf,80);

		uint32_t nTri;
		ifp.read((char *)&nTri,4);

		float num[12];
		while(true!=ifp.eof())
		{
			ifp.read((char *)num,48);

			YsVec3 p0(num[3],num[ 4],num[ 5]);
			YsVec3 p1(num[6],num[ 7],num[ 8]);
			YsVec3 p2(num[9],num[10],num[11]);
			YsVec3 nom(num[0],num[1],num[2]);

			const VertexHandle tri[3]=
			{
				AddVertex(p0),
				AddVertex(p1),
				AddVertex(p2),
			};
			auto plHd=AddPolygon(3,tri);
			SetPolygonNormal(plHd,nom);

			const float blue[4]={0,0,1,1};
			SetPolygonColor(plHd,blue);

			ifp.read(buf,2);
		}

		ifp.close();

		StitchVertex();

		for(auto vtHd=FirstVertex(); NullVertex()!=vtHd; )
		{
			auto toCheck=vtHd;
			MoveToNextVertex(vtHd);

			if(FindPolygonFromVertex(toCheck).empty())
			{
				DeleteVertex(toCheck);
			}
		}

		return true;
	}

	return false;
}
YsVec3 PolygonalMesh::GetCenter(void) const
{
	YsVec3 cen=YsVec3::Origin();
	if(0<GetNumVertex())
	{
		for(auto vtHd=FirstVertex(); NullVertex()!=vtHd; MoveToNextVertex(vtHd))
		{
			cen+=GetVertexPosition(vtHd);
		}
		cen/=(double)GetNumVertex();
	}
	return cen;
}
void PolygonalMesh::GetBoundingBox(YsVec3 bbx[2]) const
{
	bool first=true;
	bbx[0]=YsVec3::Origin();
	bbx[1]=YsVec3::Origin();
	for(auto vtHd=FirstVertex(); NullVertex()!=vtHd; MoveToNextVertex(vtHd))
	{
		auto pos=GetVertexPosition(vtHd);
		if(true==first)
		{
			bbx[0]=pos;
			bbx[1]=pos;
			first=false;
		}
		bbx[0].SetX(std::min(bbx[0].x(),pos.x()));
		bbx[0].SetY(std::min(bbx[0].y(),pos.y()));
		bbx[0].SetZ(std::min(bbx[0].z(),pos.z()));
		bbx[1].SetX(std::max(bbx[1].x(),pos.x()));
		bbx[1].SetY(std::max(bbx[1].y(),pos.y()));
		bbx[1].SetZ(std::max(bbx[1].z(),pos.z()));
	}
}


void PolygonalMesh::StitchVertex(void)
{
	std::cout << __FUNCTION__ << std::endl;

	Lattice3d <std::vector <VertexHandle> > vtxLtc;
	std::map <unsigned int,VertexHandle> vtxMap;

	// Make a lattice
	YsVec3 bbx[2];
	GetBoundingBox(bbx);
	double d=(bbx[1]-bbx[0]).GetLength();

	bbx[0].SubX(d*0.01);
	bbx[0].SubY(d*0.01);
	bbx[0].SubZ(d*0.01);
	bbx[1].AddX(d*0.01);
	bbx[1].AddY(d*0.01);
	bbx[1].AddZ(d*0.01);

	int nPlg=GetNumPolygon();
	auto c=pow(nPlg,1.0/3.0);
	int ci=((int)c)+1;
	vtxLtc.Create(ci,ci,ci,bbx[0],bbx[1]);

	// Register while making a map.
	for(auto vtHd=FirstVertex(); NullVertex()!=vtHd; MoveToNextVertex(vtHd))
	{
		VertexHandle found=NullVertex();
		auto vtPos=GetVertexPosition(vtHd);
		auto blkIdx=vtxLtc.GetBlockIndex(vtPos);
		for(int ix=blkIdx.x()-1; ix<=blkIdx.x()+1; ++ix)
		{
			for(int iy=blkIdx.y()-1; iy<=blkIdx.y()+1; ++iy)
			{
				for(int iz=blkIdx.z()-1; iz<=blkIdx.z()+1; ++iz)
				{
					YsVec3i idx(ix,iy,iz);
					if(true==vtxLtc.IsInRange(idx))
					{
						for(auto candidateVtHd : vtxLtc[idx])
						{
							if(GetVertexPosition(candidateVtHd)==vtPos)
							{
								found=candidateVtHd;
								goto FOUND;
							}
						}
					}
				}
			}
		}
	FOUND:
		if(NullVertex()!=found)
		{
			vtxMap[GetSearchKey(vtHd)]=found;
		}
		else
		{
			if(vtxLtc.IsInRange(blkIdx))
			{
				vtxLtc[blkIdx].push_back(vtHd);
			}
		}
	}

	for(auto plHd=FirstPolygon(); NullPolygon()!=plHd; MoveToNextPolygon(plHd))
	{
		auto plVtHd=GetPolygonVertex(plHd);
		bool changed=false;
		for(auto &vtHd : plVtHd)
		{
			auto mapping=vtxMap.find(GetSearchKey(vtHd));
			if(vtxMap.end()!=mapping)
			{
				vtHd=mapping->second;
				changed=true;
			}
		}
		if(changed)
		{
			SetPolygonVertex(plHd,plVtHd);
		}
	}
}

std::vector <PolygonalMesh::VertexHandle> PolygonalMesh::GetConnectedVertex(VertexHandle fromVtHd) const
{
	std::vector <VertexHandle> vtHdToRet;
	for(auto plHd : FindPolygonFromVertex(fromVtHd))
	{
		auto plVtHd=GetPolygonVertex(plHd);
		for(int i=0; i<plVtHd.size(); ++i)
		{
			if(plVtHd[i]==fromVtHd)
			{
				const VertexHandle connected[2]=
				{
					plVtHd[(i+1)%plVtHd.size()],
					plVtHd[(i+plVtHd.size()-1)%plVtHd.size()] // [0==i ? plVtHd.size()-1 : i-1]
				};

				for(auto conn : connected)
				{
					bool found=false;
					for(auto vtHd : vtHdToRet)
					{
						if(vtHd==conn)
						{
							found=true;
							break;
						}
					}
					if(true!=found)
					{
						vtHdToRet.push_back(conn);
					}
				}
			}
		}
	}
	return vtHdToRet;
}


////////////////////////////////////////////////////////////

std::vector <PolygonalMesh::PolygonHandle> FindNNeighbor(const PolygonalMesh &mesh,PolygonalMesh::PolygonHandle plHd0,int DIST)
{
	std::unordered_map <unsigned int,unsigned int> plgToDist;
	std::vector <PolygonalMesh::PolygonHandle> bin;

	bin.push_back(plHd0);
	plgToDist[mesh.GetSearchKey(plHd0)]=0;

	for(int i=0; i<bin.size(); ++i)
	{
		auto plHd=bin[i];
		auto dist=plgToDist[mesh.GetSearchKey(plHd)];
		if(dist<DIST)
		{
			for(int n=0; n<mesh.GetPolygonNumVertex(plHd); ++n)
			{
				auto neiPlHd=mesh.GetNeighborPolygon(plHd,n);
				if(plgToDist.end()==plgToDist.find(mesh.GetSearchKey(neiPlHd)))
				{
					bin.push_back(neiPlHd);
					plgToDist[mesh.GetSearchKey(neiPlHd)]=dist+1;
				}
			}
		}
	}

	return bin;
}

