// DibGlRenderer.cpp: implementation of the CDibGlRenderer class.
//
// Copyright (C) 1998,1999,2000,2003,2004,2005,2006  Dmitry Tcvetkov aka TCHV
//
// All Rights Reserved
//
// Disclaimer : this text is under authority of goverment laws, US and Russian Federation
// Unauthorizing compilation, modification and re-engineering is strictly prohibited
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include <gl\gl.h>
#include "DibGlRenderer.h"
#include "shlwapi.h"

#include "ViewGeometry.h"
#include "IsoViewGeometry.h"
#ifndef SCAD11
#ifdef SCAD21
#else
#include "schema.h"
#endif
#else
#include "schema.hpp"
#include "Result.hpp"
//#include "scad.h"
//#include "Grand.h"
#endif
#include "..\ogliso\OglIso.h"
#include "resource.h"
#include "3DIso.hpp"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CDibGlRenderer::CDibGlRenderer(const CViewGeometry* pGeometry, SPerspectiveView &rViewPos) :
	 CGLRenderer(m_ViewPosCopy), m_ViewPosCopy(rViewPos), m_pBitmapBits(nullptr),
	m_hDib(nullptr),
	m_pGeometry(pGeometry)
{

}

CDibGlRenderer::~CDibGlRenderer()
{

}

bool CDibGlRenderer::BindDib(HWND hWnd, CSize szDIB, int nBorder)
{
	memset(&m_bmi, 0, sizeof(BITMAPINFO));
	m_bmi.bmiHeader.biSize			= sizeof(BITMAPINFOHEADER);
	m_bmi.bmiHeader.biWidth			= szDIB.cx;
	m_bmi.bmiHeader.biHeight		= szDIB.cy;
	m_bmi.bmiHeader.biPlanes		= 1;
	m_bmi.bmiHeader.biBitCount		= 24;
	m_bmi.bmiHeader.biCompression	= BI_RGB;
	m_bmi.bmiHeader.biSizeImage		= ((((szDIB.cx * 24) + 31) & ~31) >> 3) * szDIB.cy;
	HDC	hDC = ::GetDC(hWnd);
	m_hDib = ::CreateDIBSection(hDC, &m_bmi, DIB_RGB_COLORS, &m_pBitmapBits, nullptr, DWORD(0));
	::ReleaseDC(hWnd, hDC);

	// 3. Create memory DC, and associate it with the DIB.
	m_hDC = ::CreateCompatibleDC(nullptr);
	if (!m_hDC)
	{
		DeleteObject(m_hDib);
		m_hDib = nullptr;
		return false;
	}
	SelectObject(m_hDC, m_hDib);

	// 4. Setup memory DC's pixel format.
	if (!SetDCPixelFormat(m_hDC, PFD_DRAW_TO_BITMAP | PFD_SUPPORT_OPENGL | PFD_STEREO_DONTCARE))
	{
		DeleteObject(m_hDib);
		m_hDib = nullptr;
		DeleteDC(m_hDC);
		m_hDC = nullptr;
		return false;
	}

	// 5. Create memory RC
	m_hRC = ::wglCreateContext(m_hDC);
	if (!m_hRC)

	{
		DeleteObject(m_hDib);
		m_hDib = nullptr;
		DeleteDC(m_hDC);
		m_hDC = nullptr;
		return false;
	}

	// 6. Store old DC and RC
		// 7. Make the memory RC current
	::wglMakeCurrent(m_hDC, m_hRC);
	glClearDepth(1.0);
	glEnable(GL_DEPTH_TEST);							// Enables Depth Testing
	glDepthFunc(GL_LEQUAL);								// The Type Of Depth Testing To Do
	BuildAllFonts(m_arrLogFonts);


	// 8. Set OpenGL state for memory RC. 
	// The state is the same as the screen RC's.
	//SetOpenGLState();
	int clw = szDIB.cx - nBorder, clh = szDIB.cy - nBorder;
	FLOAT_TYPE	SclX = clw / m_ViewPos.ViewSizeX, SclY = clh / m_ViewPos.ViewSizeY;
	FLOAT_TYPE	SclF = (SclX < SclY) ? SclX : SclY;
	//OldScrScale = m_ViewPos.ScrScale;
	m_ViewPosCopy.ScrScale = SclF;
	SetViewportSize(szDIB.cx, szDIB.cy);
	return true;
}

