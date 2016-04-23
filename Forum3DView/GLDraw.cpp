/*---------------------------------------------------------------------------
GLDraw.cpp - Вывод модели с использованием OpenGL

  ВНИМАНИЕ: модель выводится при текущих установках OpenGL,
  Rendering Context и матрицы должны быть
  проинициализированы заранее
  
---------------------------------------------------------------------------*/
// Copyright (C) 1998,1999,2000,2003,2004,2005,2006  Dmitry Tcvetkov aka TCHV
//
// All Rights Reserved
//
// Disclaimer : this text is under authority of goverment laws, US and Russian Federation
// Unauthorizing compilation, modification and re-engineering is strictly prohibited
#include "stdafx.h" //<vcl.h>
#include <math.h>
#include <gl\gl.h>
#include <gl\glu.h>
#include <algorithm>

#include "GLDraw.h"
#include "../RTree/RTree.h"
#include <complex>
#define Eps 1e-3

//#define NO_DRAW
#define NEW_DEPTH_SORT
//#define COLOR_PLATES
//#define NO_ALPHA


inline void CGLDraw::SetGlColor(TColor c)
{
	if(c == m_crCurColor)
		return;
	m_crCurColor = c;

	GLubyte r = GetRValue(c), g = GetGValue(c), b = static_cast<GLbyte>(GetBValue(c));
	glColor3ub(r, g, b);
};

inline void CGLDraw::SetGlColorAlpha(TColor c)
{
	if(c == m_crCurColor)
		return;
	m_crCurColor = c;

	GLubyte r = GetRValue(c), g = GetGValue(c), b = GetBValue(c);
#ifndef NO_ALPHA
//#ifndef NEW_DEPTH_SORT
	glColor4ub(r, g, b, 128);
#else
	glColor4ub(r, g, b, 255);
#endif
};
//#define SORT_BY_1ST




/*
inline void AddShift(S3dPoint &p, S3dPoint &s)
{
	p.x += s.x;
	p.y += s.y;
	p.z += s.z;
}
*/


inline void CGLDraw::DrawPolygon(const SViewVertex * p, NODE_NUM_TYPE NumPoints)
{
#ifdef NO_DRAW
	return;
#endif
	glBegin(NumPoints == 3 ? GL_TRIANGLES : GL_QUADS);
	for(int i = 0; i < NumPoints; i++)
		_glVertex3v(&(p[i].x));
	glEnd();
}

inline void CGLDraw::SetVertex(SViewVertex *Vertexs, int n)
{
	S3dPoint	*p = Vertexs + n;
	_glVertex3(p->x, p->y, p->z);
}

//#define COLOR_STRIPS
// Отрисовка линий через GL_LINE_STRIP
//#define SORT_FURTHEST
static UINT c = 0xff00;

bool CGLDraw::PreDrawStage(EDrawMode Mode, S3dPoint Z_Shift, bool bSmoothTransp, int nCurrentStage)
{
	switch(Mode)
	{
	case M_LINES:
		SetSmoothing();
		/*
						if(m_pOptions->bDrawOptimize && nCurrentStage == BORDER_STAGE)
						{
							SetGlColor(WIREFRAME_COLOR);
							DrawLineStrips();
							continue;
						}
						break;
		*/
	case M_FILL:
		SetSmoothing();
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		break;
	case M_FILL_AND_LINES:
	case M_FILL_AND_LINES_TRANSP:
		if(nCurrentStage == BAR_STAGE)
		{
			//               glPolygonMode(GL_FRONT_AND_BACK,GL_LINE);
			SetSmoothing();
		}
		else if(nCurrentStage == BORDER_STAGE)
		{
			if(m_pOptions->bDrawOptimize)
			{
				SetSmoothing();
				SetGlColor(m_pOptions->EdgeColor);
				DrawLineStrips();
				return true;
			}
			else
			{
				glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
				SetSmoothing();
			}
		}
		else if(nCurrentStage == FILL_STAGE)
		{
			SetGlColor(0);
			glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
			if(!m_pOptions->OGL10)
			{
				glEnable(GL_POLYGON_OFFSET_FILL);
				//glPolygonOffset(1.0, 1.0);
				glPolygonOffset(0.5f, 0.5f);
			}
			else
			{
				glPushMatrix();
				_glTranslate(Z_Shift.x, Z_Shift.y, Z_Shift.z);
			}

			if(Mode == M_FILL_AND_LINES_TRANSP)
			{
				glEnable(GL_BLEND);
				glDepthMask(GL_FALSE);
				glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
				if(bSmoothTransp)
				{
					glEnable(GL_LINE_SMOOTH);
					glDisable(GL_DEPTH_TEST);
				}
			}
		};
	}
	return false;
}

static bool Lighting = false;

static void DISABLE_LIGHTING()
{
	if(Lighting) 
	{ 
		glDisable(GL_LIGHTING); 
		Lighting = false; 
	}
}

static void ENABLE_LIGHTING(bool bLighting)
{
	if(!Lighting && bLighting)
	{ 
		glEnable(GL_LIGHTING); 
		Lighting = true; 
	}
}

void CGLDraw::DrawBar(const CViewElement & El, const SViewVertex* Vertexs, S3dPoint Z_Shift)
{
	DISABLE_LIGHTING();
	//						if(bSmoothTransp)
	//							SetGlColor(m_pOptions->BarColor);
	SetGlColor(El.Color);
	NODE_NUM_TYPE n1 = El.Points[0], n2 = El.Points[1];
	S3dPoint p1 = S3dPoint(Vertexs[n1]);
	S3dPoint p2 = S3dPoint(Vertexs[n2]);
	m_pGeometry->GetNodeCashe()->WasDrawed(n1, n2);
	glBegin(GL_LINES);
	if (El.IsContour())
	{
		_glVertex3(p1.x, p1.y, p1.z);
		_glVertex3(p2.x, p2.y, p2.z);
	}
	else if (m_pViewPos->bPerspective)
	{
		CVectorType p0(m_pViewPos->Xorg, m_pViewPos->Yorg, m_pViewPos->Zorg);
		CVectorType v1 = CVectorType(p1.x - p0.v[0], p1.y - p0.v[1], p1.z - p0.v[2]);
		CVectorType v2 = CVectorType(p2.x - p0.v[0], p2.y - p0.v[1], p2.z - p0.v[2]);
		v1.Normalize();
		v2.Normalize();
		FLOAT_TYPE zs = -2 / m_pViewPos->ScrScale;
		p1.x += v1.v[0] * zs;
		p1.y += v1.v[1] * zs;
		p1.z += v1.v[2] * zs;

		p2.x += v2.v[0] * zs;
		p2.y += v2.v[1] * zs;
		p2.z += v2.v[2] * zs;
		_glVertex3(p1.x, p1.y, p1.z);
		_glVertex3(p2.x, p2.y, p2.z);
	}
	else
	{
		glVertex3fs(p1, Z_Shift);
		glVertex3fs(p2, Z_Shift);
	}

	glEnd();
}

void CGLDraw::DrawPlate(CViewElement & El, const SViewVertex* Vertexs, EDrawMode Mode, bool bSmoothTransp, int nCurrentStage)
{
	int NumPoints = El.NumVertexs();

	SViewVertex p[4];
	for (int i1 = 0; i1 < NumPoints; i1++)
		p[i1] = Vertexs[El.Points[i1]];

	CVectorType& Norm = El.Norm;

	switch (Mode)
	{
	case M_LINES:
		{
			DISABLE_LIGHTING();
			TColor c = El.Color;
			SetGlColor(c);
			if (El.bContoured)
				DrawLines(El, p);
		}
		break;
	case M_FILL:
		ENABLE_LIGHTING(m_pDrawOptions->bLighting);
		SetGlColor(El.Color);
		CorrectNormal(Norm, p);
		_glNormal3v(Norm.GetVector());
		if (!El.bContourOnly)
			DrawPolygon(p, NumPoints);
		break;
	case M_FILL_AND_LINES:
	case M_FILL_AND_LINES_TRANSP:
		ENABLE_LIGHTING(m_pDrawOptions->bLighting);
		CorrectNormal(Norm, p);
		_glNormal3v(Norm.GetVector());
		if (nCurrentStage == BORDER_STAGE || bSmoothTransp)
		{
			if (bSmoothTransp)
			{
				SetGlColorAlpha(El.Color);
				if (!El.bContourOnly)
					DrawPolygon(p, NumPoints);
			}

			SetGlColor(m_pOptions->EdgeColor);
#ifndef NEW_DEPTH_SORT
					if (El.bContoured)
#endif
			DrawLines(El, p);
		}
		else
		{
			TColor c = El.Color;
			if (Mode == M_FILL_AND_LINES_TRANSP)
				SetGlColorAlpha(c);
			else
				SetGlColor(c);
			if (!El.bContourOnly)
				DrawPolygon(p, NumPoints);
		};
		break;
	} // switch (Mode)
	return;
}

