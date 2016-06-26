
// stumanaDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "stumana.h"
#include "stumanaDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CstumanaDlg �Ի���



CstumanaDlg::CstumanaDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CstumanaDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CstumanaDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CstumanaDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_CONNBTN, &CstumanaDlg::OnBnClickedConnbtn)
END_MESSAGE_MAP()


// CstumanaDlg ��Ϣ�������

BOOL CstumanaDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// ���ô˶Ի����ͼ�ꡣ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO: �ڴ���Ӷ���ĳ�ʼ������

	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CstumanaDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ����������о���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ����ͼ��
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
HCURSOR CstumanaDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CstumanaDlg::OnBnClickedConnbtn()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	_ConnectionPtr m_pConnection;
	_CommandPtr    m_pCommand;
	_RecordsetPtr  m_pRecordset;
	
	HRESULT hr;
	try
	{
		hr = m_pConnection.CreateInstance("ADODB.Connection");///����Connection����
		if(SUCCEEDED(hr))
		{//={Microsoft ODBC Driver For oracle};    MSDAORA.1;
			m_pConnection->ConnectionTimeout = 0;
			m_pConnection->CursorLocation=adUseClient;
			
			
			hr = m_pConnection->Open((_bstr_t)_T("Provider=OraOLEDB.Oracle.1;Password=1111;Persist Security Info=True;User ID=SCOTT;Data Source=ORCL11G"),(_bstr_t)_T(""),(_bstr_t)_T(""),adConnectUnspecified);//adConnectUnspecified  adModeUnknown

			

			// hr = m_pConnection->Open( "Provider=Microsoft.Jet.OLEDB.4.0;Data Source=db1.mdb", "", "", adModeUnknown);
			//m_pConnection->PutDefaultDatabase ((_bstr_t)"DB");//����Ĭ�����ݿ�
			m_pCommand.CreateInstance(__uuidof(Command));
			m_pCommand->CommandTimeout = 5;
			m_pCommand->ActiveConnection = m_pConnection;
			MessageBox(_T("Successful."));
		}
	}
	catch(_com_error e)///��׽�쳣
	{
		MessageBox(e.ErrorMessage());
	}
	
	m_pConnection->Execute("INSERT INTO DEPT VALUES(50,'MANAGEMNET','LA')",NULL,adCmdText);

	m_pRecordset.CreateInstance(__uuidof(Recordset));
	CString dname;
	CString loc;
	int deptno;
	VARIANT var;
	CString m_temp;
	try
	{
		
		m_pRecordset->Open("SELECT * FROM DEPT",// ��ѯDemoTable���������ֶ�
		m_pConnection.GetInterfacePtr(),  // ��ȡ��ӿ��IDispatchָ��
		adOpenDynamic,
		adLockOptimistic,
		adCmdText);
		while(!m_pRecordset->adoEOF)
		{
			var = m_pRecordset->GetCollect("DEPTNO");
			if(var.vt != VT_NULL)
				deptno = var.intVal;
			var = m_pRecordset->GetCollect("DNAME");
			if(var.vt != VT_NULL)
				dname = (LPCSTR)_bstr_t(var);
			var = m_pRecordset->GetCollect("LOC");
			if(var.vt != VT_NULL)
				loc = (LPCSTR)_bstr_t(var);
			m_temp.Format(_T("deptno=%d,dname=%s,loc=%s"),deptno,dname,loc);
			

			AfxMessageBox(m_temp);
			m_pRecordset->MoveNext();
		}
	}
	catch(_com_error *e)
	{
		AfxMessageBox(e->ErrorMessage());
	}


}
