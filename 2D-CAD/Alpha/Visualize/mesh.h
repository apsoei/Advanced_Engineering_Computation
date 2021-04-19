#ifndef POLYGONALMESH_IS_INCLUDED
#define POLYGONALMESH_IS_INCLUDED

#include <list>
#include <unordered_map>
#include <ysclass.h>
#include <string>
#include <algorithm>
#include <fstream>

class PolygonalMesh
{
private:
	unsigned int searchKeySeed=1;
	const unsigned int NullSearchKey=~0;

protected:
	class Vertex
	{
	public:
		YsVec3 pos;
		unsigned int searchKey;
	};
private:
	mutable std::list <Vertex> vtxList;
public:
	class VertexHandle
	{
	friend class PolygonalMesh;
	private:
		std::list <Vertex>::iterator vtxPtr;
	public:
		inline bool operator==(const VertexHandle &vtHd) const
		{
			return vtxPtr==vtHd.vtxPtr;
		}
		inline bool operator!=(const VertexHandle &vtHd) const
		{
			return vtxPtr!=vtHd.vtxPtr;
		}
	};

	VertexHandle AddVertex(const YsVec3 &pos);
	inline VertexHandle NullVertex(void) const
	{
		VertexHandle vtHd;
		vtHd.vtxPtr=vtxList.end();
		return vtHd;
	}
	YsVec3 GetVertexPosition(VertexHandle vtHd) const;
	unsigned int GetSearchKey(VertexHandle vtHd) const;

    long long int GetNumVertex(void) const;
    VertexHandle FirstVertex(void) const;
    bool MoveToNextVertex(VertexHandle &vtHd) const;

	void SetVertexPosition(VertexHandle vtHd,const YsVec3 pos) const;
	void DeleteVertex(VertexHandle vtHd);


protected:
	class Polygon
	{
	public:
		YsVec3 nom;
		float col[4];
		std::vector <VertexHandle> vtHd;
		unsigned int searchKey;
	};
private:
	mutable std::list <Polygon> plgList;
public:
	class PolygonHandle
	{
	friend class PolygonalMesh;
	private:
		std::list <Polygon>::iterator plgPtr;
	public:
		PolygonHandle(){};  // C++11 PolygonHandle()=default;
		inline bool operator==(const PolygonHandle &plHd) const
		{
			return plgPtr==plHd.plgPtr;
		}
		inline bool operator!=(const PolygonHandle &plHd) const
		{
			return plgPtr!=plHd.plgPtr;
		}
	};
	PolygonHandle AddPolygon(int nPlVt,const VertexHandle plVtHd[]);
	PolygonHandle AddPolygon(const std::vector <VertexHandle> &plVtHd);

	void SetPolygonNormal(PolygonHandle plHd,const YsVec3 &nom);

	inline PolygonHandle NullPolygon(void) const
	{
		PolygonHandle plHd;
		plHd.plgPtr=plgList.end();
		return plHd;
	}
	const std::vector <VertexHandle> GetPolygonVertex(PolygonHandle plHd) const;
	unsigned int GetSearchKey(PolygonHandle plHd) const;
	YsVec3 GetNormal(PolygonHandle plHd) const;

	void SetPolygonColor(PolygonHandle plHd,const float col[4]);
	void GetPolygonColor(float col[4],PolygonHandle plHd) const;
	void SetPolygonVertex(PolygonHandle plHd,int nPlVt,const VertexHandle plVtHd[]);
	void SetPolygonVertex(PolygonHandle plHd,const std::vector <VertexHandle> &plVtHd);

    long long int GetNumPolygon(void) const;
    PolygonHandle FirstPolygon(void) const;
    bool MoveToNextPolygon(PolygonHandle &plHd) const;



private:
	std::unordered_map <unsigned int,std::vector <PolygonHandle> > vtxToPlg;
public:
    std::vector <PolygonHandle> FindPolygonFromVertex(VertexHandle vtHd) const;



public:
	bool LoadBinSTL(const char fName[]);
	void StitchVertex(void);
	YsVec3 GetCenter(void) const;
	void GetBoundingBox(YsVec3 bbx[2]) const;

	std::vector <VertexHandle> GetConnectedVertex(VertexHandle fromVtHd) const;
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

				YsVec3 p0(num[3],num[ 4],num[ 5]);
				YsVec3 p1(num[6],num[ 7],num[ 8]);
				YsVec3 p2(num[9],num[10],num[11]);
				YsVec3 nom(num[0],num[1],num[2]);

				const VertexHandle tri[3]=
				{
					AddVertex(p0),
					AddVertex(p1),
					AddVertex(p2),
				};
				auto plHd=AddPolygon(3,tri);
				SetPolygonNormal(plHd,nom);