//-Refactored---------------------------------------------------------------------
void CGLDraw::Draw(void)
{
	EDrawMode	Mode = m_pDrawOptions->Mode;
	

	m_pGeometry->SetupElementColors(m_pOptions, Mode);
	c=0xff00;
	//   glDisable(GL_DITHER);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLineWidth(GLfloat(m_pOptions->LineWidth));
	glHint(GL_LINE_SMOOTH_HINT, GL_FASTEST);
	glDisable(GL_LIGHTING);
	glDisable(GL_BLEND);
	glDisable(GL_LINE_SMOOTH);
	if(m_pGeometry == nullptr)
		return;
	m_pGeometry->GetNodeCashe()->Clear();

	int			nStages = 2; // Количество проходов для отрисовки модели

	//   if (Mode==M_FILL_AND_LINES) nStages=1;
	if(Mode == M_FILL_AND_LINES || Mode == M_FILL_AND_LINES_TRANSP)
		nStages = 3;
	m_crCurColor = TColor(0);

	CViewElement	*Elements = m_pGeometry->ElementArray.GetVector();
	UINT nOriginalVertexCount = m_pGeometry->VertexArray.size();
	int				NumElements = m_pGeometry->ElementArray.size();
	SViewVertex		*Vertexs = m_pGeometry->VertexArray.GetVector();

	S3dPoint		Z_Shift( 0, 0, -2 / m_pViewPos->ScrScale);
	m_pViewPos->Rot->Rotate_1(Z_Shift.x, Z_Shift.y, Z_Shift.z);

	if(m_pDrawOptions->bNodes)
		DrawNodes(m_pDrawOptions->bBounds); // Отрисовка узлов
	if(m_pDrawOptions->bBounds)
		DrawBounds();						// Отрисовка связей

	if(m_pDrawOptions->bAxes)
		DrawAxes();						// Отрисовка связей

	// Сортировка по глубине в полупрозрачном режиме
	if(m_pDrawOptions->bSortPlanes && Mode == M_FILL_AND_LINES_TRANSP)
	{
		SortElements(Elements, NumElements);
#ifdef NEW_DEPTH_SORT
		m_pGeometry->GetNodeCashe()->Recreate();
		Vertexs = m_pGeometry->VertexArray.GetVector();

#ifdef COLOR_PLATES
		for (int i=0; i<NumElements; i++)
		{
			Elements[i].Color = c;
			c = (c * 123 + 76587) & 0xffffff;
		}
#endif
#endif
	}
	bool bSmoothTransp = (m_pOptions->bLineSmooth && Mode == M_FILL_AND_LINES_TRANSP);
	if(bSmoothTransp)
		nStages = 1;


	if(m_pOptions->bLineSmooth)
	{
		FILL_STAGE = 0;
		BAR_STAGE = 1;
		BORDER_STAGE = 2;
	}
	else
	{
		BAR_STAGE = 0;
		BORDER_STAGE = 1;
		FILL_STAGE = 2;
	};

	//glInterleavedArrays(GL_V3F,sizeof(SViewVertex),&(m_pGeometry->VertexArray->Vertexs->x));
	for(int nCurrentStage = 0; nCurrentStage < nStages; nCurrentStage++)
	{
		if (PreDrawStage(Mode, Z_Shift, bSmoothTransp, nCurrentStage)) continue;
		//bool bLightning = true;
		//bool Lighting = false;
		ENABLE_LIGHTING(m_pDrawOptions->bLighting);
		if (nCurrentStage == BAR_STAGE)
			SetGlColor(m_pOptions->BarColor);
		for (int i = 0; i < NumElements; i++)
		{
			CViewElement &El = Elements[i];
			if (
				!El.FragmentFlag || !El.DrawFlag ||
				(Mode == M_FILL && El.IsContour())
				|| (nCurrentStage != FILL_STAGE && Mode != M_FILL && !El.bContoured)
			)
				continue;
			switch (El.Type)
			{
			case EL_LINE:
				if (nCurrentStage == BAR_STAGE && El.IsContour())
					continue;
				if (nCurrentStage != BAR_STAGE && !bSmoothTransp && (!El.IsContour() || nCurrentStage != BORDER_STAGE && (Mode != M_LINES || nCurrentStage != FILL_STAGE)))
					continue;
				DrawBar(El, Vertexs, Z_Shift);
				break;
			case EL_QUAD:
			case EL_TRIANGLE:
				if (nCurrentStage == BAR_STAGE)
					continue;
				if (nCurrentStage == BORDER_STAGE && m_pOptions->bDrawOptimize && (Mode == M_FILL_AND_LINES || Mode == M_FILL_AND_LINES_TRANSP))
					continue;

				DrawPlate(El, Vertexs, Mode, bSmoothTransp, nCurrentStage);
				break;
			} // switch (el.Type)
		} // for i
		if(m_pOptions->OGL10 && nCurrentStage == FILL_STAGE)
			glPopMatrix();
		glDisable(GL_POLYGON_OFFSET_FILL);
		glDisable(GL_BLEND);
		glDepthMask(GL_TRUE);
		glEnable(GL_DEPTH_TEST);
	}					// for nCurrentStage
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	if(Mode == M_FILL_AND_LINES_TRANSP && m_pDrawOptions->bSortPlanes)
		delete[] Elements;
	if (nOriginalVertexCount != m_pGeometry->VertexArray.size())
		m_pGeometry->VertexArray.resize(nOriginalVertexCount);
}

// Отрисовка связей
void CGLDraw::DrawBounds(void)
{
	CViewVertexArray &Vertexs = m_pGeometry->VertexArray;
	double		MVM[16];
	double		PJM[16];
	int			VP[4];
	glGetDoublev(GL_MODELVIEW_MATRIX, MVM);
	glGetDoublev(GL_PROJECTION_MATRIX, PJM);
	glGetIntegerv(GL_VIEWPORT, VP);

	glPointSize(GLfloat(m_pOptions->NodeSize));

	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	glLoadIdentity();

	// glTranslatef(0.375,0.375,0);
	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
	glLoadIdentity();
	glOrtho(0.0, VP[2], 0.0, VP[3], 0, 1);	// Установка экранной СК

	for(UINT i = 0; i < m_pGeometry->NumRealVertexs; i++)
	{
		SViewVertex p = Vertexs[i];
		if(!p.FragmentFlag || (p.Flag & VF_DELETED))
			continue;

		if((p.Flag & 63) != 0)
		{	// Отрисовка связей в одном узле
			struct TDrawBound
			{
				byte	mask;
				int		xs;
				int		ys;
			}

			B[] =
			{
				{ 1, -2, 1 },
				{ 2, 0, 1 },
				{ 4, 2, 1 },
				{ 8, -2, -1 },
				{ 16, 0, -1 },
				{ 32, 2, -1 }
			};

			double	wx, wy, wz;
			gluProject(p.x, p.y, p.z, MVM, PJM, VP, &wx, &wy, &wz);
			wx = int(wx + 0.5);
			wy = int(wy + 0.5);
			SetGlColor(BOUNDS_FRAME_COLOR);

			double	NS = m_pOptions->NodeSize;

			glBegin(GL_LINE_LOOP);	// Ограничивающий прямоугольник
			double	sx = (int(NS) + 1) % 2, sx1 = (int(NS)) % 2, sy = 1;

			glVertex3d(wx - 1.5 * NS - sx+0.5, wy - NS - sy+0.5, -wz);
			glVertex3d(wx - 1.5 * NS - sx+0.5, wy + NS + 0.5, -wz);
			glVertex3d(wx + 1.5 * NS + sx1+0.5, wy + NS + 0.5, -wz);
			glVertex3d(wx + 1.5 * NS + sx1+0.5, wy - NS - sy+0.5, -wz);
			glEnd();

			glBegin(GL_POINTS);
			for(int i1 = 0; i1 < 6; i1++)
			{
				if(p.Flag & B[i1].mask)
				{
					SetGlColor(m_pOptions->BoundsColor[i1]);
					glVertex3d(wx + NS * B[i1].xs / 2, wy + NS * B[i1].ys / 2, -wz);
				}
			}

			glEnd();
		}	// if
	}		// for
	glPopMatrix();
	glMatrixMode(GL_MODELVIEW);
	glPopMatrix();
}


void CGLDraw::UpdateMaxAxesetSize(const TAxeSet &axeSet, int &size) const
{
	for (UINT i=0; i<axeSet.size(); i++)
	{
		CSize sz = m_pRenderer->GetFontExtent(SVF_AXES, axeSet[i].m_name, nullptr);
		if (sz.cx>size)
			size = sz.cx;
		if (sz.cy>size)
			size = sz.cy;
	}

}


