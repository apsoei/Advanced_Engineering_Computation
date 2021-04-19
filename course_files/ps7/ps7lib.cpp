#include <chrono>
#include <iostream>
#include "meshlattice.h"

#include "ps7lib.h"

void Paint(YsShellExt &mesh,YsShell::PolygonHandle from,const double angleTolerance)
{
	// PS7-3
	// Write your code here >>

	// Write your code here <<
}

std::vector <float> MakeSliceVertexArray(const YsShellExt &mesh)
{
	std::vector <float> vtx;
	auto t0=std::chrono::high_resolution_clock::now();

	// PS7-1
	// Write your code here >>

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

	// Write your code here <<

	auto passed=std::chrono::high_resolution_clock::now()-t0;
	auto passedMS=std::chrono::duration_cast <std::chrono::milliseconds>(passed).count();
	std::cout << passedMS << " milli seconds" << std::endl;

	return vtx;
}

