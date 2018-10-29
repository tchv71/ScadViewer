// Copyright (C) 1998,1999,2000,2003,2004,2005,2006  Dmitry Tcvetkov aka TCHV
//
// All Rights Reserved
//
// Disclaimer : this text is under authority of goverment laws, US and Russian Federation
// Unauthorizing compilation, modification and re-engineering is strictly prohibited
//---------------------------------------------------------------------------
#ifndef GLDrawH
#define GLDrawH
#include "DetViewOpts.h"
#include "ViewGeometry.h"
#include "ViewLib.h"
#include "Renderer.h"
#include "model.h"
#include <gl/GL.h>

const Graphics::TColor WIREFRAME_COLOR = clSilver;
const Graphics::TColor BOUNDS_FRAME_COLOR = clDkGray;

class CGLRenderer;
class CSortedViewElement;

#define USE_FONT_BITMAPS

class CGLDraw
{
	//friend class CSortedViewElement;
	typedef size_t ElementType;
public:
	void DrawEggs(const CViewFactorArray &rFactors);
	void DrawFactorValues(const CViewFactorArray &rFactors, bool bUpFactors = false);
	CGLDraw
	(
		CViewGeometry	*Geometry,
		const SPerspectiveView		*ViewPos,
		const SViewOptions	*Options,
		const CDrawOptions	*DrawOptions,
		IFemRenderer *pRenderer
		//int FontSize
	) :
		m_pGeometry(Geometry),
		m_pViewPos(ViewPos),
		m_pOptions(Options),
		m_pDrawOptions(DrawOptions),
		m_pRenderer(pRenderer), m_crCurColor(0), m_iCurAlpha(128), BAR_STAGE(0), BORDER_STAGE(0), FILL_STAGE(0)
	//m_FontSize(FontSize)
	{
	};

	virtual ~CGLDraw()
	{
	};

	bool PreDrawStage(EDrawMode Mode, S3dPoint Z_Shift, bool bSmoothTransp, int nCurrentStage);
	void DrawBar(const CViewElement& El, const SViewVertex* Vertexs, const S3dPoint& Z_Shift);
	void DrawPlate(CViewElement & El, const SViewVertex* Vertexs, EDrawMode Mode, bool bSmoothTransp, int nCurrentStage);
	virtual void	Draw();
	static void CorrectNormal(CVectorType &rNorm, const SViewVertex * p, const SPerspectiveView* m_pViewPos);
protected:
	void UpdateMaxAxesetSize(const TAxeSet &axeSet, int& size) const;
	CViewGeometry	*m_pGeometry;
	const SPerspectiveView		*m_pViewPos;
	const SViewOptions	*m_pOptions;
	const CDrawOptions	*m_pDrawOptions;
	IFemRenderer *m_pRenderer;
	//int m_FontSize;
private:
	//S3dPoint GetFontExtents(LPCTSTR pszText);
	void DrawAxeMarks(const S3dPoint &p1, const S3dPoint &p2, double len, double rad,  LPCTSTR pszName, double MVM[], double PJM[], int VP[]);
	void DrawAxeMark(double wx, double wy, double wz, double nx, double ny, double MarkLen, double radius, LPCTSTR pszName);
	void DrawAxeZMark(const S3dPoint & p1, LPCTSTR pszName, double MVM[], double PJM[], int VP[]);
	void DrawNodes(bool bBounds);
	void DrawBounds();
	void DrawAxes();
	bool SortElementsOnce(CViewVertexArray & Vertexs, CViewVertexArray & ProjectedVertexs, std::vector<CSortedViewElement> & vecSorted) const;
	void SortElements(CViewElementArray *& Elements, size_t& NumElements) const;


	void SetSmoothing() const;
	void DrawLineStrips() const;
	static void DrawLines(const CViewElement & El, const SViewVertex * p);
	void SetGlColor(TColor c)
	{
		if (c == m_crCurColor)
			return;
		m_crCurColor = c;
		glColor3ub(GetRValue(c), GetGValue(c), GetBValue(c));
	}
	void SetGlColorAlpha(TColor c)
	{
		if (c == m_crCurColor)
			return;
		m_crCurColor = c;

		glColor4ub(GetRValue(c), GetGValue(c), GetBValue(c), m_iCurAlpha);
	}
	static inline void			DrawPolygon(const SViewVertex * p, NODE_NUM_TYPE NumPoints);
	static void			SetVertex(SViewVertex* Vertexs, NODE_NUM_TYPE n);
	static __inline void glVertex3fs(S3dPoint &p,const S3dPoint &s)
	{
		p.x -= s.x;
		p.y -= s.y;
		p.z -= s.z;
		_glVertex3(p.x, p.y, p.z);
	}
	void			DrawTextList(int nFontNo, LPCTSTR pszName) const;
	TColor			m_crCurColor;
	BYTE			m_iCurAlpha;

	// Определение порядка отрисовки
	int BAR_STAGE;		// отрисовка стержней
	int BORDER_STAGE;	// отрисовка границ элементов
	int FILL_STAGE;		
};
#endif

