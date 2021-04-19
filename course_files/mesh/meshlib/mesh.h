#ifndef POLYGONALMESH_IS_INCLUDED
#define POLYGONALMESH_IS_INCLUDED

#include <list>
#include <unordered_map>
#include <ysclass.h>



class EdgeKey
{
public:
    unsigned int edVtKey[2];

    bool operator==(const EdgeKey &rhs) const
    {
        return (edVtKey[0]==rhs.edVtKey[0] && edVtKey[1]==rhs.edVtKey[1]) ||
               (edVtKey[0]==rhs.edVtKey[1] && edVtKey[1]==rhs.edVtKey[0]);
    }
    bool operator!=(const EdgeKey &rhs) const
    {
        return (edVtKey[0]!=rhs.edVtKey[0] || edVtKey[1]!=rhs.edVtKey[1]) &&
               (edVtKey[0]!=rhs.edVtKey[1] || edVtKey[1]!=rhs.edVtKey[0]);
    }
};

template <>
struct std::hash <EdgeKey>
{
    std::size_t operator()(const EdgeKey &s) const noexcept
    {
        unsigned int larger=std::max(s.edVtKey[0],s.edVtKey[1]);
        unsigned int smaller=std::min(s.edVtKey[0],s.edVtKey[1]);
        // return larger^smaller;
        return larger*11+smaller*7;
    };
};

class PolygonalMesh
{
public:

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
	YsVec3 GetCenter(PolygonHandle plHd) const;
	unsigned int GetPolygonNumVertex(PolygonHandle plHd) const;


	void SetPolygonColor(PolygonHandle plHd,const float col[4]);
	void GetPolygonColor(float col[4],PolygonHandle plHd) const;
	void SetPolygonVertex(PolygonHandle plHd,int nPlVt,const VertexHandle plVtHd[]);
	void SetPolygonVertex(PolygonHandle plHd,const std::vector <VertexHandle> &plVtHd);

    long long int GetNumPolygon(void) const;
    PolygonHandle FirstPolygon(void) const;
    bool MoveToNextPolygon(PolygonHandle &plHd) const;



private:
	std::unordered_map <unsigned int,std::vector <PolygonHandle> > vtxToPlg;
	std::unordered_map <EdgeKey,std::vector <PolygonHandle> > edgeToPlg;

	void RegisterPolygon(PolygonHandle plHd);
	void UnregisterPolygon(PolygonHandle plHd);
public:
    std::vector <PolygonHandle> FindPolygonFromVertex(VertexHandle vtHd) const;

	std::vector <PolygonHandle> FindPolygonFromEdgePiece(VertexHandle edVtHd0,VertexHandle edVtHd1) const;
	PolygonHandle GetNeighborPolygon(PolygonHandle plHd,int n) const;



public:
	bool LoadBinSTL(const char fName[]);
	void StitchVertex(void);
	YsVec3 GetCenter(void) const;
	void GetBoundingBox(YsVec3 bbx[2]) const;

	std::vector <VertexHandle> GetConnectedVertex(VertexHandle fromVtHd) const;
};



std::vector <PolygonalMesh::PolygonHandle> FindNNeighbor(const PolygonalMesh &mesh,PolygonalMesh::PolygonHandle plHd0,int N);


#endif