void CGLDraw::DrawAxes()
{
	double		MVM[16];
	double		PJM[16];
	int			VP[4];
	glEnable(GL_POLYGON_OFFSET_FILL);
	glGetDoublev(GL_MODELVIEW_MATRIX, MVM);
	glGetDoublev(GL_PROJECTION_MATRIX, PJM);
	glGetIntegerv(GL_VIEWPORT, VP);
		
	SetGlColor(m_pOptions->AxesColor);
	::glLineStipple(m_pOptions->LineWidth, 0xCCCC);
	glEnable(GL_LINE_STIPPLE);
	UINT i;
	SAxes axes = m_pGeometry->m_Axes;
	glBegin(GL_LINES);
	S3DBox &box = m_pGeometry->m_FragmentBox;
	{
		TAxeSet& axeSet = axes.X;
		for (i=0; i<axeSet.size(); i++)
		{
			FLOAT_TYPE pos = axeSet[i].m_pos;
			if (pos>=box.x_min && pos<= box.x_max)
			{
				_glVertex3(pos, box.y_min, box.z_min);
				_glVertex3(pos, box.y_max, box.z_min);
			}
		}
	}
	{
		TAxeSet& axeSet = axes.Y;
		for (i=0; i<axeSet.size(); i++)
		{
			FLOAT_TYPE pos = axeSet[i].m_pos;
			if (pos>=box.y_min && pos<= box.y_max)
			{
				_glVertex3(box.x_min, pos, box.z_min);
				_glVertex3(box.x_max, pos, box.z_min);
			}
		}
	}
	glEnd();
	glDisable(GL_LINE_STIPPLE);

	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	glLoadIdentity();
	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
	glLoadIdentity();
	glOrtho(0.0, VP[2], 0.0, VP[3], 0, -1);	// Установка экранной СК
	glMatrixMode(GL_MODELVIEW);

	int nMaxSize = 0;
	UpdateMaxAxesetSize(axes.X, nMaxSize);
	UpdateMaxAxesetSize(axes.Y, nMaxSize);
	int len = nMaxSize*10/18;
	int rad = len;

	{
		TAxeSet& axeSet = axes.X;
		for (i=0; i<axeSet.size(); i++)
		{
			FLOAT_TYPE pos = axeSet[i].m_pos;
			if (pos>=box.x_min && pos<= box.x_max)
			{
				FLOAT_TYPE d = (box.y_max-box.y_min)/400;
				S3dPoint p1(pos, box.y_min-d, box.z_min);
				S3dPoint p2(pos, box.y_max+d, box.z_min);
				DrawAxeMarks(p1, p2, len, rad, axeSet[i].m_name, MVM, PJM, VP);
			}	
		}
	}
	{
		TAxeSet& axeSet = axes.Y;
		for (i=0; i<axeSet.size(); i++)
		{
			FLOAT_TYPE pos = axeSet[i].m_pos;
			if (pos>=box.y_min && pos<= box.y_max)
			{
				FLOAT_TYPE d = (box.x_max-box.x_min)/400;
				S3dPoint p1(box.x_min-d, pos, box.z_min);
				S3dPoint p2(box.x_max+d, pos, box.z_min);
				DrawAxeMarks(p1, p2, len, rad, axeSet[i].m_name, MVM, PJM, VP);
			}
		}
	}
	{
		TAxeSet& axeSet = axes.Z;
		for (i=0; i<axeSet.size(); i++)
		{
			FLOAT_TYPE pos = axeSet[i].m_pos;
			if (pos>=box.z_min && pos<= box.z_max &&  axeSet[i].m_name.GetLength()>0)
			{
				FLOAT_TYPE d = (box.x_max-box.x_min)/400;
				S3dPoint p1(box.x_min-d, box.y_min - d, pos);
				DrawAxeZMark(p1, axeSet[i].m_name, MVM, PJM, VP);
			}
		}
	}


	glMatrixMode(GL_PROJECTION);
	glPopMatrix();
	glMatrixMode(GL_MODELVIEW);
	glPopMatrix();
}

void CGLDraw::DrawTextList(int nFontNo, LPCTSTR pszName) const
{
	glPushAttrib(GL_LIST_BIT);							// Pushes The Display List Bits
	glListBase(m_pRenderer->m_fontBases[nFontNo]);									// Sets The Base Character to 0
#ifdef UNICODE
	glCallLists(_tcslen(pszName), GL_UNSIGNED_SHORT, pszName);	// Draws The Display List Text
#else
	glCallLists(_tcslen(pszName), GL_UNSIGNED_BYTE, pszName);	// Draws The Display List Text
#endif
	glPopAttrib();	// Pops The Display List Bits
}

void CGLDraw::DrawAxeZMark(const S3dPoint &p1, LPCTSTR pszName, double MVM[], double PJM[], int VP[])
{
	double wx,wy,wz;
	double fScale=m_pRenderer->m_fontSizes[SVF_AXES];
	gluProject(p1.x, p1.y, p1.z, MVM, PJM, VP, &wx, &wy, &wz);
	double M_PI_2 = 2*atan(1.0);
	double a = atan2(sin(m_pViewPos->Rot->Fz_rot), cos(m_pViewPos->Rot->Fz_rot))/M_PI_2;
	if (a<-1)
		a=-1+2*(a+2);
	else if (a<0)
		a=1;
	else if (a<1)
		a=1-2*a;
	else
		a=-1;
	wx -= 2.5*fScale*a + 1.5*fScale;//4*fScale;
	glBegin(GL_LINES);
		glVertex3d(wx, wy, wz);
		glVertex3d(wx+3*fScale, wy, wz);
	glEnd();

	glBegin(GL_LINE_LOOP);
		glVertex3d(wx+fScale/2, wy, wz);
		glVertex3d(wx+fScale, wy+fScale, wz);
		glVertex3d(wx, wy+fScale, wz);
	glEnd();

	TEXTMETRIC tm;
	CSize sz = m_pRenderer->GetFontExtent(SVF_AXES, pszName, &tm);
	glPushMatrix();
	double fNameX = wx+fScale*1.2;
	//glTranslated(fNameX, wy+tm.tmDescent, 0);
	glRasterPos3d(0, 0, wz);
	glBitmap(0, 0, 0, 0, static_cast<GLfloat>(fNameX), GLfloat(wy+tm.tmDescent), nullptr);
	DrawTextList(SVF_AXES, pszName);
	glPopMatrix();

	SetGlColor(m_pOptions->BackgroundColor);
	glPolygonOffset(0,1);
	double dBorder = fScale*0.1;
	glBegin(GL_POLYGON);
		glVertex3d(fNameX-dBorder, wy+dBorder, wz);
		glVertex3d(fNameX+/*3*fScale*/+ sz.cx +dBorder, wy+dBorder, wz);
		glVertex3d(fNameX+/*3*fScale*/+ sz.cx +dBorder, wy+fScale+dBorder, wz);
		glVertex3d(fNameX-dBorder, wy+fScale+dBorder, wz);
	glEnd();
	glBegin(GL_POLYGON);
		glVertex3d(wx+fScale/2, wy, wz);
		glVertex3d(wx+fScale, wy+fScale, wz);
		glVertex3d(wx, wy+fScale, wz);
	glEnd();
	glPolygonOffset(0,0);
	SetGlColor(m_pOptions->AxesColor);

}
void CGLDraw::DrawAxeMarks(const S3dPoint &p1, const S3dPoint &p2, double len, double rad,  LPCTSTR pszName, double MVM[], double PJM[], int VP[])
{
	double w1x,w1y,w1z;
	double w2x,w2y,w2z;
	double nx1,ny1;
	double nx2,ny2;
	gluProject(p1.x, p1.y, p1.z, MVM, PJM, VP, &w1x, &w1y, &w1z);
	gluProject(p2.x, p2.y, p2.z, MVM, PJM, VP, &w2x, &w2y, &w2z);
	double dx = w1x-w2x;
	double dy = w1y-w2y;
	if (fabs(dx)<1 && fabs(dy)<1)
	{
		nx1 = nx2 = 0;
		ny1 = ny2 = -1;
	}
	else
	{
		double len1 = sqrt(dx*dx+dy*dy);
		nx1 = dx/len1;
		ny1 = dy/len1;
		nx2 = -nx1;
		ny2 = -ny1;
	}
	if (w1z>1.0 || w2z>1.0)
	{
		nx1 = -nx1;
		nx2 = -nx2;
		ny1 = -ny1;
		ny2 = -ny2;
	}
	DrawAxeMark(w1x, w1y, w1z, nx1, ny1, len, rad, pszName);
	DrawAxeMark(w2x, w2y, w2z, nx2, ny2, len, rad, pszName);
}


