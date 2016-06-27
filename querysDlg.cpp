// querysDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "stumana.h"
#include "querysDlg.h"
#include "afxdialogex.h"


// Cquerys 对话框

IMPLEMENT_DYNAMIC(Cquerys, CDialogEx)

Cquerys::Cquerys(BOOL& isquery,int& nquery,CWnd* pParent /*=NULL*/)
	: CDialogEx(Cquerys::IDD, pParent),nq(nquery),isq(isquery)
{

}

Cquerys::~Cquerys()
{
}

void Cquerys::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_QICOBO, m_qicobo);
}


BEGIN_MESSAGE_MAP(Cquerys, CDialogEx)
	ON_BN_CLICKED(IDBACK, &Cquerys::OnBnClickedBack)
	ON_CBN_SELCHANGE(IDC_QICOBO, &Cquerys::OnCbnSelchangeQicobo)
	ON_BN_CLICKED(IDOK, &Cquerys::OnBnClickedOk)
END_MESSAGE_MAP()


// Cquerys 消息处理程序


void Cquerys::OnBnClickedBack()
{
	// TODO: 在此添加控件通知处理程序代码
	isq=FALSE;
	OnOK();
}


BOOL Cquerys::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	m_qicobo.AddString(_T("Who selects all the courses."));
	m_qicobo.AddString(_T("Who selects \"Data Base\" with the second highest mark."));



	return TRUE;  // return TRUE unless you set the focus to a control
}


void Cquerys::OnCbnSelchangeQicobo()
{
	// TODO: 在此添加控件通知处理程序代码
	int nIndex = m_qicobo.GetCurSel();
	//CString tn_str;
	//m_qicobo.GetLBText( nIndex, tn_str);
	nq=nIndex;
}


void Cquerys::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
	isq=TRUE;
	CDialogEx::OnOK();
}
