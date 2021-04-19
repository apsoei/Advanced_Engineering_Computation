/* ////////////////////////////////////////////////////////////

File Name: render.cpp
Copyright (c) 2015 Soji Yamakawa.  All rights reserved.
http://www.ysflight.com

Redistribution and use in source and binary forms, with or without modification, 
are permitted provided that the following conditions are met:

1. Redistributions of source code must retain the above copyright notice, 
   this list of conditions and the following disclaimer.

2. Redistributions in binary form must reproduce the above copyright notice, 
   this list of conditions and the following disclaimer in the documentation 
   and/or other materials provided with the distribution.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" 
AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, 
THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR 
PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS 
BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR 
CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE 
GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) 
HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT 
LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT 
OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

//////////////////////////////////////////////////////////// */

#include <ysclass.h>
#include <yscompilerwarning.h>
#include <ysgl.h>
#include <ysglslcpp.h>

#include "fsgui3dapp.h"



// If you want to use fixed-function pipeline of OpenGL 1.x,
//   (1) comment out the following line, and
//   (2) change linking libraries in CMakeLists.txt from:
//          fsguilib_gl2 fsgui3d_gl2
//       to
//          fsguilib_gl1 fsgui3d_gl1
#define DONT_USE_FIXED_FUNCTION_PIPELINE

void FsGui3DMainCanvas::Draw(void)
{
	// Do this at the beginning of Draw funtion.  This will allow one of the elements set SetNeedRedraw(YSTRUE) 
	// within drawing function so that Draw function will be called again in the next iteragion. >>
	SetNeedRedraw(YSFALSE);
	drawEnv.SetNeedRedraw(YSFALSE);
	threeDInterface.SetNeedRedraw(YSFALSE);
	// <<

	int viewport[4];
	drawEnv.GetOpenGlCompatibleViewport(viewport);
	drawEnv.SetVerticalOrientation(YSTRUE);
	drawEnv.UpdateNearFar();


	glUseProgram(0);


	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_DEPTH_TEST);


	const YsMatrix4x4 &projMat=drawEnv.GetProjectionMatrix();
	const YsMatrix4x4 &viewMat=drawEnv.GetViewMatrix();
	const YsMatrix4x4 projViewMat=(projMat*viewMat);

	threeDInterface.SetViewport(viewport);
	threeDInterface.SetProjViewModelMatrix(projViewMat);


	glViewport(viewport[0],viewport[1],viewport[2],viewport[3]);

	GLfloat glProjMat[16];
	projMat.GetOpenGlCompatibleMatrix(glProjMat);

	GLfloat glModelviewMat[16];
	viewMat.GetOpenGlCompatibleMatrix(glModelviewMat);