void CGLDraw::DrawAxeMark(double wx, double wy, double wz, double nx, double ny, double MarkLen, double radius, LPCTSTR pszName)
{
	glPolygonOffset(0,0);
	glBegin(GL_LINES);
	glVertex3d(wx, wy, wz);
	wx += nx*MarkLen;
	wy += ny*MarkLen;
	glVertex3d(wx, wy, wz);
	wx += nx*radius;
	wy += ny*radius;
	glEnd();
	glBegin(GL_LINE_LOOP);
		int nSegments = 16;
		double M_2PI = 8*atan(1.0);
		for (int i=0;i<nSegments;i++)
		{
			glVertex3d(wx+radius*sin(i*M_2PI/nSegments), wy+radius*cos(i*M_2PI/nSegments), wz);
		}
	glEnd();
	glPushMatrix();
#ifndef USE_FONT_BITMAPS
		S3dPoint sz = GetFontExtents(pszName);
		glTranslated(wx-sz.x/2, wy-sz.y/2,  wz);
		glScaled(m_FontSize, m_FontSize, m_FontSize);
		glPushAttrib(GL_LIST_BIT);							// Pushes The Display List Bits
		glListBase(m_pRenderer->m_fontBases[SVF_AXES]);									// Sets The Base Character to 0
		glCallLists(strlen(pszName), GL_UNSIGNED_BYTE, pszName);	// Draws The Display List Text
		glPopAttrib();	// Pops The Display List Bits
#else
		//glTranslated(wx, wy,  wz);
		TEXTMETRIC tm;
		CSize sz = m_pRenderer->GetFontExtent(SVF_AXES, pszName, &tm);
		glRasterPos3d(0, 0, wz);
		//glTranslated(wx - sz.cx/2, wy + tm.tmDescent -sz.cy/2, 0);
		glBitmap(0, 0, 0, 0, GLfloat(wx - sz.cx/2), GLfloat(wy + tm.tmDescent -sz.cy/2), nullptr);
		DrawTextList(SVF_AXES, pszName);
#endif
//		glBegin(GL_LINES);
//		  glVertex3d(0,-20,-0.1);
//		  glVertex3d(0,20,0.1);
//		glEnd();
	glPopMatrix();
/*
	glBegin(GL_LINE_LOOP);
		glVertex3d(wx,wy,wz);
		glVertex3d(wx+sz.cx,wy,wz);
		glVertex3d(wx+sz.cx,wy+sz.cy,wz);
		glVertex3d(wx,wy+sz.cy,wz);
	glEnd();
*/

	SetGlColor(m_pOptions->BackgroundColor);
	glPolygonOffset(0,1);
	glBegin(GL_POLYGON);
		for (int i=0;i<nSegments;i++)
		{
			glVertex3d(wx+radius*sin(i*M_2PI/nSegments), wy+radius*cos(i*M_2PI/nSegments), wz);
		}
	glEnd();
	glPolygonOffset(0,0);
	SetGlColor(m_pOptions->AxesColor);
}



const FLOAT_TYPE Eps1 = 1e-4f;

class CSortedViewElement : public CViewElement
{
public:
	CSortedViewElement(const CViewElement &el)
		: CViewElement(el), xMax(0), xMin(0), yMax(0), yMin(0), zMax(0), zMin(0), m_pOriginal(nullptr)
	{
		//FragmentFlag = true;
	}

	void SetExtents(const CViewVertexArray &Vertexs)
	{
		const SViewVertex &pt = Vertexs[Points[0]];
		xMax = xMin = pt.x;
		yMax = yMin = pt.y;
		zMax = zMin = pt.z;
		for (int i=1;i<NumVertexs();i++)
		{
			const SViewVertex &pt1 = Vertexs[Points[i]];
			xMax = max(xMax,pt1.x);
			xMin = min(xMin,pt1.x);
			yMax = max(yMax,pt1.y);
			yMin = min(yMin,pt1.y);
			zMax = max(zMax,pt1.z);
			zMin = min(zMin,pt1.z);
		}
	}
	
	bool IsOwerlappingDepth(const CSortedViewElement &El) const
	{
		return zMax > El.zMin && zMin<El.zMax;
	}
	
	bool IsOnOppositeSideOf(const CSortedViewElement &El, const CViewVertexArray &Vertexs, CVectorType &ptEye, bool bPersp)
	{
		if (El.NumVertexs() == 2)
			return true;
		FLOAT_TYPE d = El.Norm.DotProduct(Vertexs[El.Points[0]]);
		FLOAT_TYPE resEye = bPersp ? ptEye.DotProduct(El.Norm) -d : El.Norm.v[2];
		if (fabs(resEye)<Eps1)
			return true;
		resEye = resEye>0 ? 1.0f: -1.0f;
		for (int i=0; i<NumVertexs(); i++)
		{
			FLOAT_TYPE res = (CVectorType(Vertexs[Points[i]]).DotProduct(El.Norm)-d)*resEye;
			if (fabs(res)<Eps1)
				continue;
			if (res>0)
				return false;
		}
		return true;
	}

	bool IsOnSameSideOf(const CSortedViewElement &El, const CViewVertexArray &Vertexs, CVectorType &ptEye, bool bPersp)
	{
		if (El.NumVertexs() == 2)
			return false;
		FLOAT_TYPE d = El.Norm.DotProduct(Vertexs[El.Points[0]]);
		FLOAT_TYPE resEye = bPersp ? ptEye.DotProduct(El.Norm) -d : El.Norm.v[2];
		if (fabs(resEye)<Eps1)
			return true;
		resEye = resEye>0 ? 1.0f: -1.0f;
		for (int i=0; i<NumVertexs(); i++)
		{
			FLOAT_TYPE res = (CVectorType(Vertexs[Points[i]]).DotProduct(El.Norm)-d)*resEye;
			if (fabs(res)<Eps1)
				continue;
			if (res<0)
				return false;
		}
		return true;
	}

	static FLOAT_TYPE GetDistanceToLine(const SViewVertex &pt, int nPoint1, int nPoint2, const CViewVertexArray &Vertexs)
	{
		S3dPoint pt1 = S3dPoint(Vertexs[nPoint1]);
		S3dPoint pt2 = S3dPoint(Vertexs[nPoint2]);
		FLOAT_TYPE a= pt2.y-pt1.y;
		FLOAT_TYPE b= pt1.x-pt2.x;
		FLOAT_TYPE c = a*pt1.x+b*pt1.y;
		return a*pt.x+b*pt.y-c;
	}

	bool PointIsInside(const SViewVertex &pt, const CViewVertexArray &Vertexs) const
	{
		if (NumVertexs()==2)
			return false;
		FLOAT_TYPE fOldDist=GetDistanceToLine(pt, Points[0], Points[1], Vertexs);
		if (fabs(fOldDist)<Eps1)
			return false;
		for (int i=1; i<NumVertexs();i++)
		{
			FLOAT_TYPE fDist=GetDistanceToLine(pt, Points[i], Points[(i+1)%NumVertexs()], Vertexs);
			FLOAT_TYPE f=fDist*fOldDist;
			if (fabs(fDist)<Eps1 || f<0)
				return false;
			fOldDist = fDist;			
		}
		return true;
	}

	bool AnyPointIsInside(const CSortedViewElement &El, const CViewVertexArray &Vertexs) const
	{
		// Либо одна из вершин, либо центр полигона
		SViewVertex pt;
		pt.x = pt.y =0;
		for (int i=0; i<NumVertexs();i++)
		{
			const SViewVertex &ptCurr = Vertexs[Points[i]];
			if (El.PointIsInside(ptCurr, Vertexs))
				return true;
			pt.x += ptCurr.x;
			pt.y += ptCurr.y;
		}
		pt.x/=NumVertexs();
		pt.y/=NumVertexs();
		return El.PointIsInside(pt,Vertexs);
	}
	// Проверка, пересекаются ли ПРОЕКЦИИ отрезков [p1,p2] и [p2,p3]
	static bool IsRibsIntersecting(int p1,int p2,int p3,int p4, const CViewVertexArray &Vertexs)
	{
		S3dPoint pt1 = S3dPoint(Vertexs[p1]);
		S3dPoint pt2 = S3dPoint(Vertexs[p2]);
		S3dPoint pt3 = S3dPoint(Vertexs[p3]);
		S3dPoint pt4 = S3dPoint(Vertexs[p4]);
		FLOAT_TYPE db = (pt4.y - pt3.y)*(pt2.x-pt1.x)+(pt3.x-pt4.x)*(pt2.y-pt1.y);
		if (fabs(db)<Eps1)
			return false;
		FLOAT_TYPE t=((pt4.y-pt3.y)*(pt3.x-pt1.x)+(pt3.x-pt4.x)*(pt3.y-pt1.y))/db;
		if (t<0+Eps1 || t>1.0f-Eps1)
			return false;
		FLOAT_TYPE u=((pt2.y-pt1.y)*(pt3.x-pt1.x)+(pt1.x-pt2.x)*(pt3.y-pt1.y))/db;
		if (u<0+Eps1 || u>1.0f-Eps1)
			return false;
		return true;
	}

	bool ProjectedFacesAreOwerlapped(const CSortedViewElement &El, const CViewVertexArray &Vertexs)
	{
		for (int i=0;i<NumVertexs(); i++)
			for (int j=0; j<El.NumVertexs(); j++)
				if (IsRibsIntersecting(Points[i],Points[(i+1)%NumVertexs()],El.Points[j],El.Points[(j+1)%El.NumVertexs()], Vertexs))
					return true;
		return AnyPointIsInside(El, Vertexs) || El.AnyPointIsInside(*this, Vertexs);
	}
	// Сечение отрезка [p1,p0] плоскостью этого элемента. Результат лежит в диапазоне [0,1] если плоскость пересекает отрезок
	FLOAT_TYPE SectByPlane(const SViewVertex& p0, const SViewVertex& p1, const CViewVertexArray &Vertexs)
	{
		FLOAT_TYPE d = Norm.DotProduct(Vertexs[Points[0]]);
		FLOAT_TYPE d1 = CVectorType(p1.x-p0.x, p1.y-p0.y,p1.z-p0.z).DotProduct(Norm);
		if (fabs(d1)<Eps1)
			return 2;
		return (d-Norm.DotProduct(p0))/ d1;
	}
	bool BreakByPlaneOf(CSortedViewElement &Q, CGLDraw &glDraw, CViewVertexArray &Vertexs, CViewVertexArray &ProjectedVertexs,
	                    std::vector <CSortedViewElement> &vecSorted, int k)
	{
		if (Type == EL_QUAD)
			return glDraw.BreakQuad(Vertexs, ProjectedVertexs, vecSorted, k, Q,  *this);
		if (Type==EL_TRIANGLE)
			return glDraw.BreakTriangle(Vertexs, ProjectedVertexs, vecSorted, k, Q,  *this);
		return false;
	}
	RTreeLib::Rectangle GetRect() const
	{
		return RTreeLib::Rectangle(xMin, yMin, xMax, yMax, 0, 0);
	}