void CDibGlRenderer::ReleaseDib()
{
	ReleaseAllFonts();
	// 1. Release memory RC, and restore the old DC and RC.
	::wglMakeCurrent(nullptr, nullptr);	
	::wglDeleteContext(m_hRC);
	//m_hMemRC = m_hOldRC;
	// 4. Release memory.
	::DeleteObject(m_hDib);
	m_hDib = nullptr;
	::DeleteDC(m_hDC);	
}

void CDibGlRenderer::DrawFrame(CDC *pDC, CRect &rcDib, CString strFileName) const
{
	FLOAT_TYPE fAspX = pDC->GetDeviceCaps(LOGPIXELSX)/25.4f; //FLOAT_TYPE(m_szPage.cx)/szPageMM.cx; // pix/mm
	FLOAT_TYPE fAspY = pDC->GetDeviceCaps(LOGPIXELSY)/25.4f; //FLOAT_TYPE(m_szPage.cy)/szPageMM.cy;
	

	int nLineWidth = int(0.3f/*mm*/*fAspX+0.5); // pix
	CPen pen(PS_SOLID, nLineWidth, COLORREF(clBlack));
	CPen* pOldPen = pDC->SelectObject(&pen);
	CFont font;
	font.CreateFont(12*pDC->GetDeviceCaps(LOGPIXELSY)/72,0,0,0,FW_NORMAL,0,0,0,RUSSIAN_CHARSET,OUT_DEFAULT_PRECIS,CLIP_DEFAULT_PRECIS,DEFAULT_QUALITY,DEFAULT_PITCH,_T("Arial"));
	CFont *pOldFont = pDC->SelectObject(&font);
	DrawPageBorder(pDC, rcDib, fAspX, fAspY, m_szPage.cx, m_szPage.cy, strFileName);
	pDC->SelectObject(pOldFont);
	pDC->SelectObject(pOldPen);

}

struct SFloatRect
{
	FLOAT_TYPE	left, top, right, bottom;
};


static void ShrinkRect
(
	RECT		&r,			// Сжимаемый прямоугольник
	SFloatRect	*offset,	// Зазоры по краям, мм
	FLOAT_TYPE		fAspX,
	FLOAT_TYPE		fAspY		// Масштаб по осям X и Y
)
{
	r.top += LONG(offset->top * fAspY);
	r.right -= LONG(offset->right * fAspX);
	r.bottom -= LONG(offset->bottom * fAspY);
	r.left += LONG(offset->left * fAspX);
}

static void MovePoint(long &pos, FLOAT_TYPE fDesired/*mm*/, FLOAT_TYPE fGap/*mm*/, FLOAT_TYPE fAsp, int nDir)
{
	FLOAT_TYPE fVal = fDesired > fGap+0.5f ? fDesired - fGap : 0.5f;
	pos += int(fVal*fAsp+0.5f)*nDir;
}

