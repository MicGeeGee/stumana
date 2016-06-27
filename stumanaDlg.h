
// stumanaDlg.h : ͷ�ļ�
//

#pragma once
#include "afxcmn.h"
#include "EditTable.h"
#include "afxwin.h"
#include <vector>
#include <string>

// CstumanaDlg �Ի���
class CstumanaDlg : public CDialogEx
{
// ����
public:
	CstumanaDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_STUMANA_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
//	afx_msg void OnBnClickedConnbtn();
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
	void set_incol(const CString& attr_str,int col_index);
	void del_incol();

	void add_outcol(const CString& attr_str);
	void add_outrow(const std::vector<CString>& row);

	CString VARIANT_to_CString(const VARIANT& var);

	CString upcache_wh;
	
	std::vector<CString> upcache_attr;

	int outcol_index;

	void show_exception(const char* info);
	void show_exception(CString info);

	//CString cur_tn;

	CString elem_to_CString(const CString& elem,int type);

	void set_incol(int ncols);

	void show_res();

	void db_conn();

	afx_msg void OnBnClickedDcbtn();
	CListCtrl m_outlst;
	afx_msg void OnBnClickedInsrtbtn();
	//CEdit m_tnedt;
	afx_msg void OnEnKillfocusTnedt();

	void exec_sql(const char* cmd);
	void exec_sql(const CString& cmd);
	void exec_sql(const _bstr_t& cmd);

	CString get_tn();

	afx_msg void OnBnClickedSelbtn();
	afx_msg void OnBnClickedDelbtn();
	afx_msg void OnNMClickOutlst(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnBnClickedAltbtn();
	CButton m_altbtn;
	afx_msg void OnCbnDropdownTncobo();
	CComboBox m_tncobo;
	afx_msg void OnCbnSelchangeTncobo();
};