				const float blue[4]={0,0,1,1};
				SetPolygonColor(plHd,blue);

				fread(buf,1,2,fp);
			}

			fclose(fp);
			StitchVertex();

			for(auto vtHd=FirstVertex(); NullVertex()!=vtHd; )
			{
				auto toCheck=vtHd;
				MoveToNextVertex(vtHd);

				if(FindPolygonFromVertex(toCheck).empty())
				{
					DeleteVertex(toCheck);
				}
			}

			return true;
		}
		return false;
	}

	bool parseASCII_STL(std::vector <float> &vtx,std::vector <float> &nom,const char fName[])
	{
		int numLines = 0;
		int numTri = 0;
		
		// open and close file to get size
		FILE *fp=fopen(fName,"r");
		fseek(fp,0L,SEEK_END);
		long fileSize = ftell(fp);
		fclose(fp);

		// open file and count lines
		fp=fopen(fName,"r");
		for (long i=0; i < fileSize; i++)
			if(getc(fp) =='\n')
				numLines++;

		numTri = numLines / 7;

		// go back to start and skip header line
		rewind(fp);
		while(getc(fp) != '\n')
		{
std::cout << __FUNCTION__ << __LINE__ <<std::endl;
			for (int i = 0; i < numTri;)
			{
std::cout << __FUNCTION__ << __LINE__ <<std::endl;
				float num[12];

				//Reading vector
				fscanf(fp,"%*s %*s %f %f %f\n",num[0],num[1],num[2]);

				//Skip outer loop
				fscanf(fp,"%*s %*s");
				//Read vertex data
				fscanf(fp,"%*s %f %f %f\n",num[3],num[4],num[5]);
				fscanf(fp,"%*s %f %f %f\n",num[6],num[7],num[8]);
				fscanf(fp,"%*s %f %f %f\n",num[9],num[10],num[12]);
				//Skip endloop
				fscanf(fp,"%*s");
				//Skip endfacet
				fscanf(fp,"%*s");

				vtx.push_back(num[3]); vtx.push_back(num[ 4]); vtx.push_back(num[ 5]);
				vtx.push_back(num[6]); vtx.push_back(num[ 7]); vtx.push_back(num[ 8]);
				vtx.push_back(num[9]); vtx.push_back(num[10]); vtx.push_back(num[11]);

				nom.push_back(num[0]); nom.push_back(num[1]); nom.push_back(num[2]);
				nom.push_back(num[0]); nom.push_back(num[1]); nom.push_back(num[2]);
				nom.push_back(num[0]); nom.push_back(num[1]); nom.push_back(num[2]);

std::cout << __FUNCTION__ << __LINE__ <<std::endl;

				YsVec3 p0(num[3],num[ 4],num[ 5]);
				YsVec3 p1(num[6],num[ 7],num[ 8]);
				YsVec3 p2(num[9],num[10],num[11]);
				YsVec3 nom(num[0],num[1],num[2]);

				const VertexHandle tri[3]=
				{
					AddVertex(p0),
					AddVertex(p1),
					AddVertex(p2),
				};
				auto plHd=AddPolygon(3,tri);
				SetPolygonNormal(plHd,nom);

				const float blue[4]={0,0,1,1};
				SetPolygonColor(plHd,blue);



			}
		} 

		

		StitchVertex();

		for(auto vtHd=FirstVertex(); NullVertex()!=vtHd; )
		{
			auto toCheck=vtHd;
			MoveToNextVertex(vtHd);

			if(FindPolygonFromVertex(toCheck).empty())
			{
				DeleteVertex(toCheck);
			}
		}




	}

	bool OpenSTL(std::vector <float> &vtx,std::vector <float> &nom,const char fName[])
	{
		bool isOpen;

		if (isASCII(fName))
		{
			isOpen = parseASCII_STL(vtx, nom, fName);
		}
			
		else
		{
			isOpen = parseBin_STL(vtx, nom, fName);
		}
			
		return isOpen;
	}

	bool isASCII(const char fName[])
	{   // return true if the file is ASCII
		using namespace std;

		std::ifstream ifp(fName);

		char subBuf[256];

		ifp.read(subBuf, 256);
		std::string bufString(subBuf, ifp.gcount());
		transform(bufString.begin(), bufString.end(), bufString.begin(), ::tolower);

		return  (bufString.find("solid") != string::npos) && 
				(bufString.find("\n") != string::npos) && 
				(bufString.find("facet") != string::npos) && 
				(bufString.find("normal") != string::npos);
	}

	bool writeSTLtoMATLAB() // TODO
	{
		return true;
	}
};

#endif
