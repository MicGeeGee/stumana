#pragma once
#include "afxwin.h"


// Cquerys �Ի���

class Cquerys : public CDialogEx
{
	DECLARE_DYNAMIC(Cquerys)

public:
	Cquerys(BOOL& isquery,int& nquery,CWnd* pParent = NULL);   // ��׼���캯��
	
	

	virtual ~Cquerys();

// �Ի�������
	enum { IDD = IDD_QUERYS_DIALOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

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
