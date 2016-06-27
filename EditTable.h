#pragma once
#include "afxcmn.h"
#include "ItemEdit.h"

#define ID_TEMPEDIT 1

class CEditTable :
	public CListCtrl
{
public:
	CEditTable(void);
	~CEditTable(void);

	CItemEdit m_edit;
	int m_nItem;
	int m_nSubItem;

	virtual void CEditTable::OnLButtonDown(UINT nFlags, CPoint point);
	int m_bEditing;

	BOOL BeginEdit();
	void CEditTable::EndEdit( BOOL bValidate );
};

