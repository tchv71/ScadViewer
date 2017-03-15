// MouseManipulatorWnd.cpp : implementation file
//
// Copyright (C) 1998,1999,2000,2003,2004,2005,2006  Dmitry Tcvetkov aka TCHV
//
// All Rights Reserved
//
// Disclaimer : this text is under authority of goverment laws, US and Russian Federation
// Unauthorizing compilation, modification and re-engineering is strictly prohibited

#include "stdafx.h"
#include "resource.h"
#include "MouseManipulatorWnd.h"
#include "View3DBox.h"
#include <gl\gl.h>
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMouseManipulatorWnd

CMouseManipulatorWnd::CMouseManipulatorWnd(SPerspectiveView	&rViewPos, TV3DBState& rState,  CCutter &rCutter) :
	z_rot1(0), x_rot1(0),
    bFirstDown(false), m_ViewPos(rViewPos), m_Cutter(rCutter), Down(false),
	State(rState),
	oState(ST_ROTATE),
	m_pOwner(nullptr)
{
}

CMouseManipulatorWnd::~CMouseManipulatorWnd()
{
}


BEGIN_MESSAGE_MAP(CMouseManipulatorWnd, CWnd)
	//{{AFX_MSG_MAP(CMouseManipulatorWnd)
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_MOUSEMOVE()
	ON_WM_RBUTTONDOWN()
	ON_WM_RBUTTONUP()
	ON_WM_MBUTTONDOWN()
	ON_WM_MBUTTONUP()
	ON_WM_SETCURSOR()
	ON_WM_LBUTTONDBLCLK()
	//}}AFX_MSG_MAP
	ON_WM_ERASEBKGND()
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// CMouseManipulatorWnd message handlers
#define TWO_CLICKS
#define WIN_MODE	(State == ST_ZOOM || State == ST_CUT || State == ST_INV_CUT)
void CMouseManipulatorWnd::OnLButtonDown(UINT nFlags, CPoint point)
{
	if (State == ST_SELECT)
	{
		if (m_pOwner->Select(point))
			m_pOwner->Redraw();
		return;

	}
	//if (Shift.Contains(ssDouble)|| (!Shift.Contains(ssLeft)&&!Shift.Contains(ssRight))) return;
#ifdef TWO_CLICKS
	if(WIN_MODE)
	{
		if(Down && bFirstDown)
		{
			bFirstDown = false;

			//FMouseUp(Sender,Button,Shift,X,Y);
			OnLButtonUp(nFlags, point);
			return;
		}
		else
			bFirstDown = true;
	}
	else
		bFirstDown = false;
#endif
	m_ptMouseDown = point;
	Down = true;
	MovePt = point;

	m_vpSave = m_ViewPos;

	m_ViewPos.Rot->GetRot(z_rot1, x_rot1);
	SetCapture();

	CWnd::OnLButtonDown(nFlags, point);
}

