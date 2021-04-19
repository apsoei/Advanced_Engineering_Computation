#include <stdio.h>
#include "mesh.h"



int main(void)
{
	PolygonalMesh mesh;
	YsVec3 p0,p1,p2,p3;

	p0.Set(1,0,0);
	p1.Set(0,1,0);
	p2.Set(0,0,1);
	p3.Set(1,1,1);

	auto vtHd0=mesh.AddVertex(p0);
	auto vtHd1=mesh.AddVertex(p1);
	auto vtHd2=mesh.AddVertex(p2);
	auto vtHd3=mesh.AddVertex(p3);

	PolygonalMesh::VertexHandle tri[2][3]=
	{
		{
			vtHd0,vtHd1,vtHd2
		}
		,
		{
			vtHd2,vtHd3,vtHd0
		}
	};

	auto plHd0=mesh.AddPolygon(3,tri[0]);
	auto plHd1=mesh.AddPolygon(3,tri[1]);


	auto foundFrom0=mesh.FindPolygonFromVertex(vtHd0);
	if(2!=foundFrom0.size())
	{
		printf("Reverse Search Corrupted.\n");
		return 1;
	}
	if((foundFrom0[0]==plHd0 && foundFrom0[1]==plHd1) ||
	   (foundFrom0[1]==plHd0 && foundFrom0[0]==plHd1))
	{
	}
	else
	{
		printf("Reverse Search Corrupted.\n");
		return 1;
	}

	auto foundFrom3=mesh.FindPolygonFromVertex(vtHd3);
	if(1!=foundFrom3.size())
	{
		printf("Reverse Search Corrupted.\n");
		return 1;
	}
	if(foundFrom3[0]!=plHd1)
	{
		printf("Reverse Search Corrupted.\n");
		return 1;
	}
	printf("Search test passed...\n");


	auto plVtHd0=mesh.GetPolygonVertex(plHd0);
	auto plVtHd1=mesh.GetPolygonVertex(plHd1);

	if(2!=mesh.GetNumPolygon())
	{
		printf("Polygon Count mismatch.\n");
		return 1;
	}

	{
		int nVtx=0;
		for(auto vtHd=mesh.FirstVertex(); vtHd!=mesh.NullVertex(); mesh.MoveToNextVertex(vtHd))
		{
			++nVtx;
		}
		if(4!=nVtx)
		{
			printf("Vertex Count mismatch.\n");
			return 1;
		}
	}

	{
		int nPlg=0;
		for(auto vtHd=mesh.FirstPolygon(); vtHd!=mesh.NullPolygon(); mesh.MoveToNextPolygon(vtHd))
		{
			++nPlg;
		}
		if(2!=nPlg)
		{
			printf("Polygon Count mismatch.\n");
			return 1;
		}
	}

	if(3!=plVtHd0.size() || 3!=plVtHd1.size())
	{
		printf("Size mismatch.\n");
		return 1;
	}

	for(int i=0; i<3; ++i)
	{
		if(plVtHd0[i]!=tri[0][i])
		{
			printf("Vertex doesn't match. %d %d\n",0,i);
			return 1;
		}
	}
	for(int i=0; i<3; ++i)
	{
		if(plVtHd1[i]!=tri[1][i])
		{
			printf("Vertex doesn't match. %d %d\n",1,i);
			return 1;
		}
	}

	printf("Vertices match.\n");

	return 0;
}