int CDibGlRenderer::DrawScale
(
	CDC			*pDC,
	CRect		&r,
	FLOAT_TYPE		fAspX,
	FLOAT_TYPE		fAspY,
	int			nColumns,
	const struct DefMapInfo *DMI
) const
{
	bool bPortrait = r.Height()>r.Width();
	const int nBoxX = int(5*fAspX);
	const int nBoxY = int(3*fAspX);
	const int nGapY = nBoxY*3/2;
	const int nGapX = int(2*fAspX);
	const int nBoxesInColumn = DMI->Scale_count/nColumns;
	const CIsoViewGeometry *pGeom = static_cast<const CIsoViewGeometry*>(m_pGeometry);
	CFont font;
	font.CreateFont(8*pDC->GetDeviceCaps(LOGPIXELSY)/72,0,0,0,FW_NORMAL,0,0,0,RUSSIAN_CHARSET,OUT_DEFAULT_PRECIS,CLIP_DEFAULT_PRECIS,DEFAULT_QUALITY,DEFAULT_PITCH,_T("Arial"));
	CFont *pOldFont = pDC->SelectObject(&font);
	int nMaxWidth =0;
	for (int i=0;i<DMI->Scale_count; i++)
	{
		CString str = pGeom->Format(DMI->binter[i]);
		CSize szText = pDC-> GetTextExtent(str);
		if (szText.cx>nMaxWidth)
			nMaxWidth = szText.cx;
	}
	const int nColumnWidth = nGapX+nBoxX+nGapX+nMaxWidth+nGapX+nMaxWidth+nGapX;
	CPoint pt;
	const int nScaleHeight = (nGapY-nBoxY)+nGapY*nBoxesInColumn;
	if (bPortrait)
	{
		pt.x = r.left+(r.Width()-nColumnWidth*(nColumns+1))/2;
		pt.y = r.bottom - nScaleHeight+nGapY-nBoxY;
	}
	else
	{
		pt.x = r.right - nColumnWidth * nColumns;
		pt.y = r.top + nGapY;
	}
	for (int nIndex = 0; nIndex<DMI->Scale_count;)
	{
		CPoint ptOld = pt;
		for (int nC=0; nC<nBoxesInColumn && nIndex<DMI->Scale_count; nC++, nIndex++)
		{
			CBrush br;
			br.CreateSolidBrush(DMI->col[nIndex]);
//			CBrush *pOldBr  = pDC->SelectObject(&br);
			RECT rc;
			rc.left = pt.x + nGapX;
			rc.top = pt.y;
			rc.right = rc.left + nBoxX;
			rc.bottom = rc.top + nBoxY;
			pDC->FillRect(&rc, &br);
//			pDC->SelectObject(pOldBr);
			CString str =  pGeom->Format(DMI->binter[nIndex]);
			CSize szText = pDC-> GetTextExtent(str);
			pDC->TextOut(pt.x+nGapX+nBoxX+nGapX+nMaxWidth-szText.cx, pt.y - (nBoxY-szText.cy) / 2, str);
			str =  pGeom->Format(DMI->einter[nIndex]);
			szText = pDC-> GetTextExtent(str);
			pDC->TextOut(pt.x+nGapX+nBoxX+2*nGapX+2*nMaxWidth-szText.cx, pt.y - (nBoxY-szText.cy) / 2, str);
			pt.y += nGapY;
		}
		pt = ptOld;
		pt.x += nColumnWidth;
	}

	
	pDC->SelectObject(pOldFont);
	//pDC->SelectObject(pOldPen);
	return bPortrait ?  nScaleHeight : nColumns*nColumnWidth;
}


