#ifndef QEM_H_IS_INCLUDED
#define QEM_H_IS_INCLUDED



#include <unordered_map>
#include "ysshellext.h"
#include "ysavltree.h"

void MidPointEdgeCollapse(YsShellExt &mesh,YsShellExt::VertexHandle vtHd0,YsShellExt::VertexHandle vtHd1);

double CalculateQEM(const YsShellExt &mesh,YsShellExt::VertexHandle vtHd0,YsShellExt::VertexHandle vtHd1);

void QEMExhaustive(YsShellExt &mesh);


class Edge
{
public:
	unsigned int vtKey[2];
	inline bool operator==(const Edge &incoming) const
	{
		return (vtKey[0]==incoming.vtKey[0] && vtKey[1]==incoming.vtKey[1]) ||
		       (vtKey[0]==incoming.vtKey[1] && vtKey[1]==incoming.vtKey[0]);
	}
	inline bool operator!=(const Edge &incoming) const
	{
		return (vtKey[0]!=incoming.vtKey[0] || vtKey[1]!=incoming.vtKey[1]) &&
		       (vtKey[0]!=incoming.vtKey[1] || vtKey[1]!=incoming.vtKey[0]);
	}
};


template <>
struct std::hash <Edge>
{
public:
    size_t operator()(Edge const &s) const
    {
		unsigned int larger=std::max(s.vtKey[0],s.vtKey[1]);
		unsigned int smaller=std::min(s.vtKey[0],s.vtKey[1]);
		return larger*11+smaller*7;
    };
};

class QEM
{
private:
	YsAVLTree <double,Edge> tree;
	std::unordered_map <Edge,YsAVLTree <double,Edge>::NodeHandle> edgeToTreeNode;

public:
	void Prepare(const YsShellExt &mesh);
	void Run(YsShellExt &mesh);
};



#endif