	FLOAT_TYPE xMax;
	FLOAT_TYPE xMin;
	FLOAT_TYPE yMax;
	FLOAT_TYPE yMin;
	FLOAT_TYPE zMax;
	FLOAT_TYPE zMin;

	CSortedViewElement *m_pOriginal;
};

static int ElCompare(const void *a, const void *b)
{
	FLOAT_TYPE d1 = reinterpret_cast<const CSortedViewElement *>(a)->zMin;
	FLOAT_TYPE d2 = reinterpret_cast<const CSortedViewElement *>(b)->zMin;
	FLOAT_TYPE	d = d1 - d2;
	if(d < 0)
		return -1;
	if(fabs(d) < Eps1)
		return 0;
	return 1;
}

static int ElCompareProj(const void *a, const void *b)
{
	FLOAT_TYPE d1 = reinterpret_cast<const CSortedViewElement *>(a)->zMax;
	FLOAT_TYPE d2 = reinterpret_cast<const CSortedViewElement *>(b)->zMax;
	FLOAT_TYPE	d = d2 - d1;
	if(d < 0)
		return -1;
	if(fabs(d) < Eps1)
		return 0;
	return 1;
}



static bool IsDisjoint(FLOAT_TYPE p1Min, FLOAT_TYPE p1Max, FLOAT_TYPE p2Min, FLOAT_TYPE p2Max)
{
	return p2Max <p1Min || p2Min>p1Max;
}

void CGLDraw::ProjectVertex(SViewVertex &pt, SViewVertex &v) const
{
	GLint viewport[4];
	GLdouble modelview[16];
	GLdouble projection[16];

	glGetDoublev( GL_MODELVIEW_MATRIX, modelview );
	glGetDoublev( GL_PROJECTION_MATRIX, projection );
	glGetIntegerv( GL_VIEWPORT, viewport );

	GLdouble x,y,z;
	gluProject(v.x, v.y, v.z, modelview, projection, viewport, &x, &y, &z);
	pt.x = FLOAT_TYPE(x/1000); pt.y=FLOAT_TYPE(y/1000); pt.z = FLOAT_TYPE(-z);
	m_pViewPos->Rot->Rotate(v.x, v.y, v.z);
	pt.z = v.z;
}

inline bool ElLessZMin(CSortedViewElement el1, CSortedViewElement el2)
{
	return el1.zMin < el2.zMin;
}

inline bool ElLessXMax(CSortedViewElement el1, CSortedViewElement el2)
{
	return el1.xMax < el2.xMax;
}

typedef std::vector<CSortedViewElement>::iterator ItS;
typedef std::vector<CSortedViewElement> VecS;

void CGLDraw::EraseElement(CSortedViewElement& El) const
{
	if (!m_pTree)
		return;
	
	m_pTree->Delete(El.GetRect(), &El);
}

void CGLDraw::InsertElement(CSortedViewElement* pEl) const
{
	pEl->FragmentFlag = true;
	if (!m_pTree)
		return;
	m_pTree->Add(pEl->GetRect(), pEl);
}


void CGLDraw::SwapElements(CSortedViewElement &P, CSortedViewElement &Q) const
{
	//m_pTree->Delete(P.GetRect(), &P);
	//m_pTree->Delete(Q.GetRect(), &Q);
	//EraseElement(P);
	//EraseElement(Q);
	CSortedViewElement ElTmp = Q;
	ElTmp.FragmentFlag = false;
	Q = P;
	P = ElTmp;
	//m_pTree->Add(P.GetRect(), &P);
	//m_pTree->Add(Q.GetRect(), &Q);
	m_pTree->Swap(&P, &Q);
}

bool CGLDraw::OrderIsRight(CSortedViewElement& P, CSortedViewElement& Q, const CViewVertexArray & Vertexs, const CViewVertexArray & ProjectedVertexs, CVectorType ptEye, bool bPersp)
{
	return  Q.NumVertexs() == 2 && P.NumVertexs() == 2 ||
		IsDisjoint(P.xMin, P.xMax, Q.xMin, Q.xMax) ||
		IsDisjoint(P.yMin, P.yMax, Q.yMin, Q.yMax) ||
		P.IsOnOppositeSideOf(Q, Vertexs, ptEye, bPersp) ||
		Q.IsOnSameSideOf(P, Vertexs, ptEye, bPersp) ||
		!P.ProjectedFacesAreOwerlapped(Q, ProjectedVertexs);
}

bool CGLDraw::SortElementsOnce(CViewVertexArray & Vertexs, CViewVertexArray & ProjectedVertexs, std::vector<CSortedViewElement> & vecSorted)
{
	CVectorType ptEye(m_pViewPos->Xorg,m_pViewPos->Yorg,m_pViewPos->Zorg);
	m_pViewPos->Rot->Rotate(ptEye.v[0], ptEye.v[1], ptEye.v[2]);
	bool bPersp = m_pViewPos->bPerspective; 
	std::vector<CSortedViewElement> vecSwapped;
	std::vector<CSortedViewElement> vecSwappedPrev;
	std::vector<CSortedViewElement> vecSwappedPrev1;
	int nSwapCount = 0;
	bool bElementsWereReordered = false;

	for (size_t k=0; k< vecSorted.size() && vecSorted.size()!=0;)
	{
		
		bool bCheckNextElement = true;
		CSortedViewElement &P = vecSorted[k];
		if (P.NumVertexs()==2)
		{
			k++;
			continue;
		}
		std::list<CSortedViewElement*> list = m_pTree->Intersects(P.GetRect());

		for (auto it = list.begin(); it != list.end() && bCheckNextElement; ++it)
		{
			CSortedViewElement &Q = **it;
			int dist = &Q -&P;
			if (dist<=0)
				continue;

			if (OrderIsRight(P, Q, Vertexs, ProjectedVertexs, ptEye, bPersp))
				continue;
			// FragmentFlag == false  === Element was swapped at least once
			if ((P.FragmentFlag || Q.FragmentFlag)&&(Q.IsOnOppositeSideOf(P,Vertexs, ptEye, bPersp)
				|| P.IsOnSameSideOf(Q,Vertexs, ptEye, bPersp)))
			{
				vecSwapped.push_back(Q);
				vecSwapped.push_back(P);
				SwapElements(P, Q);

				bCheckNextElement = false;
				break;
			}
			// Both elements were reordered earlier
			if (!P.FragmentFlag && !Q.FragmentFlag)
			{
				//DebugBreak();
				P.FragmentFlag = true;
				Q.FragmentFlag = true;

				// Try to break P by any of elements swapped (reordered) earlier
				for (size_t i=0; i<vecSwapped.size(); i++)
					if (P.BreakByPlaneOf(vecSwapped[i], *this, Vertexs, ProjectedVertexs, vecSorted, k))
					{
						bCheckNextElement = false;
						break;
					}
				//if (P.BreakByPlaneOf(Q, *this, Vertexs, ProjectedVertexs, vecSorted, k))
				//	bCheckNextElement = false;
				if (bCheckNextElement && vecSwapped.size() == vecSwappedPrev.size())
				{
					for (size_t i=0; i<vecSwapped.size(); i++)
						if (
							memcmp(&vecSwapped[i],&vecSwappedPrev[i],sizeof(CSortedViewElement))!=0 &&
							i<vecSwappedPrev1.size() &&
							memcmp(&vecSwapped[i],&vecSwappedPrev1[i],sizeof(CSortedViewElement))!=0
						)
						{
							bCheckNextElement = false;
							break;
						}
				}
				else
					bCheckNextElement = false;
				if (!bCheckNextElement && nSwapCount++ >10)
					bCheckNextElement = true;
				//bCheckNextElement = false;
				vecSwappedPrev1 = vecSwappedPrev;
				vecSwappedPrev = vecSwapped;
				vecSwapped.clear();
			}
			else if (P.BreakByPlaneOf(Q, *this, Vertexs, ProjectedVertexs, vecSorted, k))
				bCheckNextElement = false;
			break;
		}
		if (bCheckNextElement)
		{
			nSwapCount = 0;
			k++;
		}
		else
		{
			bElementsWereReordered = true;
		}
#if 0 //def DEBUG
		VecS vecSortByX1 = vecSorted;
		for (UINT i=0; i<vecSorted.size(); i++)
			vecSortByX1[i].m_pOriginal = &vecSorted[i];
		std::sort(vecSortByX1.begin(), vecSortByX1.end(), ElLessXMax);
		for (UINT i=0; i<vecSortByX1.size(); i++)
		{
			bool bCmp = false;
			CSortedViewElement el(vecSortByX1[i]);
			el.xMax = vecSortByX[i].xMax;
			for(auto it = std::lower_bound(vecSortByX1.begin(), vecSortByX1.end(), el, ElLessXMax); it!=vecSortByX1.end() && it->xMax  == el.xMax; it++)
				if (memcmp(&(*it),&vecSortByX[i],sizeof(CSortedViewElement))==0)
					bCmp = true;

			if (!bCmp)
				DebugBreak();
		}
#endif
	}
	return bElementsWereReordered;
}

