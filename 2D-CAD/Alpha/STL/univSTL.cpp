#include "univSTL.h"
#include <stdio.h>
#include <stdint.h>
#include <vector>
#include <string>

#include <fstream>

bool parseBin_STL(std::vector <float> &vtx,std::vector <float> &nom,const char fName[])
{   //Soji's lecture code
    // With C stdio

    char buf[80];

	FILE *fp=fopen(fName,"rb");
	if(nullptr!=fp)
	{
		fread(buf,1,80,fp);

		uint32_t nTri;  // Same as unsigned int
		fread(&nTri,1,4,fp);
		printf("%d\n",nTri);

		float num[12];
		while(48==fread(num,1,48,fp)) // fread will return number of bytes read from file. !=48 means end of file.
		{
			vtx.push_back(num[3]); vtx.push_back(num[ 4]); vtx.push_back(num[ 5]);
			vtx.push_back(num[6]); vtx.push_back(num[ 7]); vtx.push_back(num[ 8]);
			vtx.push_back(num[9]); vtx.push_back(num[10]); vtx.push_back(num[11]);

			nom.push_back(num[0]); nom.push_back(num[1]); nom.push_back(num[2]);
			nom.push_back(num[0]); nom.push_back(num[1]); nom.push_back(num[2]);
			nom.push_back(num[0]); nom.push_back(num[1]); nom.push_back(num[2]);

			fread(buf,1,2,fp);
		}

		fclose(fp);

		return true;
	}
	return false;
}

bool parseASCII_STL(std::vector <float> &vtx,std::vector <float> &nom,const char fName[]);
{
    int numLines = 0;
    int numTri = 0;
    
    // open and close file to get size
	FILE *fp=fopen(fName,"rb");
    fseek(fp,0L,SEEK_END);
    long fileSize = ftell(fp);
    fclose(file);

    // open file and count lines
    FILE *fp=fopen(fName,"rb");
    for (long i=0; i < fileSize; i++)
        if(getc(fp) =='\n')
            numLines++;

    numTri = numLines / 7;

    // go back to start and skip header line
    rewind(fp);
    while(getc(fp) != '\n'); 

    for (int i = 0; i < numTri)
    {
        float num[12]

        //Reading vector
        fscanf(file,"%*s %*s %f %f %f\n",num[0],num[1],num[2]);
        //Skip outer loop
        fscanf(file,"%*s %*s");
        //Read vertex data
        fscanf(file,"%*s %f %f %f\n",num[3],num[4],num[5]);
        fscanf(file,"%*s %f %f %f\n",num[6],num[7],num[8]);
        fscanf(file,"%*s %f %f %f\n",num[9],num[10],num[12]);
        //Skip endloop
        fscanf(file,"%*s");
        //Skip endfacet
        fscanf(file,"%*s");

        vtx.push_back(num[3]); vtx.push_back(num[ 4]); vtx.push_back(num[ 5]);
        vtx.push_back(num[6]); vtx.push_back(num[ 7]); vtx.push_back(num[ 8]);
        vtx.push_back(num[9]); vtx.push_back(num[10]); vtx.push_back(num[11]);

        nom.push_back(num[0]); nom.push_back(num[1]); nom.push_back(num[2]);
        nom.push_back(num[0]); nom.push_back(num[1]); nom.push_back(num[2]);
        nom.push_back(num[0]); nom.push_back(num[1]); nom.push_back(num[2]);
    }



}

bool openSTL(std::vector <float> &vtx,std::vector <float> &nom,const char fName[])
{
    bool isOpen;

    if isASCII(fName)
        isOpen = parseASCII_STL(vtx, nom, fName)
    else
        isOpen = parseBin_STL(vtx, nom, fName)

    return isOpen;
}

bool isASCII(const char fName[])
{   // return true if the file is ASCII
    using namespace std;

    ifstream in(fName);

    char subBuf[256];

    in.read(subBuf, 256)
    string bufString(chars, in.gcount());
    transform(bufString.begin(), bufString.end(), bufString.begin(), ::tolower);

    return  (bufString.find("solid") ! = string::npos) && 
            (bufString.find("\n") ! = string::npos) && 
            (bufString.find("facet") ! = string::npos) && 
            (bufString.find("normal") ! = string::npos) && 
}

bool writeShapesToText(std::vector <float> &vtx)
{
    
    return true;
}