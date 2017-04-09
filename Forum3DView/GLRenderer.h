// GLRenderer.h: interface for the CGLRenderer class.
//
// Copyright (C) 1998,1999,2000,2003,2004,2005,2006  Dmitry Tcvetkov aka TCHV
//
// All Rights Reserved
//
// Disclaimer : this text is under authority of goverment laws, US and Russian Federation
// Unauthorizing compilation, modification and re-engineering is strictly prohibited
//////////////////////////////////////////////////////////////////////
#if !defined(AFX_GLRENDERER_H__C29F2A7B_8CBD_4EAD_B373_AD7756A84629__INCLUDED_)
#define AFX_GLRENDERER_H__C29F2A7B_8CBD_4EAD_B373_AD7756A84629__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "Renderer.h"

class CGLRenderer : public IFemRenderer
{
public:
	CGLRenderer(SPerspectiveView &rViewPos);
	virtual~CGLRenderer(void);
public:
	void ReleaseAllFonts();
	void BuildAllFonts(const SLogFont arrLogFonts[], float fScale = 1.0f);
	CSize GetFontExtent(ESvFont fontNo, LPCTSTR  pszText, TEXTMETRIC* ptm) override;
	bool Select(CViewGeometry *pGeometry, CPoint pt, FLOAT_TYPE fDepth) const;
	static CString GetRenderString();
	// IFemRenderer support
	HRESULT	BindWindow(HWND hBindWnd, bool bSoftOGL, const SLogFont  arrLogFonts[]) override;
	HRESULT	ReleaseWindow(void) override;
	HRESULT Render(CViewGeometry *pGeometry, const SViewOptions * pViewOptions, const CDrawOptions * pDrawOptions) override;
	void	SetViewportSize(int x, int y)
	{
		//		szOld.cx = GLWidth;
		//		szOld.cy = GLHeight;
		GLWidth = x;
		GLHeight = y;
	};
	void	SwapBuffers(void) const;
	void BuildFont(ESvFont fontNo, const LOGFONT *pLogFont);
	void BuildVBOs();
	void DeleteVBOs();
	bool IsExtensionSupported(char* szTargetExtension);
	bool IsVBOSupported() { return m_bVBOSupported; }
protected:
	void	DrawCoordSys(void) const;
	int		GLWidth;
	int		GLHeight;

	// Vertex buffer variables
	// ARB_vertex_buffer_object supported?
	bool    m_bVBOSupported;
public:
	// Vertex Buffer Object Names
	unsigned int	m_nVBOVertices;								// Vertex VBO Name
	unsigned int	m_nVBOColors;								// Color VBO Name
	unsigned int	m_nVBONormals;								// Normal VBO Name
	// Element VBOs
	unsigned int	m_nVBOTriangles;							// Triangles VBO Name
	unsigned int	m_nVBOQuads;								// Quads   VBO Name

protected:
	void	SetGLView(const SPerspectiveView &crViewPos) const;
	void	SetGLProjection
	(
		const S3DBox	&rViewBox,
		FLOAT_TYPE			Depth,
		CPoint*			pptSelect = nullptr
	) const;
	static void	SetGLLighting(bool bPerspective);
	static void	CreateRGBPalette(HDC hDC, PIXELFORMATDESCRIPTOR &pfd);
	static int		ChoosePixelFormatEx
	(
		HDC hdc,
		int *pnColorBits,
		int *pnDepthBits,
		int *pnWantDoubleBuffer,
		int *pnWantAcceleration
	);
	bool	bSetupPixelFormat(DWORD dwFlags, bool Soft);
	static bool	SetDCPixelFormat(HDC hDC, DWORD dwFlags);

	void			DrawAxe(char Name) const;

	HWND	m_hWnd;

	const SPerspectiveView &m_ViewPos;

	HFONT	m_fonts[SVF_SIZE];										// Windows Font ID
	SLogFont m_arrLogFonts[SVF_SIZE];
	// Printing
	HDC			m_hDC;
	HGLRC		m_hRC;

protected:
	void ReleaseFont(ESvFont fontNo);
};
#endif // !defined(AFX_GLRENDERER_H__C29F2A7B_8CBD_4EAD_B373_AD7756A84629__INCLUDED_)