void CGLDraw::SortElements(CViewElement * &Elements, int &NumElements)
{
	CViewVertexArray Vertexs(m_pGeometry->VertexArray);

	GLint viewport[4];
	GLdouble modelview[16];
	GLdouble projection[16];

	glGetDoublev( GL_MODELVIEW_MATRIX, modelview );
	glGetDoublev( GL_PROJECTION_MATRIX, projection );
	glGetIntegerv( GL_VIEWPORT, viewport );

	SViewVertex *vptr;
	CViewVertexArray ProjectedVertexs;
	ProjectedVertexs.resize(Vertexs.size());
	vptr = Vertexs.GetVector();
	for(UINT i = 0; i<Vertexs.size(); i++,vptr++)
	{
		GLdouble x,y,z;
		gluProject(vptr->x, vptr->y, vptr->z, modelview, projection, viewport, &x, &y, &z);
		SViewVertex &pt = ProjectedVertexs[i];
		pt.x = FLOAT_TYPE(x/1000); pt.y=FLOAT_TYPE(y/1000); pt.z = FLOAT_TYPE(-z);
		m_pViewPos->Rot->Rotate(vptr->x, vptr->y, vptr->z);
		pt.z = vptr->z;
	}


	std::vector<CSortedViewElement> vecSorted;
	vecSorted.reserve(NumElements*4);

	int k = 0;

	for(UINT i = 0; i < static_cast<UINT>(NumElements); i++)
	{
		CSortedViewElement	El(m_pGeometry->ElementArray[i]);
		if(!El.FragmentFlag || !El.DrawFlag /*|| El.IsContour()*/)
			continue;
		El.OrgNorm = El.Norm;
		FLOAT_TYPE *pNorm = El.Norm.GetVector();
		m_pViewPos->Rot->Rotate(pNorm[0], pNorm[1], pNorm[2]);
		El.SetExtents(ProjectedVertexs);
		vecSorted.push_back(El);
		vecSorted[vecSorted.size() - 1].m_pOriginal = &vecSorted[vecSorted.size() - 1];
		k++;
	}

	NumElements = k;
	//if (vecSorted.size()>0)
	//	qsort(&vecSorted[0], NumElements, sizeof(CSortedViewElement), ElCompare);
	std::sort(vecSorted.begin(), vecSorted.end(), ElLessZMin);

	RTreeLib::RTree<CSortedViewElement*> tree;
	m_pTree = &tree;
	for (size_t i=0; i<vecSorted.size(); i++)
	{
		CSortedViewElement& El = vecSorted[i];
		tree.Add(El.GetRect(), &vecSorted[i]);
	}
#ifdef NEW_DEPTH_SORT
	SortElementsOnce(Vertexs, ProjectedVertexs, vecSorted);
#endif
	m_pTree = nullptr;
	NumElements = int(vecSorted.size());
	Elements = new CViewElement[NumElements];
	for (size_t i=0;i< vecSorted.size();i++)
	{
		Elements[i] = CViewElement(vecSorted[i]);
		Elements[i].Norm = Elements[i].OrgNorm;
		Elements[i].FragmentFlag = true;
	}
}

bool CGLDraw::BreakTriangle(CViewVertexArray& Vertexs, CViewVertexArray& ProjectedVertexs,
                            std::vector<CSortedViewElement>& vecSorted, int k, CSortedViewElement& Q, CSortedViewElement& P) const
{
	// Split P by plane of Q
	// Mark and insert pieces of P
	for (int i=0; i<P.NumVertexs()-1; i++)
	{
		 SViewVertex &p0 = Vertexs[P.Points[i]];
		 SViewVertex &p1 = Vertexs[P.Points[(i+1)%P.NumVertexs()]];
		 FLOAT_TYPE t = Q.SectByPlane(p0,p1,Vertexs);
		 if (t>Eps1 && t<1-Eps1)
		 {
			 SViewVertex &p_0 = m_pGeometry->VertexArray[P.Points[i]];
			 SViewVertex &p_1 = m_pGeometry->VertexArray[P.Points[(i+1)%P.NumVertexs()]];
			 SViewVertex pn1 = p_0;
			 pn1.x = p_0.x + t*(p_1.x-p_0.x); pn1.y = p_0.y+t*(p_1.y-p_0.y); pn1.z = p_0.z+t*(p_1.z-p_0.z);
			 for (int j=i+1; j<P.NumVertexs(); j++)
			 {
				 SViewVertex &p0_ = Vertexs[P.Points[j]];
				 SViewVertex &p1_ = Vertexs[P.Points[(j+1)%P.NumVertexs()]];
				 FLOAT_TYPE t1 = Q.SectByPlane(p0_,p1_,Vertexs);
				 if (t1>Eps1 && t1<1-Eps1)
				 {
					 SViewVertex &p_0_ = m_pGeometry->VertexArray[P.Points[j]];
					 SViewVertex &p_1_ = m_pGeometry->VertexArray[P.Points[(j+1)%P.NumVertexs()]];
					 SViewVertex pn2 = m_pGeometry->VertexArray[P.Points[j]];
					 pn2.x = p_0_.x + t1*(p_1_.x-p_0_.x); pn2.y = p_0_.y+t1*(p_1_.y-p_0_.y); pn2.z = p_0_.z+t1*(p_1_.z-p_0_.z);
					 UINT nNewPoints = Vertexs.size();
					 Vertexs.push_back(pn1);
					 Vertexs.push_back(pn2);
					 m_pGeometry->VertexArray.push_back(pn1);
					 m_pGeometry->VertexArray.push_back(pn2);
					 ProjectedVertexs.push_back(pn1);
					 ProjectedVertexs.push_back(pn2);
					 ProjectVertex(ProjectedVertexs[nNewPoints], Vertexs[nNewPoints]);
					 ProjectVertex(ProjectedVertexs[nNewPoints+1], Vertexs[nNewPoints+1]);
					 CSortedViewElement elNew = P;
					 CSortedViewElement el = P;
					 if (j==i+2)
					 {
						 EraseElement(P);
						 vecSorted[k].Points[i+1]=nNewPoints;
						 vecSorted[k].Points[i+2]=nNewPoints+1;
						 vecSorted[k].SetExtents(ProjectedVertexs);
						 InsertElement( &vecSorted[k]);

						 elNew.Type = EL_QUAD;
						 elNew.Points[0] = nNewPoints;
						 elNew.Points[1] = el.Points[i+1];
						 elNew.Points[2] = el.Points[i+2];
						 elNew.Points[3] = nNewPoints+1;
						 elNew.SetExtents(ProjectedVertexs);
						 vecSorted.push_back(elNew);
						 InsertElement(&vecSorted[vecSorted.size()-1]);
						 return true;
					 } else if (j==i+1)
					 {
						 EraseElement(P);
						 vecSorted[k].Points[i]=nNewPoints;
						 vecSorted[k].Points[(i+2)%P.NumVertexs()]=nNewPoints+1;
						 vecSorted[k].SetExtents(ProjectedVertexs);
						 InsertElement(&vecSorted[k]);

						 elNew.Type = EL_QUAD;
						 elNew.Points[0] = nNewPoints;
						 elNew.Points[1] = nNewPoints+1;
						 elNew.Points[2] = el.Points[(i+2)%el.NumVertexs()];
						 elNew.Points[3] = el.Points[i];
						 elNew.SetExtents(ProjectedVertexs);
						 vecSorted.push_back(elNew);
						 InsertElement(&vecSorted[vecSorted.size()-1]);
						 return true;
					 }
				 }
			 }
		 }
	}
	return false;
}

