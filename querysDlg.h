#pragma once
#include "afxwin.h"
#include <vector>
#include <stack>

// Cquerys 对话框

class Cquerys : public CDialogEx
{
	DECLARE_DYNAMIC(Cquerys)

public:
	Cquerys(_ConnectionPtr& m_pConn,
	_RecordsetPtr&  m_pRec,BOOL& isquery,int& nquery,CWnd* pParent = NULL);   // 标准构造函数
	
	

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

	_ConnectionPtr& m_pConnection;
	_RecordsetPtr&  m_pRecordset;

	void exec_sql(const char* cmd);
	void exec_sql(const CString& cmd);
	void exec_sql(const _bstr_t& cmd);

	void VARIANT_to_CString(const VARIANT& var,CString& strValue);

	void show_exception(const char* info);
	void show_exception(CString info);

	int& nq;
	BOOL& isq;

	afx_msg void OnCbnSelchangeQicobo();
	afx_msg void OnBnClickedOk();
	
	void load_combo();
	
	afx_msg void OnBnClickedAddqBtn();
	CEdit m_infoedt;
	CEdit m_cmdedt;
	CButton m_execqbtn;
	afx_msg void OnCbnDropdownQicobo();
};