void CMouseManipulatorWnd::OnLButtonUp(UINT nFlags, CPoint point)
{
#ifdef TWO_CLICKS
	if(bFirstDown && WIN_MODE)
		return;
#endif
	ReleaseCapture();

	int X = point.x;
	int Y = point.y;
	if(!Down)
		return;

	//if (oPopupMenu) PopupMenu=oPopupMenu;
	Down = false;
	switch(State)
	{
		case ST_ZOOM:
			{
				//TRect clr = ClientRect;
				CRect	clr;
				GetClientRect(clr);

				//Canvas->Pen->Mode = pmNotXor;
				//Canvas->Rectangle(m_ptMouseDown.x, m_ptMouseDown.y, MovePt.x, MovePt.y);
				CDC		*pDC = GetDC();
				int		nOldRop = pDC->SetROP2(R2_XORPEN);
				CPen	pen(PS_DOT, 1, RGB(0, 0, 0));
				CPen	*pOldPen = pDC->SelectObject(&pen);

				int		clw = clr.Width(), clh = clr.Height();
				int		WinX = abs(point.x - m_ptMouseDown.x), WinY = abs(point.y - m_ptMouseDown.y);
				if((WinX == 0) || (WinY == 0))
					return;

				FLOAT_TYPE	SclX = clw / FLOAT_TYPE(WinX), SclY = clh / FLOAT_TYPE(WinY);
				FLOAT_TYPE	SclF = (SclX < SclY) ? SclX : SclY;
				m_ViewPos.Xorg -= ((clr.left+clr.right)/2-(point.x + m_ptMouseDown.x)/2)/m_ViewPos.ScrScale;
				m_ViewPos.Yorg += ((clr.top+clr.bottom)/2-(point.y + m_ptMouseDown.y)/2)/m_ViewPos.ScrScale;
				m_ViewPos.ScrScale *= SclF;

				m_ViewPos.ViewSizeX /= SclF;
				m_ViewPos.ViewSizeY /= SclF;
				m_ViewPos.TargetDist /= SclF;
				
				pDC->SetROP2(nOldRop);
				pDC->SelectObject(pOldPen);
				ReleaseDC(pDC);
				m_pOwner->Redraw();
			}
			break;
		case ST_ROTATE:
			break;
		case ST_CUT:
		case ST_INV_CUT:
			{
				//TRect clr = ClientRect;
				CWaitCursor cur;
				CRect	clr;
				GetClientRect(clr);

				int	xc = (clr.left + clr.right) / 2;
				int yc = (clr.top + clr.bottom) / 2;
				FLOAT_TYPE	x1, x2, y1, y2;
//				if(X > m_ptMouseDown.x)
//				{
					x1 =  ((X < m_ptMouseDown.x ? X : m_ptMouseDown.x) - xc) / m_ViewPos.ScrScale + m_ViewPos.Xorg;
					y1 = -((Y > m_ptMouseDown.y ? Y : m_ptMouseDown.y) - yc) / m_ViewPos.ScrScale + m_ViewPos.Yorg;
					x2 =  ((X > m_ptMouseDown.x ? X : m_ptMouseDown.x) - xc) / m_ViewPos.ScrScale +	m_ViewPos.Xorg;
					y2 = -((Y < m_ptMouseDown.y ? Y : m_ptMouseDown.y) - yc) / m_ViewPos.ScrScale +	m_ViewPos.Yorg;
//				}

				m_Cutter.DoCut(State == ST_INV_CUT ? INV_CUT : CUT, m_ViewPos.Rot, x1, y1, x2, y2);
				State = m_pOwner->GetStateBeforeCut();
				m_pOwner->ZoomAll();
				//if (FOnCut)FOnCut(x1,y1,x2,y2);
				//if (FOnRepaint) FOnRepaint(this);
			}
			break;
		case ST_PAN:
			m_ViewPos.Xorg -= (X - m_ptMouseDown.x) / m_ViewPos.ScrScale;
			m_ViewPos.Yorg += (Y - m_ptMouseDown.y) / m_ViewPos.ScrScale;

			//if (FOnRepaint) FOnRepaint(this);
			m_pOwner->Redraw();
			break;
	case ST_SELECT: break;
	case ST_WALK: break;
	case ST_LOOK_AROUND: break;
	case ST_ZOOM_IN_OUT: break;
	default: break;
	}

	CWnd::OnLButtonUp(nFlags, point);
}

inline FLOAT_TYPE CMouseManipulatorWnd::MouseAngle(int ang)
{
	return ang * atanf(1) / 45 / 2;
}

void CMouseManipulatorWnd::Cross(int x1, int y1, int x2, int y2)
{
#if 0
	CDC		*pDC = GetDC();
	int		nOldRop = pDC->SetROP2(R2_XORPEN);
	CPen	pen(PS_DOT, 1, RGB(0, 0, 0));
	CPen	*pOldPen = pDC->SelectObject(&pen);
	HGDIOBJ  hOldBrush= pDC->SelectObject(::GetStockObject(NULL_BRUSH));
	pDC->Rectangle(m_ptMouseDown.x,	m_ptMouseDown.y, MovePt.x, MovePt.y);
	//pDC->MoveTo(m_ptMouseDown.x, m_ptMouseDown.y);
	//pDC->LineTo(MovePt.x, MovePt.y);

	pDC->SetROP2(nOldRop);
	pDC->SelectObject(hOldBrush);
	pDC->SelectObject(pOldPen);
	ReleaseDC(pDC);
#else
	int			VP[4];
	glGetIntegerv(GL_VIEWPORT, VP);

	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	glLoadIdentity();

	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
	glLoadIdentity();
	glColor3f(0,0,0);
	glDisable(GL_DEPTH_TEST);
	glOrtho(0.0, VP[2], VP[3], 0, 0, 1);	// Установка экранной СК
	glEnable(GL_LINE_STIPPLE);
	glLineStipple(1,0xAAAA);
	glBegin(GL_LINE_LOOP);	// Ограничивающий прямоугольник
		glVertex3d(x1, y1, 0);
		glVertex3d(x1, y2, 0);
		glVertex3d(x2, y2, 0);
		glVertex3d(x2, y1, 0);
	glEnd();
	glDisable(GL_LINE_STIPPLE);
	glMatrixMode(GL_PROJECTION);
	glPopMatrix();
	glMatrixMode(GL_MODELVIEW);
	glPopMatrix();
	CDC * pDc = GetDC();
	SwapBuffers(pDc->m_hDC);
	ReleaseDC(pDc);

#endif
}

