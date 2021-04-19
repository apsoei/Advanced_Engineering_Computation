#include "binstl.h"
#include <stdio.h>
#include <stdint.h>  // <-> #include <cstdint>

#include <fstream>



bool OpenBinSTL(std::vector <float> &vtx,std::vector <float> &nom,const char fName[])
{
	char buf[80];

// With C++ STL
	std::ifstream ifp(fName,std::ios::binary);
	if(true==ifp.is_open())
	{
		ifp.read(buf,80);

		uint32_t nTri;
		ifp.read((char *)&nTri,4);

		float num[12];
		while(true!=ifp.eof())
		{
			ifp.read((char *)num,48);

			vtx.push_back(num[3]); vtx.push_back(num[ 4]); vtx.push_back(num[ 5]);
			vtx.push_back(num[6]); vtx.push_back(num[ 7]); vtx.push_back(num[ 8]);
			vtx.push_back(num[9]); vtx.push_back(num[10]); vtx.push_back(num[11]);

			nom.push_back(num[0]); nom.push_back(num[1]); nom.push_back(num[2]);
			nom.push_back(num[0]); nom.push_back(num[1]); nom.push_back(num[2]);
			nom.push_back(num[0]); nom.push_back(num[1]); nom.push_back(num[2]);

			ifp.read(buf,2);
		}

		ifp.close();

		return true;
	}

// With C stdio
//	FILE *fp=fopen(fName,"rb");
//	if(nullptr!=fp)
//	{
//		fread(buf,1,80,fp);
//
//		uint32_t nTri;  // Same as unsigned int
//		fread(&nTri,1,4,fp);
//		printf("%d\n",nTri);
//
//		float num[12];
//		while(48==fread(num,1,48,fp)) // fread will return number of bytes read from file. !=48 means end of file.
//		{
//			vtx.push_back(num[3]); vtx.push_back(num[ 4]); vtx.push_back(num[ 5]);
//			vtx.push_back(num[6]); vtx.push_back(num[ 7]); vtx.push_back(num[ 8]);
//			vtx.push_back(num[9]); vtx.push_back(num[10]); vtx.push_back(num[11]);
//
//			nom.push_back(num[0]); nom.push_back(num[1]); nom.push_back(num[2]);
//			nom.push_back(num[0]); nom.push_back(num[1]); nom.push_back(num[2]);
//			nom.push_back(num[0]); nom.push_back(num[1]); nom.push_back(num[2]);
//
//			fread(buf,1,2,fp);
//		}
//
//		fclose(fp);
//
//		return true;
//	}
	return false;
}
