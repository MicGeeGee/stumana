#pragma once
#include "afxwin.h"


// Cquerys 对话框

class Cquerys : public CDialogEx
{
	DECLARE_DYNAMIC(Cquerys)

public:
	Cquerys(BOOL& isquery,int& nquery,CWnd* pParent = NULL);   // 标准构造函数
	
	

	virtual ~Cquerys();

// 对话框数据
	enum { IDD = IDD_QUERYS_DIALOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedBack();
	virtual BOOL OnInitDialog();
	CComboBox m_qicobo;

	int& nq;
	BOOL& isq;

	afx_msg void OnCbnSelchangeQicobo();
	afx_msg void OnBnClickedOk();
};