bool CGLDraw::BreakQuad(CViewVertexArray &Vertexs, CViewVertexArray &ProjectedVertexs,
		std::vector<CSortedViewElement>& vecSorted, int k, CSortedViewElement &Q, 
		CSortedViewElement &P) const
{
	// Split P by plane of Q
	// Mark and insert pieces of P
	for (int i=0; i<P.NumVertexs()-1; i++)
     {
         SViewVertex &p0 = Vertexs[P.Points[i]];
         SViewVertex &p1 = Vertexs[P.Points[(i+1)%P.NumVertexs()]];
         FLOAT_TYPE t = Q.SectByPlane(p0,p1,Vertexs);
         if (t>Eps1 && t<1-Eps1)
         {
             SViewVertex &p_0 = m_pGeometry->VertexArray[P.Points[i]];
             SViewVertex &p_1 = m_pGeometry->VertexArray[P.Points[(i+1)%P.NumVertexs()]];
             SViewVertex pn1 = p_0;
             pn1.x = p_0.x + t*(p_1.x-p_0.x); pn1.y = p_0.y+t*(p_1.y-p_0.y); pn1.z = p_0.z+t*(p_1.z-p_0.z);
             for (int j=i+1; j<P.NumVertexs(); j++)
             {
                 SViewVertex &p0_ = Vertexs[P.Points[j]];
                 SViewVertex &p1_ = Vertexs[P.Points[(j+1)%P.NumVertexs()]];
                 FLOAT_TYPE t1 = Q.SectByPlane(p0_,p1_,Vertexs);
                 if (t1>Eps1 && t1<1-Eps1)
                 {
                     SViewVertex &p_0_ = m_pGeometry->VertexArray[P.Points[j]];
                     SViewVertex &p_1_ = m_pGeometry->VertexArray[P.Points[(j+1)%P.NumVertexs()]];
                     SViewVertex pn2 = m_pGeometry->VertexArray[P.Points[j]];
                     pn2.x = p_0_.x + t1*(p_1_.x-p_0_.x); pn2.y = p_0_.y+t1*(p_1_.y-p_0_.y); pn2.z = p_0_.z+t1*(p_1_.z-p_0_.z);
                     UINT nNewPoints = Vertexs.size();
                     Vertexs.push_back(pn1);
                     Vertexs.push_back(pn2);
                     m_pGeometry->VertexArray.push_back(pn1);
                     m_pGeometry->VertexArray.push_back(pn2);
                     ProjectedVertexs.push_back(pn1);
                     ProjectedVertexs.push_back(pn2);
                     ProjectVertex(ProjectedVertexs[nNewPoints], Vertexs[nNewPoints]);
                     ProjectVertex(ProjectedVertexs[nNewPoints+1], Vertexs[nNewPoints+1]);
                     CSortedViewElement elNew = P;
                     CSortedViewElement el = P;
                     if (j==i+2)
                     {

                         EraseElement(P);
                         vecSorted[k].Points[i+1]=nNewPoints;
                         vecSorted[k].Points[i+2]=nNewPoints+1;
                         vecSorted[k].SetExtents(ProjectedVertexs);
                         InsertElement(&vecSorted[k]);

                         elNew.Points[0] = nNewPoints;
                         elNew.Points[1] = el.Points[i+1];
                         elNew.Points[2] = el.Points[i+2];
                         elNew.Points[3] = nNewPoints+1;
                         elNew.SetExtents(ProjectedVertexs);
                         vecSorted.push_back(elNew);
                         InsertElement(&vecSorted[vecSorted.size()-1]);
						 return true;
                     } else if (j==i+1)
                     {
                         EraseElement(P);
                         vecSorted[k].Points[(i+1)]=nNewPoints;
                         vecSorted[k].Points[(i+2)%P.NumVertexs()]=nNewPoints+1;
                         vecSorted[k].SetExtents(ProjectedVertexs);
                         InsertElement(&vecSorted[k]);

						 elNew.Type = EL_TRIANGLE;
                         elNew.Points[0] = nNewPoints;
                         elNew.Points[1] = el.Points[i+1];
                         elNew.Points[2] = nNewPoints+1;
                         elNew.SetExtents(ProjectedVertexs);
                         vecSorted.push_back(elNew);
                         InsertElement(&vecSorted[vecSorted.size()-1]);

                         elNew.Points[0] = nNewPoints+1;
                         elNew.Points[1] = el.Points[(i+2)%el.NumVertexs()];
                         elNew.Points[2] = el.Points[(i+3)%el.NumVertexs()];
                         elNew.SetExtents(ProjectedVertexs);
                         vecSorted.push_back(elNew);
                         InsertElement(&vecSorted[vecSorted.size()-1]);
						 return true;
                     }
                     else if (j==i+3)
                     {
                         EraseElement(P);
                         vecSorted[k].Points[i]=nNewPoints;
                         vecSorted[k].Points[i+3]=nNewPoints+1;
                         vecSorted[k].SetExtents(ProjectedVertexs);
                         InsertElement(&vecSorted[k]);

                         elNew.Type = EL_TRIANGLE;
                         elNew.Points[0] = nNewPoints;
                         elNew.Points[1] = nNewPoints+1;
                         elNew.Points[2] = el.Points[i];
                         elNew.SetExtents(ProjectedVertexs);
                         vecSorted.push_back(elNew);
                         InsertElement(&vecSorted[vecSorted.size()-1]);

                         elNew.Points[0] = nNewPoints+1;
                         elNew.Points[1] = el.Points[(i+2)%el.NumVertexs()];
                         elNew.Points[2] = el.Points[(i+3)%el.NumVertexs()];
                         elNew.SetExtents(ProjectedVertexs);
                         vecSorted.push_back(elNew);
                         InsertElement(&vecSorted[vecSorted.size()-1]);
						 return true;
                     }
                 }
             }
         }
     }
	 return false;
}

// Отрисовка узлов
void CGLDraw::DrawNodes(bool bBounds)
{
	CViewVertexArray &Vertexs = m_pGeometry->VertexArray;
	glPointSize(GLfloat(m_pOptions->NodeSize));
	SetGlColor(m_pOptions->NodeColor);
	glBegin(GL_POINTS);
	for(UINT i = 0; i < m_pGeometry->NumRealVertexs; i++)
	{
		SViewVertex p = Vertexs[i];
		if(!p.FragmentFlag || (p.Flag & VF_DELETED))
			continue;

		if(!bBounds || (p.Flag & 63) == 0)
			_glVertex3(p.x, p.y, p.z);
	}	// for
	glEnd();
}

void CGLDraw::SetSmoothing(void) const
{
	if(m_pOptions->bLineSmooth)
	{
		glEnable(GL_BLEND);
		glEnable(GL_LINE_SMOOTH);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	}
	else
	{
		glDisable(GL_BLEND);
		glDisable(GL_LINE_SMOOTH);
	}
}

// Скорректировать направление нормали, чтобы смотрела всегда на нас
inline void CGLDraw::CorrectNormal(CVectorType &rNorm, SViewVertex *p) const
{
	if(m_pViewPos->bPerspective)
	{
		CVectorType V
					(
						m_pViewPos->Xorg - p[0].x,
						m_pViewPos->Yorg - p[0].y,
						m_pViewPos->Zorg - p[0].z
					);
		if(V.DotProduct(rNorm) < 0)
			rNorm.Invert();
	}
	else
	{
		// Инвертируем нормали, смотрящие от нас
		CVectorType ViewNormVec(rNorm);
		FLOAT_TYPE	*ViewNorm = ViewNormVec.GetVector();
		m_pViewPos->Rot->Rotate(ViewNorm[0], ViewNorm[1], ViewNorm[2]);
		if(ViewNorm[2] < 0)
			rNorm.Invert();
	}
}

// Отрисовка линий через GL_LINE_STRIP
// Скорректировать направление нормали, чтобы смотрела всегда на нас
//#define SORT_FURTHEST
void CGLDraw::DrawLineStrips(void) const
{
#ifdef COLOR_STRIPS

	unsigned	c = 0;//clBlack;
#endif
	glDisable(GL_LIGHTING);

	SLineStripRec	*Strip = m_pGeometry->GetNodeCashe()->Strips(0);
	if (Strip== nullptr /*&& m_pGeometry->LineStrips.size()==0*/)
		return;
	while(Strip->Vertex != -1)
	{
#if 1
		glBegin(GL_LINE_STRIP);
#ifdef COLOR_STRIPS
		SetGlColor(c);
		c = (c * 123 + 76587) & 0xffffff;
#endif
		for(; Strip->Vertex != -1; Strip++)
			SetVertex(m_pGeometry->VertexArray.GetVector(), Strip->Vertex);
		glEnd();
#else
		int oldVertex = Strip->Vertex;
		Strip++;
		glBegin(GL_LINES);
#ifdef COLOR_STRIPS
		SetGlColor(c);
		c = (c * 123 + 76587) & 0xffffff;
#endif
		for(; Strip->Vertex != -1; Strip++)
		{
			SetVertex(m_pGeometry->VertexArray->Vertexs, oldVertex);
			SetVertex(m_pGeometry->VertexArray->Vertexs, Strip->Vertex);
			oldVertex = Strip->Vertex;
		}

		glEnd();
#endif
		Strip++;
	}
}

inline void CGLDraw::DrawLines(const CViewElement & El, const SViewVertex * p) const
{
#ifdef NO_DRAW
	return;
#endif
	NODE_NUM_TYPE	NumPoints = El.NumVertexs();
	glBegin(GL_LINES);

	NODE_NUM_TYPE	pn1 = El.Points[0];
	for(int i = 0; i < NumPoints; i++)
	{
		int				j = (i + 1) % NumPoints;
		NODE_NUM_TYPE	pn2 = El.Points[j];
		if(!m_pGeometry->GetNodeCashe()->WasDrawed(pn1, pn2))
		{
			_glVertex3(p[i].x, p[i].y, p[i].z);
			_glVertex3(p[j].x, p[j].y, p[j].z);
		}

		pn1 = pn2;
	}

	glEnd();
}