void CDibGlRenderer::DrawPageBorder
(
	CDC			*pDC,
	CRect		&r,
	FLOAT_TYPE		fAspX,
	FLOAT_TYPE		fAspY,
	int			W,
	int			H,
	CString		strFileName
) const
{
	SFloatRect	PortraitShrink = { 20, 5, 5, 5 },
	LandscapeShrink = { 5, 20, 5, 5 };
	SFloatRect sPrinterGaps = // mm
		{
			pDC->GetDeviceCaps(PHYSICALOFFSETX)/fAspX,
			pDC->GetDeviceCaps(PHYSICALOFFSETY)/fAspY,
			(pDC->GetDeviceCaps(PHYSICALWIDTH)- pDC->GetDeviceCaps(PHYSICALOFFSETX) -W)/fAspX,
			(pDC->GetDeviceCaps(PHYSICALHEIGHT)- pDC->GetDeviceCaps(PHYSICALOFFSETY)-H)/fAspY
		};

//	int PW = pDC->GetDeviceCaps(PHYSICALWIDTH);
//	int POX = pDC->GetDeviceCaps(PHYSICALOFFSETX);
//	int lX =pDC->GetDeviceCaps(HORZRES);
//	int szX =pDC->GetDeviceCaps(HORZSIZE);
	
	//ShrinkRect(r, (H > W) ? &PortraitShrink : &LandscapeShrink, fAspX, fAspY);
	bool bPortrait = (H > W);
	SFloatRect *pShRc = bPortrait ? &PortraitShrink : &LandscapeShrink;
	MovePoint(r.left, pShRc->left, sPrinterGaps.left, fAspX, 1);
	MovePoint(r.top, pShRc->top, sPrinterGaps.top, fAspY, 1);
	MovePoint(r.right, pShRc->right, sPrinterGaps.right, fAspX, -1);
	MovePoint(r.bottom, pShRc->bottom, sPrinterGaps.bottom, fAspY, -1);

	pDC->MoveTo(r.left, r.top); // Ограничивающий прямоугольник
	pDC->LineTo(r.right, r.top);
	pDC->LineTo(r.right, r.bottom);
	pDC->LineTo(r.left, r.bottom);
	pDC->LineTo(r.left, r.top);

	int nGap = int(2 * fAspX);
	PathCompactPath(pDC->GetSafeHdc(), strFileName.GetBuffer(MAX_PATH), r.right - r.left - 2*nGap);
	strFileName.ReleaseBuffer();
	
	CSize szText = pDC-> GetTextExtent(strFileName);

	int nFieldHeigh = szText.cy * 3 / 2;

	pDC->TextOut(r.left + nGap, r.top + szText.cy / 4, strFileName);
	r.top += nFieldHeigh;
	pDC->MoveTo(r.left, r.top);
	pDC->LineTo(r.right, r.top);
	int rRight = r.right;
	if (m_pGeometry->IsIso())
	{
		int x = r.left + 2*nGap + szText.cx;
		pDC->MoveTo(x, r.top-nFieldHeigh);
		pDC->LineTo(x, r.top);
		x+= nGap;

		const CIsoViewGeometry *pGeom = static_cast<const CIsoViewGeometry*>(m_pGeometry);
#ifdef SCAD21

		CString str;
		if (pGeom->m_Params.nTypeData == Iso_Disp)
			switch (pGeom->m_Params.nTypeFactor)
			{
			case 0:	str = _T("X"); break;
			case 1: str = _T("Y"); break;
			case 2:	str = _T("Z"); break;
			case 3:	str = _T("UX"); break;
			case 4: str = _T("UY"); break;
			case 5:	str = _T("UZ"); break;
			case 6:	str = _T("SUM"); break;
			}
		else
			switch (pGeom->m_Params.nTypeFactor)
			{
			case 0:	str = _T("NX"); break;
			case 1: str = _T("NY"); break;
			case 2:	str = _T("TXY"); break;
			case 3:	str = _T("MX"); break;
			case 4: str = _T("MY"); break;
			case 5:	str = _T("MXY"); break;
			case 6:	str = _T("QX"); break;
			case 7:	str = _T("QY"); break;
			case 8:	str = _T("Sx верх"); break;
			case 9: str = _T("Sx низ"); break;
			case 10:str = _T("Sy верх"); break;
			case 11:str = _T("Sy низ"); break;
			};


		strFileName.Format(pGeom->m_Params.nTypeData == Iso_Disp ? IDS_DISPLACEMENTS : IDS_STRESSES, str);
		strFileName += _T(". ");
		strFileName += pGeom->m_Params.strCurLoad;
#else
		SCHEMA *pSchem = pGeom->m_Params.Res->SchemaData;
		strFileName = pSchem->FileName;
#endif
		//PathCompactPath(pDC->GetSafeHdc(), strFileName.GetBuffer(MAX_PATH), r.right - x - nGap);
		//strFileName.ReleaseBuffer();
		pDC->TextOut(x, r.top + szText.cy / 4 - nFieldHeigh, strFileName);

		int nSize = DrawScale(pDC, r, fAspX, fAspY, bPortrait ? 4: 1, pGeom->m_Params.pDMI);
		if (bPortrait)
		{
			r.bottom-= nSize;
			pDC->MoveTo(r.left, r.bottom);
			pDC->LineTo(r.right, r.bottom);
		}
		else
		{
			r.right -= nSize;
			pDC->MoveTo(r.right, r.top);
			pDC->LineTo(r.right, r.bottom);
		}

	}
	CTime tm= CTime::GetCurrentTime();
	CString str = tm.Format(_T("%d.%m.%Y"));
	szText = pDC-> GetTextExtent(str);
	int x = rRight - szText.cx - 2*nGap;
	pDC->MoveTo(x, r.top-nFieldHeigh);
	pDC->LineTo(x, r.top);
	x+= nGap;
	pDC->TextOut(x, r.top + szText.cy / 4 - nFieldHeigh, str);

	SFloatRect	Shrink = { 1, 1, 1, 1 };
	ShrinkRect(r, &Shrink, fAspX, fAspY);
}



