#include <vector>
#include <chrono>
#include <ysclass.h>
#include <iostream>

class Cube
{
public:
	void MakeBlock(std::vector <float> &vtx,std::vector <float> &nom,std::vector <float> &col,float x1,float y1,float z1,float x2,float y2,float z2)
	{
		vtx.clear();
		col.clear();
		nom.clear();

		// 0  1 Quad
		// 3  2
		// 0-1-2  2-3-0  Triangles

		vtx.push_back(x1);vtx.push_back(y1);vtx.push_back(z1);
		vtx.push_back(x2);vtx.push_back(y1);vtx.push_back(z1);
		vtx.push_back(x2);vtx.push_back(y2);vtx.push_back(z1);

		vtx.push_back(x2);vtx.push_back(y2);vtx.push_back(z1);
		vtx.push_back(x1);vtx.push_back(y2);vtx.push_back(z1);
		vtx.push_back(x1);vtx.push_back(y1);vtx.push_back(z1);

		nom.push_back(0);nom.push_back(0);nom.push_back(-1);
		nom.push_back(0);nom.push_back(0);nom.push_back(-1);
		nom.push_back(0);nom.push_back(0);nom.push_back(-1);
		nom.push_back(0);nom.push_back(0);nom.push_back(-1);
		nom.push_back(0);nom.push_back(0);nom.push_back(-1);
		nom.push_back(0);nom.push_back(0);nom.push_back(-1);

		col.push_back(1);col.push_back(0);col.push_back(0);col.push_back(1);
		col.push_back(1);col.push_back(0);col.push_back(0);col.push_back(1);
		col.push_back(1);col.push_back(0);col.push_back(0);col.push_back(1);
		col.push_back(1);col.push_back(0);col.push_back(0);col.push_back(1);
		col.push_back(1);col.push_back(0);col.push_back(0);col.push_back(1);
		col.push_back(1);col.push_back(0);col.push_back(0);col.push_back(1);

		

		vtx.push_back(x1);vtx.push_back(y1);vtx.push_back(z2);
		vtx.push_back(x2);vtx.push_back(y1);vtx.push_back(z2);
		vtx.push_back(x2);vtx.push_back(y2);vtx.push_back(z2);

		vtx.push_back(x2);vtx.push_back(y2);vtx.push_back(z2);
		vtx.push_back(x1);vtx.push_back(y2);vtx.push_back(z2);
		vtx.push_back(x1);vtx.push_back(y1);vtx.push_back(z2);

		nom.push_back(0);nom.push_back(0);nom.push_back(1);
		nom.push_back(0);nom.push_back(0);nom.push_back(1);
		nom.push_back(0);nom.push_back(0);nom.push_back(1);
		nom.push_back(0);nom.push_back(0);nom.push_back(1);
		nom.push_back(0);nom.push_back(0);nom.push_back(1);
		nom.push_back(0);nom.push_back(0);nom.push_back(1);

		col.push_back(0);col.push_back(1);col.push_back(0);col.push_back(1);
		col.push_back(0);col.push_back(1);col.push_back(0);col.push_back(1);
		col.push_back(0);col.push_back(1);col.push_back(0);col.push_back(1);
		col.push_back(0);col.push_back(1);col.push_back(0);col.push_back(1);
		col.push_back(0);col.push_back(1);col.push_back(0);col.push_back(1);
		col.push_back(0);col.push_back(1);col.push_back(0);col.push_back(1);

		

		vtx.push_back(x1);vtx.push_back(y1);vtx.push_back(z1);
		vtx.push_back(x2);vtx.push_back(y1);vtx.push_back(z1);
		vtx.push_back(x2);vtx.push_back(y1);vtx.push_back(z2);

		vtx.push_back(x2);vtx.push_back(y1);vtx.push_back(z2);
		vtx.push_back(x1);vtx.push_back(y1);vtx.push_back(z2);
		vtx.push_back(x1);vtx.push_back(y1);vtx.push_back(z1);

		nom.push_back(0);nom.push_back(-1);nom.push_back(0);
		nom.push_back(0);nom.push_back(-1);nom.push_back(0);
		nom.push_back(0);nom.push_back(-1);nom.push_back(0);
		nom.push_back(0);nom.push_back(-1);nom.push_back(0);
		nom.push_back(0);nom.push_back(-1);nom.push_back(0);
		nom.push_back(0);nom.push_back(-1);nom.push_back(0);

		col.push_back(0);col.push_back(0);col.push_back(1);col.push_back(1);
		col.push_back(0);col.push_back(0);col.push_back(1);col.push_back(1);
		col.push_back(0);col.push_back(0);col.push_back(1);col.push_back(1);
		col.push_back(0);col.push_back(0);col.push_back(1);col.push_back(1);
		col.push_back(0);col.push_back(0);col.push_back(1);col.push_back(1);
		col.push_back(0);col.push_back(0);col.push_back(1);col.push_back(1);

		

		vtx.push_back(x1);vtx.push_back(y2);vtx.push_back(z1);
		vtx.push_back(x2);vtx.push_back(y2);vtx.push_back(z1);
		vtx.push_back(x2);vtx.push_back(y2);vtx.push_back(z2);

		vtx.push_back(x2);vtx.push_back(y2);vtx.push_back(z2);
		vtx.push_back(x1);vtx.push_back(y2);vtx.push_back(z2);
		vtx.push_back(x1);vtx.push_back(y2);vtx.push_back(z1);

		nom.push_back(0);nom.push_back(1);nom.push_back(0);
		nom.push_back(0);nom.push_back(1);nom.push_back(0);
		nom.push_back(0);nom.push_back(1);nom.push_back(0);
		nom.push_back(0);nom.push_back(1);nom.push_back(0);
		nom.push_back(0);nom.push_back(1);nom.push_back(0);
		nom.push_back(0);nom.push_back(1);nom.push_back(0);

		col.push_back(1);col.push_back(1);col.push_back(0);col.push_back(1);
		col.push_back(1);col.push_back(1);col.push_back(0);col.push_back(1);
		col.push_back(1);col.push_back(1);col.push_back(0);col.push_back(1);
		col.push_back(1);col.push_back(1);col.push_back(0);col.push_back(1);
		col.push_back(1);col.push_back(1);col.push_back(0);col.push_back(1);
		col.push_back(1);col.push_back(1);col.push_back(0);col.push_back(1);

		

		vtx.push_back(x1);vtx.push_back(y1);vtx.push_back(z1);
		vtx.push_back(x1);vtx.push_back(y2);vtx.push_back(z1);
		vtx.push_back(x1);vtx.push_back(y2);vtx.push_back(z2);

		vtx.push_back(x1);vtx.push_back(y2);vtx.push_back(z2);
		vtx.push_back(x1);vtx.push_back(y1);vtx.push_back(z2);
		vtx.push_back(x1);vtx.push_back(y1);vtx.push_back(z1);

		nom.push_back(-1);nom.push_back(0);nom.push_back(0);
		nom.push_back(-1);nom.push_back(0);nom.push_back(0);
		nom.push_back(-1);nom.push_back(0);nom.push_back(0);
		nom.push_back(-1);nom.push_back(0);nom.push_back(0);
		nom.push_back(-1);nom.push_back(0);nom.push_back(0);
		nom.push_back(-1);nom.push_back(0);nom.push_back(0);

		col.push_back(0.5);col.push_back(1);col.push_back(0.5);col.push_back(1);
		col.push_back(0.5);col.push_back(1);col.push_back(0.5);col.push_back(1);
		col.push_back(0.5);col.push_back(1);col.push_back(0.5);col.push_back(1);
		col.push_back(0.5);col.push_back(1);col.push_back(0.5);col.push_back(1);
		col.push_back(0.5);col.push_back(1);col.push_back(0.5);col.push_back(1);
		col.push_back(0.5);col.push_back(1);col.push_back(0.5);col.push_back(1);

		

		vtx.push_back(x2);vtx.push_back(y1);vtx.push_back(z1);
		vtx.push_back(x2);vtx.push_back(y2);vtx.push_back(z1);
		vtx.push_back(x2);vtx.push_back(y2);vtx.push_back(z2);

		vtx.push_back(x2);vtx.push_back(y2);vtx.push_back(z2);
		vtx.push_back(x2);vtx.push_back(y1);vtx.push_back(z2);
		vtx.push_back(x2);vtx.push_back(y1);vtx.push_back(z1);

		nom.push_back(1);nom.push_back(0);nom.push_back(0);
		nom.push_back(1);nom.push_back(0);nom.push_back(0);
		nom.push_back(1);nom.push_back(0);nom.push_back(0);
		nom.push_back(1);nom.push_back(0);nom.push_back(0);
		nom.push_back(1);nom.push_back(0);nom.push_back(0);
		nom.push_back(1);nom.push_back(0);nom.push_back(0);

		col.push_back(0);col.push_back(1);col.push_back(1);col.push_back(1);
		col.push_back(0);col.push_back(1);col.push_back(1);col.push_back(1);
		col.push_back(0);col.push_back(1);col.push_back(1);col.push_back(1);
		col.push_back(0);col.push_back(1);col.push_back(1);col.push_back(1);
		col.push_back(0);col.push_back(1);col.push_back(1);col.push_back(1);
		col.push_back(0);col.push_back(1);col.push_back(1);col.push_back(1);

		
	}
};