/*
S3dPoint CGLDraw::GetFontExtents(LPCTSTR pszText)
{
	S3dPoint pt(0,0,0);
	for (unsigned int loop=0;loop<(strlen(pszText));loop++)
	{
		unsigned char index = pszText[loop];
		pt.x+=m_pRenderer->m_gmf[index].gmfCellIncX*m_FontSize;
		pt.y = max(pt.y,m_pRenderer->m_gmf[index].gmfBlackBoxY*m_FontSize);
	}
	return pt;
}
*/

//DEL double CGLDraw::GetLineRatioWzWx(const S3dPoint &p1, const S3dPoint &p2, double MVM[], double PJM[], int VP[])
//DEL {
//DEL 	double w1x,w1y,w1z;
//DEL 	double w2x,w2y,w2z;
//DEL 	gluProject(p1.x, p1.y, p1.z, MVM, PJM, VP, &w1x, &w1y, &w1z);
//DEL 	gluProject(p2.x, p2.y, p2.z, MVM, PJM, VP, &w2x, &w2y, &w2z);
//DEL 	if (fabs(w1x-w2x) < 1e-5)
//DEL 		return 0;
//DEL 	return (w1z-w2z)/((w1x-w2x));
//DEL }


class CGlDrawGeomHelper
{
	struct CLineShift
	{
		double d1;
		double d2;
	};
public:
	CGlDrawGeomHelper(const CViewGeometry* pGeom) : m_pGeometry(pGeom) {};
	double GetShift(const SViewFactorVertex &p, const CViewElement &el,const  CRect &rct, double MVM[], double PJM[], int VP[]) const
	{
		C3DVector<double> wp;
		gluProject(p.x, p.y, p.z, MVM, PJM, VP, wp.v, wp.v+1, wp.v+2);

		C3DVector<double> X(rct.left, rct.top, wp.v[2]);
		C3DVector<double> Y(rct.left, rct.bottom, wp.v[2]);

		signed char  p1i=-1, p2i=-1;
		if (el.NumVertexs()>2)
		{
			for (signed char j=0;j<el.NumVertexs(); j++)
			{
				if (j==p.nVertexIndex || j==p1i || j==p2i)
					continue;
				if (p1i==-1)
					p1i = j;
				else if (p2i==-1)
				{
					p2i = j;
					break;
				}

			}
			const S3dPoint &p1 = m_pGeometry->VertexArray[el.Points[p1i]];
			const S3dPoint &p2 = m_pGeometry->VertexArray[el.Points[p2i]];

			C3DVector<double> wp1,wp2;
			gluProject(p1.x, p1.y, p1.z, MVM, PJM, VP, wp1.v, wp1.v+1, wp1.v+2);
			gluProject(p2.x, p2.y, p2.z, MVM, PJM, VP, wp2.v, wp2.v+1, wp2.v+2);

			C3DVector<double> L = wp1-wp, M = wp2-wp;
			//N = (wp1 - wp)x(wp2 - wp)
			//N = N / | N |  - нормаль к плоскости  // в принципе это можно и не делать
			C3DVector<double> N; N.SetCrossProduct(L, M);

			C3DVector<double> V = wp - X;
			// расстояние до плоскости по нормали
			double d = N.DotProduct(V);  
			C3DVector<double> W = Y - X;
			// приближение к плоскости по нормали при прохождении отрезка
			double e = N.DotProduct(W); 

			//C3DVector<double> P12;
			if( fabs(e)>1e-15)
			{
			  //P12 = X + W * (d/e);          // одна точка
			  double D = N.DotProduct(wp);
			  double D1 = -(N.DotProduct(C3DVector<double>(X.v[0],X.v[1],0))-D)/N.v[2]-wp.v[2];
			  //if (D1<0) D1 = 0;
			  double D2 = -(N.DotProduct(C3DVector<double>(Y.v[0],Y.v[1],0))-D)/N.v[2]-wp.v[2];
			  //if (D2<0) D2 = 0;
			  return -max (fabs(D1),fabs(D2));
			}
			else if( fabs(d)<1e-5)
			{
			  return -0.0001;//O =X + W * (anything)     // прямая принадлежит плоскости
			}
			//else
			  
			  //O = empty;                // прямая параллельна плоскости


		}
		return 0;
	}
protected:
	const CViewGeometry* m_pGeometry;
};


void CGLDraw::DrawFactorValues(const CViewFactorArray &rFactors, bool bUpFactors)
{
	double		MVM[16];
	double		PJM[16];
	int			VP[4];
	SetGlColor(clBlack);
	glEnable(GL_POLYGON_OFFSET_FILL);
	glGetDoublev(GL_MODELVIEW_MATRIX, MVM);
	glGetDoublev(GL_PROJECTION_MATRIX, PJM);
	glGetIntegerv(GL_VIEWPORT, VP);
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	glLoadIdentity();
	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
	glLoadIdentity();
	glOrtho(0.0, VP[2], 0.0, VP[3], 0, -1);	// Установка экранной СК
	glMatrixMode(GL_MODELVIEW);
	CViewElementArray &els = m_pGeometry->ElementArray;
	for(UINT i = 0; i <  rFactors.size(); i++)
	{
		SViewFactorVertex p = rFactors[i];
		if(!p.FragmentFlag || (p.Flag & VF_DELETED))
			continue;
		double wx = p.x;
		double wy = p.y;
		double wz = p.z;
		gluProject(p.x, p.y, p.z, MVM, PJM, VP, &wx, &wy, &wz);
		//CViewElement el = els[p.nElement];

		CString str= m_pGeometry->Format(p.fFactor);
	glPushMatrix();
#ifndef USE_FONT_BITMAPS
		S3dPoint sz = GetFontExtents(str);
		glTranslated(wx-sz.x/2, wy-sz.y/2,  wz);
		glScaled(m_FontSize, m_FontSize, m_FontSize);
		glPushAttrib(GL_LIST_BIT);							// Pushes The Display List Bits
		glListBase(m_pRenderer->m_fontBase);									// Sets The Base Character to 0
		glCallLists(strlen(pszName), GL_UNSIGNED_BYTE, pszName);	// Draws The Display List Text
		glPopAttrib();	// Pops The Display List Bits
#else
		//glTranslated(wx, wy,  wz);
		TEXTMETRIC tm;
		CSize sz = m_pRenderer->GetFontExtent(SVF_VALUES, str, &tm);


		CRect rect(int(wx)-sz.cx, int(wy), int(wx), int(wy+sz.cy+tm.tmDescent));
		
		CGlDrawGeomHelper drHelper(m_pGeometry);
		if (p.nElement!=-1)
			wz += drHelper.GetShift(p, els[p.nElement], rect, MVM, PJM, VP);
		if (wz<0)
			wz = 0;
		glRasterPos3d(0, 0, wz);
		//glTranslated(wx - sz.cx/2, wy + tm.tmDescent -sz.cy/2, 0);
		if (p.nElement == -1 ||  p.nVertexIndex<els[p.nElement].NumVertexs())
			glBitmap(0, 0, 0, 0, GLfloat(wx - sz.cx), GLfloat(wy + tm.tmDescent/* -sz.cy/2*/), nullptr);
		else
		{
			if (bUpFactors)
				wy+=m_pOptions->NodeSize+sz.cy/2+1;
			glBitmap(0, 0, 0, 0, GLfloat(wx - sz.cx/2), GLfloat(wy + tm.tmDescent - sz.cy/2), nullptr);
		}
		DrawTextList(SVF_VALUES, str);
#endif
	glPopMatrix();

	}	// for
	glMatrixMode(GL_PROJECTION);
	glPopMatrix();
	glMatrixMode(GL_MODELVIEW);
	glPopMatrix();

}

void CGLDraw::DrawEggs(const CViewFactorArray &rFactors)
{
	glEnable(GL_POINT_SMOOTH);
	glEnable(GL_BLEND);
	glDisable(GL_LIGHTING);
	const CViewFactorArray &Vertexs = rFactors;//m_pGeometry->VertexArray;
	glPointSize(GLfloat(m_pOptions->NodeSize)*2);
	SetGlColor(m_pOptions->NodeColor);
	glBegin(GL_POINTS);
	for(UINT i = 0; i < Vertexs.size()/*m_pGeometry->NumRealVertexs*/; i++)
	{
		SViewFactorVertex p = Vertexs[i];
		if(!p.FragmentFlag || (p.Flag & VF_DELETED))
			continue;
		SetGlColor(p.clr);

		//if(/*!m_pDrawOptions->bBounds ||*/ (p.Flag & 63) == 0)
			_glVertex3(p.x, p.y, p.z);
	}	// for
	glEnd();
	glDisable(GL_POINT_SMOOTH);
	glDisable(GL_BLEND);

}

