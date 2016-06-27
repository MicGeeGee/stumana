
// stumanaDlg.h : 头文件
//

#pragma once
#include "afxcmn.h"
#include "EditTable.h"
#include "afxwin.h"
#include <vector>
#include <string>

// CstumanaDlg 对话框
class CstumanaDlg : public CDialogEx
{
// 构造
public:
	CstumanaDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
	enum { IDD = IDD_STUMANA_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedConnbtn();
	CListCtrl m_inlst;
	
	int incol_index;

	int hitRow;
	int hitCol;


	_ConnectionPtr m_pConnection;
	_CommandPtr    m_pCommand;
	_RecordsetPtr  m_pRecordset;
	
	HRESULT hr;

	afx_msg void OnNMDblclkInlst(NMHDR *pNMHDR, LRESULT *pResult);


	CEdit m_tmpedt;
	afx_msg void OnEnKillfocusTempedt();
	afx_msg void OnBnClickedOk();
	virtual BOOL PreTranslateMessage(MSG* pMsg);

	afx_msg void OnBnClickedAcbtn();

	void add_incol();
	void del_incol();

	void add_outcol(const CString& attr_str);
	void add_outrow(const std::vector<CString>& row);

	CString VARIANT_to_CString(const VARIANT& var);


	int outcol_index;

	void show_exception(const char* info);
	void show_exception(CString info);



	void show_res();

	void db_conn();

	afx_msg void OnBnClickedDcbtn();
	CListCtrl m_outlst;
	afx_msg void OnBnClickedInsrtbtn();
	CEdit m_tnedt;
	afx_msg void OnEnKillfocusTnedt();

	void exec_sql(const char* cmd);
	void exec_sql(const CString& cmd);
	void exec_sql(const _bstr_t& cmd);


	afx_msg void OnBnClickedSelbtn();
};
