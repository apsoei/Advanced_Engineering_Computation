#include "qem.h"



void MidPointEdgeCollapse(YsShellExt &mesh,YsShellExt::VertexHandle vtHd0,YsShellExt::VertexHandle vtHd1)
{
	// First delete polygons using edge (vtHd0,vtHd1).
	for(auto plHd : mesh.FindPolygonFromEdgePiece(vtHd0,vtHd1))
	{
		mesh.DeletePolygon(plHd);
	}

	// Remap vtHd0 to vtHd1.
	for(auto plHd : mesh.FindPolygonFromVertex(vtHd0))
	{
		auto plVtHd=mesh.GetPolygonVertex(plHd);
		for(auto &vtHd : plVtHd)
		{
			if(vtHd==vtHd0)
			{
				vtHd=vtHd1;
			}
		}
		mesh.SetPolygonVertex(plHd,plVtHd);
	}

	// Move vtHd1 to the center of vtHd0 and vtHd1.
	auto cen=mesh.GetCenter(vtHd0,vtHd1);
	mesh.SetVertexPosition(vtHd1,cen);

	// Delete vtHd0 which is no longer used.
	mesh.DeleteVertex(vtHd0);
}

double CalculateQEM(const YsShellExt &mesh,YsShellExt::VertexHandle vtHd0,YsShellExt::VertexHandle vtHd1)
{
	YsShellExt::VertexHandle edVtHd[2]=
	{
		vtHd0,vtHd1
	};

	auto cen=mesh.GetCenter(vtHd0,vtHd1);

	double sum=0.0;

	// For each vertex of the edge.
	for(auto vtHd : edVtHd)
	{
		// for each polygon using one of the vertices of the edge
		for(auto plHd : mesh.FindPolygonFromVertex(vtHd))
		{
			auto plVtPos=mesh.GetPolygonVertexPosition(plHd);
			if(3<=plVtPos.size())
			{
				YsPlane pln;
				if(YSOK==pln.MakePlaneFromTriangle(plVtPos[0],plVtPos[1],plVtPos[2]))
				{
					auto dist=pln.GetDistance(cen);
					sum+=dist*dist;
				}
			}
		}
	}

	return sum;
}

void QEMExhaustive(YsShellExt &mesh)
{
	double minErr=0.0;
	YsShellExt::VertexHandle minErrEdge[2]={nullptr,nullptr};

	for(auto plHd : mesh.AllPolygon())
	{
		auto plVtHd=mesh.GetPolygonVertex(plHd);
		for(int i=0; i<plVtHd.size(); ++i)
		{
			auto err=CalculateQEM(mesh,plVtHd[i],plVtHd[(i+1)%plVtHd.size()]);
			if(err<minErr || nullptr==minErrEdge[0])
			{
				minErr=err;
				minErrEdge[0]=plVtHd[i];
				minErrEdge[1]=plVtHd[(i+1)%plVtHd.size()];
			}
		}
	}

	if(nullptr!=minErrEdge[0])
	{
		MidPointEdgeCollapse(mesh,minErrEdge[0],minErrEdge[1]);
	}
}

////////////////////////////////////////////////////////////

void QEM::Prepare(const YsShellExt &mesh)
{
	for(auto plHd : mesh.AllPolygon())
	{
		auto plVtHd=mesh.GetPolygonVertex(plHd);
		for(int i=0; i<plVtHd.size(); ++i)
		{
			Edge e;
			e.vtKey[0]=mesh.GetSearchKey(plVtHd[i]);
			e.vtKey[1]=mesh.GetSearchKey(plVtHd[(i+1)%plVtHd.size()]);

			if(edgeToTreeNode.find(e)==edgeToTreeNode.end())
			{
				auto err=CalculateQEM(mesh,plVtHd[i],plVtHd[(i+1)%plVtHd.size()]);
				edgeToTreeNode[e]=tree.Insert(err,e);
			}
		}
	}
}

void QEM::Run(YsShellExt &mesh)
{
	auto first=tree.First();
	if(true==first.IsNotNull())
	{
		Edge e=tree.Value(first);
		auto edVtHd0=mesh.FindVertex(e.vtKey[0]);
		auto edVtHd1=mesh.FindVertex(e.vtKey[1]);

		if(edVtHd0!=nullptr && edVtHd1!=nullptr)
		{
			YsShellExt::VertexHandle edVtHd[2]=
			{
				edVtHd0,edVtHd1
			};
			for(auto vtHd : edVtHd)
			{
				for(auto connVtHd : mesh.GetConnectedVertex(vtHd))
				{
					Edge e;
					e.vtKey[0]=mesh.GetSearchKey(vtHd);
					e.vtKey[1]=mesh.GetSearchKey(connVtHd);
					auto found=edgeToTreeNode.find(e);
					if(found!=edgeToTreeNode.end())
					{
						tree.Delete(found->second);
						edgeToTreeNode.erase(found);
					}
				}
			}

			MidPointEdgeCollapse(mesh,edVtHd0,edVtHd1);

			for(auto connVtHd : mesh.GetConnectedVertex(edVtHd1))
			{
				auto err=CalculateQEM(mesh,connVtHd,edVtHd1);
				Edge e;
				e.vtKey[0]=mesh.GetSearchKey(edVtHd1);
				e.vtKey[1]=mesh.GetSearchKey(connVtHd);
				edgeToTreeNode[e]=tree.Insert(err,e);
			}
		}
		else
		{
			tree.Delete(first);
		}
	}
}
