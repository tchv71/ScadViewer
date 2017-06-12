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
#include <gl\GL.h>// Added by ClassView
#include "../RTree/RTree.h"

const Graphics::TColor WIREFRAME_COLOR = clSilver;
const Graphics::TColor BOUNDS_FRAME_COLOR = clDkGray;

class CGLRenderer;
class CSortedViewElement;

#define USE_FONT_BITMAPS

class CGLDraw
{
	friend class CSortedViewElement;
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
	m_pRenderer(pRenderer), m_pTree(nullptr), m_crCurColor(0), BAR_STAGE(0), BORDER_STAGE(0), FILL_STAGE(0)
	//m_FontSize(FontSize)
	{
	};

	virtual ~CGLDraw(void)
	{
	};

	bool PreDrawStage(EDrawMode Mode, S3dPoint Z_Shift, bool bSmoothTransp, int nCurrentStage);
	void DrawBar(const CViewElement & El, const SViewVertex* Vertexs, S3dPoint Z_Shift);
	void DrawPlate(CViewElement & El, const SViewVertex* Vertexs, EDrawMode Mode, bool bSmoothTransp, int nCurrentStage);
	virtual void	Draw(void);
	static void CorrectNormal(CVectorType &rNorm, const SViewVertex * p, const SPerspectiveView* m_pViewPos);
protected:
	void UpdateMaxAxesetSize(const TAxeSet &axeSet, int& size) const;
	CViewGeometry	*m_pGeometry;
	const SPerspectiveView		*m_pViewPos;
	const SViewOptions	*m_pOptions;
	const CDrawOptions	*m_pDrawOptions;
	IFemRenderer *m_pRenderer;
	RTreeLib::RTree<CSortedViewElement*>* m_pTree;
	//int m_FontSize;
private:
	//S3dPoint GetFontExtents(LPCTSTR pszText);
	bool			BreakTriangle(CViewVertexArray &Vertexs, CViewVertexArray &ProjectedVertexs,
	    			              std::vector <CSortedViewElement> &vecSorted, size_t k, CSortedViewElement &ElTest,
	    			              CSortedViewElement & ElCurr) const;

	bool			BreakQuad(CViewVertexArray &Vertexs, CViewVertexArray &ProjectedVertexs,
	    			          std::vector<CSortedViewElement>& vecSorted, size_t k, CSortedViewElement &ElTest,
	    			          CSortedViewElement & ElCurr) const;
	void DrawAxeMarks(const S3dPoint &p1, const S3dPoint &p2, double len, double rad,  LPCTSTR pszName, double MVM[], double PJM[], int VP[]);
	void DrawAxeMark(double wx, double wy, double wz, double nx, double ny, double MarkLen, double radius, LPCTSTR pszrName);
	void DrawAxeZMark(const S3dPoint &p, LPCTSTR pszName, double MVM[], double PJM[], int VP[]);
	void DrawNodes(bool bBounds);
	void DrawBounds(void);
	void DrawAxes(void);
	void ProjectVertex(SViewVertex &pt, SViewVertex &v) const;
	void EraseElement(CSortedViewElement& El) const;
	void InsertElement(CSortedViewElement* pEl) const;
	void SwapElements(CSortedViewElement& P, CSortedViewElement& Q) const;
	static bool OrderIsRight(CSortedViewElement& P, CSortedViewElement& Q, const CViewVertexArray & Vertexs, const CViewVertexArray & ProjectedVertexs, CVectorType ptEye, bool bPersp);
	bool SortElementsOnce(CViewVertexArray & Vertexs, CViewVertexArray & ProjectedVertexs, std::vector<CSortedViewElement> & vecSorted);
	void SortElements(CViewElementArray *& Elements, size_t& NumElements);


	void SetSmoothing(void) const;
	void DrawLineStrips(void) const;
	void DrawLines(const CViewElement & El, const SViewVertex * p) const;
	inline	void			SetGlColor(TColor c);
	void			SetGlColorAlpha(TColor c);
	static inline void			DrawPolygon(const SViewVertex * p, NODE_NUM_TYPE NumPoints);
	static void			SetVertex(SViewVertex* Vertexs, NODE_NUM_TYPE n);
	static __inline void			glVertex3fs(S3dPoint &p, S3dPoint &s)
	{
		p.x -= s.x;
		p.y -= s.y;
		p.z -= s.z;
		_glVertex3(p.x, p.y, p.z);
	}
	void			DrawTextList(int nFontNo, LPCTSTR pszName) const;
	TColor			m_crCurColor;
	// Определение порядка отрисовки
	int BAR_STAGE;		// отрисовка стержней
	int BORDER_STAGE;	// отрисовка границ элементов
	int FILL_STAGE;		
};
#endif

