// Csignin.cpp : 实现文件
//

#include "stdafx.h"
#include "stumana.h"
#include "signinDlg.h"
#include "afxdialogex.h"


// Csignin 对话框

IMPLEMENT_DYNAMIC(Csignin, CDialogEx)



Csignin::Csignin(_ConnectionPtr& mpconn, _CommandPtr& mpcmd,
	_RecordsetPtr&  mprecrd,CWnd* pParent)
	: CDialogEx(Csignin::IDD, pParent),m_pConnection(mpconn),m_pCommand(mpcmd),m_pRecordset(mprecrd)
{
	//m_pConnection=mpconn;
	//m_pCommand=mpcmd;
	//m_pRecordset=mprecrd;
}


BOOL Csignin::conn()
{
	// TODO: 在此添加控件通知处理程序代码
	try
	{
		hr = m_pConnection.CreateInstance("ADODB.Connection");///创建Connection对象
		if(SUCCEEDED(hr))
		{
			//={Microsoft ODBC Driver For oracle};    MSDAORA.1;
			m_pConnection->ConnectionTimeout = 0;
			m_pConnection->CursorLocation=adUseClient;
			
			CString conn_str;
			CString un;
			CString pw;
			CString ds;

			m_unedt.GetWindowTextW(un);
			m_pwedt.GetWindowTextW(pw);
			m_dsedt.GetWindowTextW(ds);

			conn_str+=_T("Provider=OraOLEDB.Oracle.1;Password=");
			conn_str+=pw;
			conn_str+=_T(";Persist Security Info=True;User ID=");
			conn_str+=un;
			conn_str+=_T(";Data Source=")+ds;

			//conn_str+=_T(";Data Source=ORCL11G");

			hr = m_pConnection->Open((_bstr_t)conn_str.GetString(),(_bstr_t)_T(""),(_bstr_t)_T(""),adConnectUnspecified);//adConnectUnspecified  adModeUnknown
			// hr = m_pConnection->Open( "Provider=Microsoft.Jet.OLEDB.4.0;Data Source=db1.mdb", "", "", adModeUnknown);
			//m_pConnection->PutDefaultDatabase ((_bstr_t)"DB");//设置默认数据库
			m_pCommand.CreateInstance(__uuidof(Command));
			m_pCommand->CommandTimeout = 5;
			m_pCommand->ActiveConnection = m_pConnection;

			m_pRecordset.CreateInstance(__uuidof(Recordset));

			//MessageBox(_T("Successful."));
			return TRUE;
		}
	}
	catch(_com_error& e)///捕捉异常
	{
		//MessageBox(e.ErrorMessage());

		MessageBox(_T("Cannot sign in."));
		return FALSE;
		//show_exception(e.ErrorMessage());
	}

	

}

Csignin::~Csignin()
{
}

void Csignin::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_USRNEDT, m_unedt);
	DDX_Control(pDX, IDC_PWEDT, m_pwedt);
	DDX_Control(pDX, IDC_DSEDT, m_dsedt);
}


BEGIN_MESSAGE_MAP(Csignin, CDialogEx)
	ON_BN_CLICKED(IDOK, &Csignin::OnBnClickedOk)
	ON_BN_CLICKED(ID_SIGNINBTN, &Csignin::OnBnClickedSigninbtn)
END_MESSAGE_MAP()


// Csignin 消息处理程序


void Csignin::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
	//CDialogEx::OnOK();
	exit(0);
}




void Csignin::OnBnClickedSigninbtn()
{
	// TODO: 在此添加控件通知处理程序代码
	if(conn())
		OnOK();

}


BOOL Csignin::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	m_dsedt.SetWindowTextW(_T("ORCL11G"));

	return TRUE;
}
