#include <iostream>
#include "mesh.h"

int main(int ac,char *av[])
{
	PolygonalMesh mesh;
	if(2<=ac && true==mesh.LoadBinSTL(av[1]))
	{
		std::cout << mesh.GetNumVertex() << " vertices." << std::endl;
		std::cout << mesh.GetNumPolygon() << " polygons." << std::endl;
	}
	return 0;
}
