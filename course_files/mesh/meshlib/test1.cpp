#include <stdio.h>
#include "mesh.h"



int main(void)
{
	PolygonalMesh mesh;
	YsVec3 p0,p1,p2;

	p0.Set(1,0,0);
	p1.Set(0,1,0);
	p2.Set(0,0,1);

	auto vtHd0=mesh.AddVertex(p0);
	auto vtHd1=mesh.AddVertex(p1);
	auto vtHd2=mesh.AddVertex(p2);

	if(p0!=mesh.GetVertexPosition(vtHd0) ||
	   p1!=mesh.GetVertexPosition(vtHd1) ||
	   p2!=mesh.GetVertexPosition(vtHd2))
	{
		printf("Coordinate doesn't match.\n");
		return 1;
	}

	printf("Coordinates match.\n");

	return 0;
}