void CMouseManipulatorWnd::OnMouseMove(UINT nFlags, CPoint point)
{
#ifdef TWO_CLICKS
	if(Down && (WIN_MODE || (nFlags & (MK_LBUTTON | MK_MBUTTON)) != 0))
#else
		if(Down && (nFlags & (MK_LBUTTON | MK_MBUTTON) != 0))
#endif
		{
			if ((nFlags & MK_MBUTTON) && State != ST_PAN && State != ST_ROTATE)
				;
			else
			switch(State)
			{
				case ST_ZOOM:
				case ST_CUT:
				case ST_INV_CUT:
					{
						//Cross(m_ptMouseDown.x,m_ptMouseDown.y,MovePt.x,MovePt.y);
						MovePt = point;
						m_pOwner->Redraw(FALSE);
						Cross(m_ptMouseDown.x,m_ptMouseDown.y,MovePt.x,MovePt.y);
					}
					break;
				case ST_ROTATE:
					{
						m_ViewPos.Rot->SetRot(z_rot1, x_rot1);

						FLOAT_TYPE	x = m_vpSave.Xorg, y = m_vpSave.Yorg, z;

	#define Z_CENTER
	#ifdef Z_CENTER
						z = m_vpSave.Zorg;
	#else
						z = y * sin(x_rot1) / cos(x_rot1);
	#endif
						m_ViewPos.Rot->Rotate_1(x, y, z);

						FLOAT_TYPE	zr = MouseAngle(point.x - m_ptMouseDown.x);
						FLOAT_TYPE	xr = MouseAngle(point.y - m_ptMouseDown.y);
						m_ViewPos.Rot->SetRot(z_rot1 + zr, x_rot1 + xr);
						m_ViewPos.Rot->Rotate(x, y, z);

						m_ViewPos.Xorg = x;
						m_ViewPos.Yorg = y;
						m_ViewPos.Zorg = z;
					}
					break;
				case ST_LOOK_AROUND:
					{
						FLOAT_TYPE	Xo, Yo, Zo;
						m_ViewPos.Rot->SetRot(z_rot1, x_rot1);
						Xo = m_vpSave.Xorg;
						Yo = m_vpSave.Yorg;
						Zo = m_vpSave.Zorg;
						Zo += m_ViewPos.TargetDist;
						m_ViewPos.Rot->Rotate_1(Xo, Yo, Zo);

						FLOAT_TYPE	zr = MouseAngle(point.x - m_ptMouseDown.x), xr = MouseAngle(point.y - m_ptMouseDown.y);
						m_ViewPos.Rot->SetRot(z_rot1 + zr, x_rot1 + xr);
						m_ViewPos.Rot->Rotate(Xo, Yo, Zo);
						Zo -= m_ViewPos.TargetDist;
						m_ViewPos.Xorg = Xo, m_ViewPos.Yorg = Yo, m_ViewPos.Zorg = Zo;
					}
					break;

				case ST_WALK:
					{
                        const FLOAT_TYPE   fltMoveSpeed = 2.0f;
                        const FLOAT_TYPE   fltForwardTreshold = tanf(45.0f*atanf(1.0f)/45.0f); // radians
						FLOAT_TYPE	Xo = m_ViewPos.Xorg, Yo = m_ViewPos.Yorg, Zo =
							m_ViewPos.Zorg;
						FLOAT_TYPE	z_r = MouseAngle(point.x - m_ptMouseDown.x);
                        if ((point.y-m_ptMouseDown.y)!=0 && fabs(z_r/MouseAngle(point.y-m_ptMouseDown.y))< fltForwardTreshold)
                            z_r = 0.0;
						CRotator r(0, x_rot1), r1(z_r, 0);
						Zo += m_ViewPos.TargetDist;
						r.Rotate_1(Xo, Yo, Zo);
						r1.Rotate(Xo, Yo, Zo);
                        if ((point.x - m_ptMouseDown.x)==0 || fabs(MouseAngle(point.y-m_ptMouseDown.y)/z_r) > fltForwardTreshold)
						    Yo -= (point.y-m_ptMouseDown.y) / m_ViewPos.ScrScale * fltMoveSpeed ;
						r.Rotate(Xo, Yo, Zo);
						Zo -= m_ViewPos.TargetDist;
						m_ViewPos.Xorg = Xo, m_ViewPos.Yorg = Yo, m_ViewPos.Zorg = Zo;

						z_rot1 += z_r;
						m_ViewPos.Rot->SetRot(z_rot1, x_rot1);
						m_ptMouseDown.x = point.x;
						m_ptMouseDown.y = point.y;
					}
					break;
				case ST_PAN:
					m_ViewPos.Xorg -= (point.x - m_ptMouseDown.x) / m_ViewPos.ScrScale;
					m_ViewPos.Yorg += (point.y - m_ptMouseDown.y) / m_ViewPos.ScrScale;
					m_ptMouseDown = point;
					break;
			case ST_SELECT: break;
			case ST_ZOOM_IN_OUT: break;
			default: break;
			}

			if(State != ST_ZOOM && State != ST_CUT && State != ST_INV_CUT)
				m_pOwner->Redraw();
		}
		else if((nFlags & MK_RBUTTON) != 0 && Down)
		{
			if(abs(point.y - m_ptMouseDown.y) < 2)
				return;

			//PopupMenu=nullptr;
			m_pOwner->EnablePopupMenu(false);
			FLOAT_TYPE	Sc = FLOAT_TYPE(m_ptMouseDown.y - point.y) / 100;
			FLOAT_TYPE	S = (Sc > 0) ? 1 + Sc : 1 / (1 - Sc);
			m_ViewPos.ScrScale = m_vpSave.ScrScale * S;
			m_ViewPos.ViewSizeX = m_vpSave.ViewSizeX / S;
			m_ViewPos.ViewSizeY = m_vpSave.ViewSizeY / S;
			m_ViewPos.TargetDist = m_vpSave.TargetDist / S;

			//if (FOnRepaint) FOnRepaint(this);
			m_pOwner->Redraw();
		}
		else
			Down = false;

	CWnd::OnMouseMove(nFlags, point);
}

