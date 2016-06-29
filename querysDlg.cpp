// querysDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "stumana.h"
#include "querysDlg.h"
#include "afxdialogex.h"


// Cquerys 对话框

IMPLEMENT_DYNAMIC(Cquerys, CDialogEx)

Cquerys::Cquerys(_ConnectionPtr& m_pConn,
	_RecordsetPtr&  m_pRec,BOOL& isquery,int& nquery,CWnd* pParent /*=NULL*/)
	: CDialogEx(Cquerys::IDD, pParent),nq(nquery),isq(isquery),m_pConnection(m_pConn),m_pRecordset(m_pRec)
{

}

Cquerys::~Cquerys()
{
}

void Cquerys::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_QICOBO, m_qicobo);
	//	DDX_Control(pDX, IDC_QEDT, m_qedt);
	//DDX_Control(pDX, IDC_QEDT, m_qedt);
	DDX_Control(pDX, IDC_QINFOEDT, m_infoedt);
	DDX_Control(pDX, IDC_CMDEDT, m_cmdedt);
	DDX_Control(pDX, IDOK, m_execqbtn);
}


BEGIN_MESSAGE_MAP(Cquerys, CDialogEx)
	ON_BN_CLICKED(IDBACK, &Cquerys::OnBnClickedBack)
	ON_CBN_SELCHANGE(IDC_QICOBO, &Cquerys::OnCbnSelchangeQicobo)
	ON_BN_CLICKED(IDOK, &Cquerys::OnBnClickedOk)
	ON_BN_CLICKED(ID_ADDQ_BTN, &Cquerys::OnBnClickedAddqBtn)
	ON_CBN_DROPDOWN(IDC_QICOBO, &Cquerys::OnCbnDropdownQicobo)
END_MESSAGE_MAP()


// Cquerys 消息处理程序


void Cquerys::OnBnClickedBack()
{
	// TODO: 在此添加控件通知处理程序代码
	isq=FALSE;
	OnOK();
}

void Cquerys::load_combo()
{
	VARIANT var;

	m_qicobo.ResetContent();

	std::vector<CString> tn_list;
	exec_sql("SELECT * FROM QUERYS ORDER BY ID");

	//m_qicobo.AddString(_T("who"));
	//m_qicobo.AddString(_T("aaa"));


	try
	{
		while(!m_pRecordset->adoEOF)
		{
			var=m_pRecordset->GetCollect("INFO");
			
			tn_list.push_back(var.bstrVal);
			m_pRecordset->MoveNext();
		}
	}
	catch(_com_error &e)
	{
		show_exception(e.Description());
		return;
	}

	

	for(int i=0;i<tn_list.size();i++)
		m_qicobo.AddString(tn_list[i]);

}


BOOL Cquerys::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	load_combo();


	//m_qicobo.AddString(_T("Who selects all the courses."));
	//m_qicobo.AddString(_T("Who selects \"Data Base\" with the second highest mark."));



	return TRUE;  // return TRUE unless you set the focus to a control
}


void Cquerys::OnCbnSelchangeQicobo()
{
	// TODO: 在此添加控件通知处理程序代码
	int nIndex = m_qicobo.GetCurSel();
	
	VARIANT var_info;
	VARIANT var_cmd;
	CString cmd;
	cmd.Format(_T("SELECT INFO,CMD FROM QUERYS WHERE ID=%d"),nIndex);
	exec_sql(cmd);
	try
	{
		var_info=m_pRecordset->GetCollect("INFO");
		m_infoedt.SetWindowTextW(var_info.bstrVal);
		var_cmd=m_pRecordset->GetCollect("CMD");
		m_cmdedt.SetWindowTextW(var_cmd.bstrVal);

		m_execqbtn.EnableWindow(TRUE);
	}
	catch(_com_error &e)
	{
		show_exception(e.Description());
		return;
	}
	
	
	
	



	nq=nIndex;
}


void Cquerys::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
	isq=TRUE;
	CDialogEx::OnOK();
}


void Cquerys::show_exception(const char* info)
{
	CString info_cstr(info);
	::MessageBox(NULL,info_cstr,_T("Error"),MB_ICONERROR);
}

void Cquerys::show_exception(CString info)
{
	::MessageBox(NULL,info,_T("Error"),MB_ICONERROR);
}

void Cquerys::exec_sql(const char* cmd)
{
	try
	{
		m_pRecordset=m_pConnection->Execute(cmd,NULL,adCmdText);
		m_pConnection->Execute("commit",NULL,adCmdText);
	}
	catch(_com_error& e)
	{
		show_exception(e.Description());
	}
}

void Cquerys::exec_sql(const CString& cmd)
{
	try
	{
		_bstr_t str=(_bstr_t)cmd.GetString();
		m_pRecordset=m_pConnection->Execute((_bstr_t)cmd,NULL,adCmdText);
		m_pConnection->Execute("commit",NULL,adCmdText);
	}
	catch(_com_error &e)
	{
		show_exception(e.Description());
	}
}
void Cquerys::exec_sql(const _bstr_t& cmd)
{
	try
	{
		m_pRecordset=m_pConnection->Execute(cmd,NULL,adCmdText);
		m_pConnection->Execute("commit",NULL,adCmdText);
	}
	catch(_com_error &e)
	{
		show_exception(e.Description());
	}
}






void Cquerys::OnBnClickedAddqBtn()
{
	// TODO: 在此添加控件通知处理程序代码
	CString cmd_str;
	CString info_str;
	m_cmdedt.GetWindowTextW(cmd_str);
	m_infoedt.GetWindowTextW(info_str);


	try
	{
		_bstr_t str=(_bstr_t)cmd_str.GetString();
		//CString temp_cmd=cmd_str;
		//temp_cmd.Remove('"');
		m_pRecordset=m_pConnection->Execute((_bstr_t)cmd_str,NULL,adCmdText);
		m_pConnection->Execute("commit",NULL,adCmdText);
	}
	catch(_com_error &e)
	{
		show_exception(e.Description());
		return;
	}


	

	int count;
	exec_sql("SELECT COUNT(*) NUM FROM QUERYS");

	VARIANT var;

	try
	{
		var=m_pRecordset->GetCollect("NUM");
		count=var.intVal;
	}
	catch(_com_error &e)
	{
		show_exception(e.Description());
		return;
	}


	CString cmd;

	int n=cmd_str.GetLength();

	for(int i=0;i<cmd_str.GetLength();i++)
		if(cmd_str.GetAt(i)=='\'')
		{
			cmd_str.Insert(i,_T("'"));
			i++;
		}
		

	

	cmd.Format(_T("INSERT INTO QUERYS VALUES(%d,'%s','%s')"),count,info_str,cmd_str);

	exec_sql(cmd);
	load_combo();


}


void Cquerys::OnCbnDropdownQicobo()
{
	// TODO: 在此添加控件通知处理程序代码
	m_execqbtn.EnableWindow(FALSE);

}
