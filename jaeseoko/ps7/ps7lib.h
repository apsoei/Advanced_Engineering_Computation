#ifndef PS7LIB_IS_INCLUDED
#define PS7LIB_IS_INCLUDED

#include <vector>
#include <ysshellext.h>

std::vector <float> MakeSliceVertexArray(const YsShellExt &mesh);
std::vector <float> MakeRayIntersectionVertexArray(const YsShellExt &mesh);
void Paint(YsShellExt &mesh,YsShell::PolygonHandle from,const double angleTolerance);

#endif