void CMouseManipulatorWnd::OnRButtonDown(UINT nFlags, CPoint point)
{
	if (Down)
		return;
	m_ptMouseDown = point;
	Down = true;
	MovePt = point;

	m_vpSave = m_ViewPos;

	//if (PopupMenu) oPopupMenu=PopupMenu;
	m_pOwner->EnablePopupMenu(true);
	m_ViewPos.Rot->GetRot(z_rot1, x_rot1);
	oState = State;

	State = ST_ZOOM_IN_OUT;
	OnSetCursor(this, 0, 0);
	SetCapture();

	CWnd::OnRButtonDown(nFlags, point);
}

void CMouseManipulatorWnd::OnRButtonUp(UINT nFlags, CPoint point)
{
	if (nFlags & (MK_MBUTTON | MK_LBUTTON))
		return;
	ReleaseCapture();
	Down = false;
	State = oState;
	CWnd::OnRButtonUp(nFlags, point);
}

void CMouseManipulatorWnd::OnMButtonDown(UINT nFlags, CPoint point)
{
	if (Down)
		return;
	m_ptMouseDown = point;
	Down = true;
	MovePt = point;
	m_vpSave = m_ViewPos;

	oState = State;
	State = nFlags & MK_SHIFT ? ST_ROTATE : ST_PAN;
	OnSetCursor(this, 0, 0);
	SetCapture();

	CWnd::OnMButtonDown(nFlags, point);
}

void CMouseManipulatorWnd::OnMButtonUp(UINT nFlags, CPoint point)
{
	if (nFlags & (MK_RBUTTON | MK_LBUTTON))
		return;
	ReleaseCapture();
	Down = false;
	State = oState;
	CWnd::OnMButtonUp(nFlags, point);
}

// ReSharper disable once CppMemberFunctionMayBeConst
BOOL CMouseManipulatorWnd::OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message)
{
	UINT nCursorIDs[] =
	{
		IDC_CURSOR_PAN,             // ST_PAN
		IDC_CURSOR_ZOOM,			// ST_ZOOM
		IDC_CURSOR_ROTATE,			// ST_ROTATE
		IDC_CURSOR_SELECT,							// ST_SELECT
		IDC_CURSOR_WALK,			// ST_WALK
		IDC_CURSOR_LOOKAROUND,		// ST_LOOK_AROUND
		IDC_CURSOR_ZOOM_IN_OUT,		// ST_ZOOM_IN_OUT
		IDC_CURSOR_CUT,				// ST_CUT
		IDC_CURSOR_INV_CUT			// ST_INV_CUT
	};
	
	::SetCursor(AfxGetApp()->LoadCursor(nCursorIDs[State-1]));
	return TRUE;
	//return CView::OnSetCursor(pWnd, nHitTest, message);
}

void CMouseManipulatorWnd::OnLButtonDblClk(UINT nFlags, CPoint point) 
{
	GetParentFrame()->SendMessage(WM_COMMAND, ID_SCAD_VIEW_DBLCLICK);
	
	CWnd::OnLButtonDblClk(nFlags, point);
}


BOOL CMouseManipulatorWnd::OnEraseBkgnd(CDC* pDC)
{
	C3DBoxView *pView = dynamic_cast<C3DBoxView *>(GetParent());
	if (pView && pView->OnEraseBkgnd(pDC))
		return TRUE;
	CRect rc;
	GetClientRect(&rc);
	pDC->FillRect(&rc, CBrush::FromHandle(HBRUSH(GetStockObject(WHITE_BRUSH))));
	return CWnd::OnEraseBkgnd(pDC);
}
