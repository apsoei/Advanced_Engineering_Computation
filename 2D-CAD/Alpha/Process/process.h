#ifndef PROCESS_IS_INCLUDED
#define PROCESS_IS_INCLUDED

#include <vector>
#include <iostream>
//#include "binstl.h"


class Process
{
private:
public:
	//Process();//int argc, char* argv[]);
	std::vector <float> twoDvtx, surface;
	std::vector <float> GetSameNormals(std::vector <float> vtx, std::vector <float> nom,std::vector <float> mouse_nom);
	bool Compare_Vectors(std::vector<float> vtx1, std::vector<float> vtx2, std::vector<float> surface, int NumTri, int Indx);
	std::vector <float> GetShape(std::vector <float> surface);

};

#endif
