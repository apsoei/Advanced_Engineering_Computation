#include <vector>

bool parseBinSTL(std::vector <float> &vtx,std::vector <float> &nom,const char fName[]);
bool parseASCIISTL(std::vector <float> &vtx,std::vector <float> &nom,const char fName[]);
bool openSTL(std::vector <float> &vtx,std::vector <float> &nom,const char fName[]);
bool isBinary(char * buffer);
bool writeSTLtoMATLAB();    //TODO