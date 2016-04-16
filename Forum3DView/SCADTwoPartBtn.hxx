//////////////////////////////////////////////////////////////////////
//
// SCADTwoPartBtn.hxx: interface for the CSCADTwoPartBtn class.
//
//////////////////////////////////////////////////////////////////////

#ifndef SCADTwoPartBtn_hxx
#define SCADTwoPartBtn_hxx


#pragma  pack(push,1)
// Group=Base Classes


/*
	Name:
	Description:
	Inputs:
	Return Value:
	Remarks:
*/
class SCADTwoPartBtn : public CMFCToolBarMenuButton
{
	DECLARE_SERIAL(SCADTwoPartBtn)

public:
	SCADTwoPartBtn()
	{
	}

	SCADTwoPartBtn(UINT uiCmdID, HMENU h, LPCTSTR lpszText) : CMFCToolBarMenuButton(uiCmdID, h, GetCmdMgr()->GetCmdImage(uiCmdID, FALSE), lpszText)
	{
	}



protected:
	CMFCPopupMenu* CreatePopupMenu() override
	{
		return CMFCToolBarMenuButton::CreatePopupMenu();
	};

	BOOL IsEmptyMenuAllowed() const override
	{
		return TRUE;
	}

	void OnChangeParentWnd(CWnd* pWndParent) override
	{
		CMFCToolBarMenuButton::OnChangeParentWnd(pWndParent);
		m_bDrawDownArrow = TRUE;
	}

	BOOL IsExclusive() const override
	{
		return FALSE;
	}
};

#pragma  pack(pop)

#endif //SCADTwoPartBtn_hxx
