#include <chrono>
#include <iostream>
#include "meshlattice.h"

#include "ps7lib.h"

void Paint(YsShellExt &mesh,YsShell::PolygonHandle from,const double angleTolerance)
{
	// PS7-3
	// Write your code here >>
	if(mesh.NullPolygon()==from) return;

	YsVec3 myNom;
	YsVec3 neiNom;
	YsColor col;
	mesh.GetNormalOfPolygon(myNom,from);
	
	
	if(mesh.GetColor(from)!=YsRed())
	{
		mesh.SetPolygonColor(from,YsRed());
		std::vector<YsShell::PolygonHandle> todo;
		todo.push_back(from);
		while(0<todo.size())
		{
			auto curr = todo.back();
			todo.pop_back();

			for(int i=0; i<3; ++i)
			{
				auto nei = mesh.GetNeighborPolygon(curr,i);
				if(mesh.NullPolygon()!=nei && mesh.GetColor(nei)!=YsRed())
				{
					mesh.GetNormalOfPolygon(neiNom,curr);
					auto dotProd = neiNom.x()*myNom.x() + neiNom.y()*myNom.y() + neiNom.z()*myNom.z();
					auto magnitude = neiNom.GetLength() * myNom.GetLength();
					if(dotProd/magnitude > cos(angleTolerance))
					{
						mesh.SetPolygonColor(nei,YsRed());
						todo.push_back(nei);
					}
				}
				
			}
		}
	}
}

std::vector <float> MakeSliceVertexArray(const YsShellExt &mesh)
{
	std::vector <float> vtx;
	auto t0=std::chrono::high_resolution_clock::now();

	// PS7-1
	// Write your code here >>
	YsVec3 bbx[2];
	YsVec3 n;
	n.SetX(0);n.SetY(1);n.SetZ(0);
	mesh.GetBoundingBox(bbx[0],bbx[1]);
	
	auto minY = bbx[0].y();
	auto maxY = bbx[1].y();
	auto range = maxY - minY;
	float newMaxY = 0;

	for(auto plHd: mesh.AllPolygon())
	{
		auto plVtHd = mesh.GetPolygonVertex(plHd);
		auto numVtx = mesh.GetPolygonNumVertex(plHd);

		std::vector<YsVec3> temp;
		std::vector<YsVec3> vtPosList;
		float y = 0;
		for(int i =0; i<numVtx; ++i)
		{	
			auto vtPos = mesh.GetVertexPosition(plVtHd[i]);
			if(vtPos.y() > y) y = vtPos.y();
			
			vtPosList.push_back(vtPos);
			
		}
		if(y < maxY) newMaxY = y;
		else newMaxY = maxY;

		
		for(auto currY = minY; currY <= newMaxY; currY+=range/100)
		{
			
			YsPlane pln;
			YsVec3 pos(0,currY,0); 
			pln.Set(pos,n);
			
			for(int i = 0; i<vtPosList.size(); ++i)
			{
				auto vtPos0=vtPosList[i];
				auto vtPos1=vtPosList[(i+1)%vtPosList.size()];
				YsVec3 crs;
				if(YSOK == pln.GetPenetration(crs,vtPos0,vtPos1))
				{
					temp.push_back(crs);
				}
			}


			// auto vtPos0=mesh.GetVertexPosition(plVtHd[i]);
			// auto vtPos1=mesh.GetVertexPosition(plVtHd[(i+1)%numVtx]);
			// YsVec3 crs;
			// if(YSOK == pln.GetPenetration(crs,vtPos0,vtPos1))
			// {
			// 	temp.push_back(crs);
			// }
		}
		// Add only when found 2 points from one polygon to avoid the issue
		if(temp.size()>0 && 0 == temp.size()%2)
		{

			for(auto point : temp)
			{
				vtx.push_back(point.xf());
				vtx.push_back(point.yf());
				vtx.push_back(point.zf());
			}
		}
		
	}
	


	// Write your code here <<

	auto passed=std::chrono::high_resolution_clock::now()-t0;
	auto passedMS=std::chrono::duration_cast <std::chrono::milliseconds>(passed).count();
	std::cout << passedMS << " milli seconds" << std::endl;

	return vtx;
}


std::vector <float> MakeRayIntersectionVertexArray(const YsShellExt &mesh)
{
	std::vector <float> vtx;
	auto t0=std::chrono::high_resolution_clock::now();

	// PS7-2
	// Write your code here >>
	YsVec3 bbx[2];
	mesh.GetBoundingBox(bbx[0],bbx[1]);
	auto minX = bbx[0].xf();
	auto maxX = bbx[1].xf();
	auto rangeX = maxX - minX;
	auto minY = bbx[0].yf();
	auto maxY = bbx[1].yf();
	auto rangeY = maxY - minY;
	auto minZ = bbx[0].zf();
	auto maxZ = bbx[1].zf();
// std::cout << " maxZ - minZ " << maxZ-minZ <<std::endl;

	MeshLattice ltc;
	ltc.SetDomain(mesh,100,100,1);
	


	for(auto currY = minY; currY < maxY - (rangeY/100); currY += rangeY/100)
	{

		for(auto currX = minX; currX < maxX - (rangeX/100); currX += rangeX/100)
		{
			
			YsVec3 min,max;
			// auto dim = lattice.GetBlockDimension();
			min.SetX(currX);min.SetY(currY);min.SetZ(minZ);
			max.SetX(currX+rangeX/100);max.SetY(currY+rangeY/100);max.SetZ(maxZ);
			

			
			auto cenX = (max.xf() + min.xf())/2; auto cenY = (max.yf() + min.yf())/2;
			YsVec3 pos;
			pos.SetX(cenX);pos.SetY(cenY);pos.SetZ((maxZ+minZ)/2);

			// Find block idx
			auto blockIdx = ltc.GetBlockIndex(pos);
			// Get polyons in the current cell.
			auto plHdList = ltc[blockIdx].plHd;

			// Make ray line.
			YsVec3 line[2];
			line[0].SetX(cenX); line[0].SetY(cenY); line[0].SetZ(minZ - 10);
			line[1].SetX(cenX); line[1].SetY(cenY); line[1].SetZ(maxZ + 10);

			for(auto plHd : plHdList)
			{
				std::vector <YsVec3> plVtPos;
				for(auto vtHd : mesh.GetPolygonVertex(plHd))
				{
					plVtPos.push_back(mesh.GetVertexPosition(vtHd));
				}
				YsPlane pln;
				if(YSOK==pln.MakeBestFitPlane(plVtPos.size(),plVtPos.data()))
				{
					YsVec3 itsc;
					if(YSOK==pln.GetPenetration(itsc,line[0],line[1]))
					{
						auto side=YsCheckInsidePolygon3(itsc,plVtPos.size(),plVtPos.data());
						if(YSBOUNDARY==side || YSINSIDE==side)
						{
							vtx.push_back(itsc.xf());
							vtx.push_back(itsc.yf());
							vtx.push_back(itsc.zf());
						}
					}
				}
			}
				
			

		}
	}

	// Write your code here <<

	auto passed=std::chrono::high_resolution_clock::now()-t0;
	auto passedMS=std::chrono::duration_cast <std::chrono::milliseconds>(passed).count();
	std::cout << passedMS << " milli seconds" << std::endl;

	return vtx;
}

