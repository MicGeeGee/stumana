#pragma once
#include "afxwin.h"

class CItemEdit :
	public CEdit
{
public:
	CItemEdit(void);
	~CItemEdit(void);
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	virtual void CItemEdit::OnKillFocus(CWnd* pNewWnd);

	int m_bInputValid;
};