#ifndef DONT_USE_FIXED_FUNCTION_PIPELINE
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glMultMatrixf(glProjMat);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glMultMatrixf(glModelviewMat);
#endif


	YsGLSLSetShared3DRendererProjection(glProjMat);
	YsGLSLSetShared3DRendererModelView(glModelviewMat);



	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);

	glDisable(GL_DEPTH_TEST);
	auto fdHd=GetCurrentField();
	if(nullptr!=fdHd)
	{
		world.Render(fdHd,YSTRUE,view_showMarkUp->GetCheck());
		if(YSTRUE==showDiff && YSTRUE==ShowDiff())
		{
			auto fieldPtr=world.GetField(fdHd);
			auto selMpHd=fieldPtr->SelectedMapPiece();
			RetroMap_World::MapPieceStore mpStore;
			for(auto mpHd : selMpHd)
			{
				mpStore.Add(mpHd);
			}
			world.RenderDiff(fdHd,mpStore,16,YsRed());
		}
	}

	{
		YsGLSLPlain3DRenderer renderer;
		renderer.SetTextureType(YSGLSL_TEX_TYPE_NONE);
	}

	if(YSTRUE==view_showPositionReferenceMarker->GetCheck())
	{
		YsGLSLPlain3DRenderer renderer;
		renderer.SetTextureType(YSGLSL_TEX_TYPE_NONE);
		renderer.SetUniformColor(YsGreen());
		float vtx[]=
		{
			position_reference_marker.xf()         ,position_reference_marker.yf(),0,
			position_reference_marker.xf()-50000.0f,position_reference_marker.yf(),0,
			position_reference_marker.xf()         ,position_reference_marker.yf(),0,
			position_reference_marker.xf()+50000.0f,position_reference_marker.yf(),0,
			position_reference_marker.xf()         ,position_reference_marker.yf(),0,
			position_reference_marker.xf()         ,position_reference_marker.yf()-50000.0f,0,
			position_reference_marker.xf()         ,position_reference_marker.yf()        ,0,
			position_reference_marker.xf()         ,position_reference_marker.yf()+50000.0f,0,
		};
		renderer.DrawVtx(YsGL::LINES,8,vtx);
	}

	// if(YSTRUE==showAnchor)
	{
		auto fieldPtr=world.GetField(fdHd);
		if(nullptr!=fieldPtr)
		{
		#ifdef GL_POINT_SPRITE
			glEnable(GL_POINT_SPRITE);
		#endif
		#ifdef GL_PROGRAM_POINT_SIZE
			glEnable(GL_PROGRAM_POINT_SIZE);
		#endif
			YsGLSLMarker3DRenderer renderer;
			renderer.SetUniformColor(YsBlue());
			renderer.SetMarkerType(YSGLSL_MARKER_TYPE_EMPTY_STAR);
			renderer.SetMarkerDimension(24.0);

			YsGLVertexBuffer vtxBuf;
			for(auto anHd : fieldPtr->AllAnchor())
			{
				auto pos2i=fieldPtr->GetAnchorPosition(anHd);
				vtxBuf.Add(YsVec3(pos2i.x(),pos2i.y(),0));
			}
			renderer.DrawVtx(YsGL::POINTS,vtxBuf.size(),vtxBuf.data());
		#ifdef GL_POINT_SPRITE
			glDisable(GL_POINT_SPRITE);
		#endif
		#ifdef GL_PROGRAM_POINT_SIZE
			glDisable(GL_PROGRAM_POINT_SIZE);
		#endif
		}
	}

	if(nullptr!=fdHd)
	{
		auto o=drawEnv.GetViewPosition(),v=drawEnv.GetViewDirection();

		YsVec2i pos=YsVec2i::Origin();
		YsPlane pln(YsOrigin(),YsZVec());
		YsVec3 crs;
		if(YSOK==pln.GetIntersection(crs,o,v))
		{
			pos.Set((int)crs.x(),(int)crs.y());
		}

		auto nextShape=world.ExpectedShape(fdHd,pos);
		auto bbx=nextShape.GetBoundingBox();
		const float vtx[]=
		{
			bbx.Min().xf(),bbx.Min().yf(),0.0f,
			bbx.Max().xf(),bbx.Min().yf(),0.0f,
			bbx.Max().xf(),bbx.Max().yf(),0.0f,
			bbx.Min().xf(),bbx.Max().yf(),0.0f,
		};
		const float col[4]={0.0f,0.0f,0.0f,0.3f};
		YsGLSLPlain3DRenderer renderer;
		renderer.SetTextureType(YSGLSL_TEX_TYPE_NONE);
		renderer.SetUniformColor(col);
		renderer.DrawVtx(YsGL::LINE_LOOP,4,vtx);

		auto d=(bbx.Max()-bbx.Min())/5.0;
		const float vtx2[]=
		{
			bbx.Min().xf()       ,bbx.Min().yf()       ,0.0f,
			bbx.Min().xf()-d.xf(),bbx.Min().yf()       ,0.0f,

			bbx.Min().xf()       ,bbx.Min().yf()       ,0.0f,
			bbx.Min().xf()       ,bbx.Min().yf()-d.yf(),0.0f,

			bbx.Max().xf()       ,bbx.Min().yf()       ,0.0f,
			bbx.Max().xf()+d.xf(),bbx.Min().yf()       ,0.0f,

			bbx.Max().xf()       ,bbx.Min().yf()       ,0.0f,
			bbx.Max().xf()       ,bbx.Min().yf()-d.yf(),0.0f,

			bbx.Max().xf()       ,bbx.Max().yf()       ,0.0f,
			bbx.Max().xf()+d.xf(),bbx.Max().yf()       ,0.0f,

			bbx.Max().xf()       ,bbx.Max().yf()       ,0.0f,
			bbx.Max().xf()       ,bbx.Max().yf()+d.yf(),0.0f,

			bbx.Min().xf()       ,bbx.Max().yf()       ,0.0f,
			bbx.Min().xf()-d.xf(),bbx.Max().yf()       ,0.0f,

			bbx.Min().xf()       ,bbx.Max().yf()       ,0.0f,
			bbx.Min().xf()       ,bbx.Max().yf()+d.yf(),0.0f,
		};
		renderer.DrawVtx(YsGL::LINES,16,vtx2);
	}

	threeDInterface.Draw();
	if(nullptr!=draw3dCallBack)
	{
		draw3dCallBack();
	}

	if(DEFAULTACTION_BOXSELECTING==defAction ||
	   DEFAULTACTION_MARKUPPOINTSELECTION_BOXSELECTING==defAction)
	{
		YsGLVertexBuffer vtxBuf;
		vtxBuf.Add<double>(defAction_DragStart.x()  ,defAction_DragStart.y()  ,0);
		vtxBuf.Add<double>(defAction_CurrentDrag.x(),defAction_DragStart.y()  ,0);
		vtxBuf.Add<double>(defAction_CurrentDrag.x(),defAction_CurrentDrag.y(),0);
		vtxBuf.Add<double>(defAction_DragStart.x(),  defAction_CurrentDrag.y(),0);

		YsGLSLPlain3DRenderer renderer;
		renderer.SetTextureType(YSGLSL_TEX_TYPE_NONE);
		renderer.SetUniformColor(YsBlue());
		renderer.DrawVtx(GL_LINE_LOOP,vtxBuf.GetN(),vtxBuf);
	}

	int nTri=0;
	YsVec3 tri[9];
	if(YSOK==FsGui3DGetArrowHeadTriangle(
	    tri+nTri*3,YsOrigin(),YsXVec(),viewport,projMat,viewMat,0.1,10,8))
	{
		++nTri;
	}
	if(YSOK==FsGui3DGetArrowHeadTriangle(
	    tri+nTri*3,YsOrigin(),YsYVec(),viewport,projMat,viewMat,0.1,10,8))
	{
		++nTri;
	}
	if(YSOK==FsGui3DGetArrowHeadTriangle(
	    tri+nTri*3,YsOrigin(),YsZVec(),viewport,projMat,viewMat,0.1,10,8))
	{
		++nTri;
	}