void CDibGlRenderer::OnBeforePrint(CDC* pDC, CPrintInfo* pInfo, CView* pView, CString strFileName, FLOAT_TYPE &fScale) 
{
	// 1. Determine the DIB size for either printing or print preview.
	CRect rcClient;
	pView->GetClientRect(&rcClient); 
	//FLOAT_TYPE fClientRatio = FLOAT_TYPE(rcClient.Height())/rcClient.Width();

	// Get page size
	m_szPage.cx  = pDC->GetDeviceCaps(HORZRES);
	m_szPage.cy = pDC->GetDeviceCaps(VERTRES);
	CRect rcDIB = CRect(CPoint(0,0), m_szPage);
	FLOAT_TYPE fAspX = pDC->GetDeviceCaps(LOGPIXELSX)/25.4f; //FLOAT_TYPE(m_szPage.cx)/szPageMM.cx; // pix/mm
	FLOAT_TYPE fAspY = pDC->GetDeviceCaps(LOGPIXELSY)/25.4f; //FLOAT_TYPE(m_szPage.cy)/szPageMM.cy;
	m_strFileName = strFileName;
	DrawFrame(pDC, rcDIB, strFileName);
	//CSize szPageMM(pDC->GetDeviceCaps(HORZSIZE),pDC->GetDeviceCaps(VERTSIZE));
	

//	CRect &r= rcDIB;
//	pDC->MoveTo(r.left, r.top); // Ограничивающий прямоугольник
//	pDC->LineTo(r.right, r.top);
//	pDC->LineTo(r.right, r.bottom);
//	pDC->LineTo(r.left, r.bottom);
//	pDC->LineTo(r.left, r.top);
	
	CSize szDIB;
	// Use higher resolution for printing.
	// Adjust size according screen's ratio.
	szDIB = rcDIB.Size();
	m_rcDIB = rcDIB;
	// Reduce the Resolution if the Bitmap size is too big.
	// Ajdust the maximum value, which is depends on printer's memory.
	// I use 20 MB. 
	while (szDIB.cx*szDIB.cy > 20e6)   
	{
		szDIB.cx = szDIB.cx/2;
		szDIB.cy = szDIB.cy/2;
		fAspX/=2;
		fAspY/=2;
	}

	TRACE("Buffer size: %d x %d = %6.2f MB\n", szDIB.cx, szDIB.cy, szDIB.cx*szDIB.cy*0.000001);
	
	// 2. Create DIB Section

	int nBorder = int(4*fAspX);
	BindDib(pView->m_hWnd, szDIB, nBorder);

	fScale = 0.25f*fAspX;
	//SetFrustum();

	// 9. Create display list with the newly created memory RC
	//CreateDisplayList(1);
}

