#pragma once
#include "afxwin.h"


// Csignin �Ի���

class Csignin : public CDialogEx
{
	DECLARE_DYNAMIC(Csignin)

public:
	

	Csignin(_ConnectionPtr& mpconn, _CommandPtr& mpcmd,
	_RecordsetPtr&  mprecrd,CWnd* pParent = NULL);   // ��׼���캯��


	virtual ~Csignin();

// �Ի�������
	enum { IDD = IDD_SIGNIN_DIALOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
	

	_ConnectionPtr& m_pConnection;
	_CommandPtr&    m_pCommand;
	_RecordsetPtr&  m_pRecordset;
	
	HRESULT hr;

	afx_msg void OnBnClickedSigninbtn();
	CEdit m_unedt;
	CEdit m_pwedt;

	BOOL conn();
	CEdit m_dsedt;
	virtual BOOL OnInitDialog();
};
