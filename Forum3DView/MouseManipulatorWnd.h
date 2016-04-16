// MouseManipulatorWnd.h : header file
//
// Copyright (C) 1998,1999,2000,2003,2004,2005,2006  Dmitry Tcvetkov aka TCHV
//
// All Rights Reserved
//
// Disclaimer : this text is under authority of goverment laws, US and Russian Federation
// Unauthorizing compilation, modification and re-engineering is strictly prohibited

#if !defined(AFX_MOUSEMANIPULATORWND_H__229F278D_B472_4A4A_886E_624C665D093E__INCLUDED_)
#define AFX_MOUSEMANIPULATORWND_H__229F278D_B472_4A4A_886E_624C665D093E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "SvTypes.h"
#include "ViewLib.h"
#include "Cutter.h"

enum TV3DBState
{
	ST_PAN			= 1,
	ST_ZOOM,
	ST_ROTATE,
	ST_SELECT,
	ST_WALK,
	ST_LOOK_AROUND,
	ST_ZOOM_IN_OUT,
	ST_CUT,
	ST_INV_CUT
};
	
class I3DBoxView
{
public:
	virtual ~I3DBoxView()
	{
	}

	virtual void ZoomAll() = 0;
	virtual void Redraw(BOOL bSwap = TRUE) =0;
	virtual void EnablePopupMenu(bool bEnable) =0;
	virtual TV3DBState GetStateBeforeCut() = 0;
	virtual bool Select(CPoint pt) = 0;
	virtual void RedoCut()=0;
};


/////////////////////////////////////////////////////////////////////////////
// CMouseManipulatorWnd window

class CMouseManipulatorWnd : public CWnd
{
private:
	CPoint			m_ptMouseDown;

	FLOAT_TYPE			z_rot1;
	FLOAT_TYPE			x_rot1;

	CPoint			MovePt;
	bool			bFirstDown;


	static FLOAT_TYPE			MouseAngle(int ang);
// Construction
public:
	CMouseManipulatorWnd(SPerspectiveView	&rViewPos, TV3DBState& rState,  CCutter &rCutter);

// Attributes
public:

// Operations
public:
	void SetOwnerView(I3DBoxView *pOwner) { m_pOwner = pOwner;	}
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMouseManipulatorWnd)
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CMouseManipulatorWnd();

	// Generated message map functions
protected:
	SPerspectiveView		&m_ViewPos;
	SPerspectiveView		m_vpSave;
	CCutter					&m_Cutter;
	bool			Down;
	TV3DBState		&State;
	TV3DBState		oState;
	I3DBoxView		*m_pOwner;

	//{{AFX_MSG(CMouseManipulatorWnd)
	afx_msg void	OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void	OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void	OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void	OnRButtonDown(UINT nFlags, CPoint point);
	afx_msg void	OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg void	OnMButtonDown(UINT nFlags, CPoint point);
	afx_msg void	OnMButtonUp(UINT nFlags, CPoint point);
	afx_msg BOOL	OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message);
	afx_msg void	OnLButtonDblClk(UINT nFlags, CPoint point);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
public:
	void Cross(int x1, int y1, int x2, int y2);
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MOUSEMANIPULATORWND_H__229F278D_B472_4A4A_886E_624C665D093E__INCLUDED_)