void CDibGlRenderer::OnAfterPrint(CDC* pDC) 
{
	// Now the image is in the DIB already. We don't need the memory RC anymore. 
	// We'll copy the image to the DC for printing or print preview.
	// Stretch image to fit in the target size.
	SetStretchBltMode(pDC->GetSafeHdc(), COLORONCOLOR);
	int nRet = ::StretchDIBits(pDC->GetSafeHdc(),
							  m_rcDIB.left, m_rcDIB.top, 
							  m_rcDIB.Width(), m_rcDIB.Height(), 
							  0, 0,
							  m_bmi.bmiHeader.biWidth, m_bmi.bmiHeader.biHeight,
							  static_cast<GLubyte*>(m_pBitmapBits),
							  &m_bmi, DIB_RGB_COLORS, SRCCOPY);

	if(nRet == GDI_ERROR)
		TRACE0("Failed in StretchDIBits()");
	ReleaseDib();
	CRect rcDIB = CRect(CPoint(0,0), m_szPage);
	DrawFrame(pDC, rcDIB, m_strFileName);

}

void CDibGlRenderer::SetClipboardData() const
{
	HDC hMetaDC = CreateMetaFile(static_cast<LPTSTR>(nullptr));
	StretchDIBits(hMetaDC, 0, 0, m_bmi.bmiHeader.biWidth, m_bmi.bmiHeader.biHeight, 0, 0, m_bmi.bmiHeader.biWidth, 
		 m_bmi.bmiHeader.biHeight, m_pBitmapBits, &m_bmi, DIB_RGB_COLORS, SRCCOPY);
	HMETAFILE hMetafile = CloseMetaFile(hMetaDC);
	METAFILEPICT *pmfp;
	HGLOBAL hglbCopy = ::GlobalAlloc(GMEM_MOVEABLE, sizeof(METAFILEPICT));
	pmfp = static_cast<METAFILEPICT *>(::GlobalLock(hglbCopy));
	pmfp->hMF = hMetafile;
	pmfp->mm = MM_TEXT;
	pmfp->xExt = m_bmi.bmiHeader.biWidth;
	pmfp->yExt = m_bmi.bmiHeader.biHeight;
	::GlobalUnlock(hglbCopy);
	if ( ::SetClipboardData( CF_METAFILEPICT, hglbCopy ) == nullptr )
	{
		ASSERT(FALSE);
	}
	DeleteMetaFile(hMetafile);
	
}

bool CDibGlRenderer::SaveImage(LPCTSTR szFileName) const
{
    BITMAPFILEHEADER bmfHdr;
    
	CFile File(szFileName, CFile::modeCreate|CFile::modeWrite);
    bmfHdr.bfType = 'BM';
    // initialize to BitmapInfo size
    DWORD dwImageSize= m_bmi.bmiHeader.biSize;
	// Add in palette size
    WORD wColors = 0;
    WORD wPaletteSize = WORD(wColors*sizeof(RGBQUAD));
    dwImageSize+=wPaletteSize;
    
    // Add in size of actual bit array
    dwImageSize+=m_bmi.bmiHeader.biSizeImage;
    bmfHdr.bfSize = dwImageSize + sizeof(BITMAPFILEHEADER);
    bmfHdr.bfReserved1 = 0;
    bmfHdr.bfReserved2 = 0;
    bmfHdr.bfOffBits = DWORD(sizeof(BITMAPFILEHEADER)) + m_bmi.bmiHeader.biSize + wPaletteSize;
    File.Write(&bmfHdr, sizeof(BITMAPFILEHEADER));
    
    File.Write(&m_bmi, sizeof(BITMAPINFO) + (wColors-1)*sizeof(RGBQUAD));

	// Determine the number of bytes of image data to write
	DWORD dwSizeImg = m_bmi.bmiHeader.biSizeImage;
	File.Write(m_pBitmapBits, dwSizeImg);
	File.Close();
	return true;
}

