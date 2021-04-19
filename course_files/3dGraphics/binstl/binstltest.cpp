#include <vector>
#include "binstl.h"


int main(int argc,char *argv[])
{
	std::vector <float> vtx,nom;
	OpenBinSTL(vtx,nom,argv[1]);
	return 0;
}