// Do I need an axis?
// #ifdef DONT_USE_FIXED_FUNCTION_PIPELINE
// 	{
//         auto renderer=YsGLSLSharedVariColor3DRenderer();
//         YsGLSLUse3DRenderer(renderer);
// 
// 		const float col[4]={0,0,0,1};
//         YsGLSLSet3DRendererUniformColorfv(renderer,col);
// 
//         const float vtxPos[6*3]=
// 		{
// 			0,0,0, 1,0,0,
// 			0,0,0, 0,1,0,
// 			0,0,0, 0,0,1
// 		};
//         YsGLSLDrawPrimitiveVtxfv(renderer,GL_LINES,6,vtxPos);
// 
// 		if(0<nTri)
// 		{
// 	        float triVtxPos[9*3];
// 			for(int i=0; i<nTri*3; ++i)
// 			{
// 				triVtxPos[i*3  ]=tri[i].xf();
// 				triVtxPos[i*3+1]=tri[i].yf();
// 				triVtxPos[i*3+2]=tri[i].zf();
// 			}
// 	        YsGLSLDrawPrimitiveVtxfv(renderer,GL_TRIANGLES,nTri*3,triVtxPos);
// 		}
//         YsGLSLEndUse3DRenderer(renderer);
// 	}
// #else
// 	glUseProgram(0);
// 	glColor3ub(0,0,0);
// 	glBegin(GL_LINES);
// 	glVertex3d(0.0,0.0,0.0);
// 	glVertex3d(1.0,0.0,0.0);
// 	glVertex3d(0.0,0.0,0.0);
// 	glVertex3d(0.0,1.0,0.0);
// 	glVertex3d(0.0,0.0,0.0);
// 	glVertex3d(0.0,0.0,1.0);
// 	glEnd();
// 
// 	if(0<nTri)
// 	{
// 		glBegin(GL_TRIANGLES);
// 		for(int i=0; i<nTri*3; ++i)
// 		{
// 			glVertex3dv(tri[i]);
// 		}
// 		glEnd();
// 	}
// #endif


	// 2D Drawing
#ifndef DONT_USE_FIXED_FUNCTION_PIPELINE
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0.0,(double)viewport[2],(double)viewport[3],0.0,-1.0,1.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
#endif

	YsGLSLUsePlain2DRenderer(YsGLSLSharedPlain2DRenderer());
	YsGLSLUseWindowCoordinateInPlain2DDrawing(YsGLSLSharedPlain2DRenderer(),YSTRUE);
	YsGLSLEndUsePlain2DRenderer(YsGLSLSharedPlain2DRenderer());

	glDisable(GL_DEPTH_TEST);

	glUseProgram(0);
	FsGuiCanvas::Show();

	FsSwapBuffers();
}

