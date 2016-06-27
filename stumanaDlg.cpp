
// stumanaDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "stumana.h"
#include "stumanaDlg.h"
#include "afxdialogex.h"



#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CstumanaDlg 对话框



CstumanaDlg::CstumanaDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CstumanaDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CstumanaDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_INLST, m_inlst);
	//  DDX_Control(pDX, IDC_TEMPEDT, m_tempedt);
	DDX_Control(pDX, IDC_TEMPEDT, m_tmpedt);
	DDX_Control(pDX, IDC_OUTLST, m_outlst);
	//DDX_Control(pDX, IDC_TNEDT, m_tnedt);
	DDX_Control(pDX, IDC_ALTBTN, m_altbtn);
	DDX_Control(pDX, IDC_TNCOBO, m_tncobo);
}

BEGIN_MESSAGE_MAP(CstumanaDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_CONNBTN, &CstumanaDlg::OnBnClickedConnbtn)
	ON_NOTIFY(NM_DBLCLK, IDC_INLST, &CstumanaDlg::OnNMDblclkInlst)
	ON_EN_KILLFOCUS(IDC_TEMPEDT, &CstumanaDlg::OnEnKillfocusTempedt)
	ON_BN_CLICKED(IDOK, &CstumanaDlg::OnBnClickedOk)
	ON_BN_CLICKED(IDC_ACBTN, &CstumanaDlg::OnBnClickedAcbtn)
	ON_BN_CLICKED(IDC_DCBTN, &CstumanaDlg::OnBnClickedDcbtn)
	ON_BN_CLICKED(IDC_INSRTBTN, &CstumanaDlg::OnBnClickedInsrtbtn)
	ON_EN_KILLFOCUS(IDC_TNEDT, &CstumanaDlg::OnEnKillfocusTnedt)
	ON_BN_CLICKED(IDC_SELBTN, &CstumanaDlg::OnBnClickedSelbtn)
	ON_BN_CLICKED(IDC_DELBTN, &CstumanaDlg::OnBnClickedDelbtn)
	ON_NOTIFY(NM_CLICK, IDC_OUTLST, &CstumanaDlg::OnNMClickOutlst)
	ON_BN_CLICKED(IDC_ALTBTN, &CstumanaDlg::OnBnClickedAltbtn)
	ON_CBN_DROPDOWN(IDC_TNCOBO, &CstumanaDlg::OnCbnDropdownTncobo)
	ON_CBN_SELCHANGE(IDC_TNCOBO, &CstumanaDlg::OnCbnSelchangeTncobo)
END_MESSAGE_MAP()


// CstumanaDlg 消息处理程序

BOOL CstumanaDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 设置此对话框的图标。当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码
	DWORD grid_style = m_inlst.GetExtendedStyle();
	grid_style|= LVS_EX_FULLROWSELECT;
	//grid_style|= LVS_EX_GRIDLINES;
	m_inlst.SetExtendedStyle(grid_style);
	m_outlst.SetExtendedStyle(grid_style);


	incol_index=0;
	outcol_index=0;

	m_inlst.InsertColumn(++incol_index,_T("#"),LVCFMT_CENTER,50);
	
	m_inlst.InsertItem(0,_T(""));
	m_inlst.SetItemText(0,0,_T("Values"));
	

	add_incol();
	add_incol();
	add_incol();

	//int row_index=p_lst->InsertItem(index,_T(""));
		//p_lst->SetItemText(row_index,0,cstr);


	CHeaderCtrl* p_header_ctrl=(CHeaderCtrl* )m_inlst.GetHeaderCtrl();
	//p_header_ctrl->EnableWindow(FALSE);


	m_tmpedt.ShowWindow(FALSE);
	m_altbtn.EnableWindow(FALSE);

	

	
	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CstumanaDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CstumanaDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CstumanaDlg::db_conn()
{
	try
	{
		hr = m_pConnection.CreateInstance("ADODB.Connection");///创建Connection对象
		if(SUCCEEDED(hr))
		{
			//={Microsoft ODBC Driver For oracle};    MSDAORA.1;
			m_pConnection->ConnectionTimeout = 0;
			m_pConnection->CursorLocation=adUseClient;
			hr = m_pConnection->Open((_bstr_t)_T("Provider=OraOLEDB.Oracle.1;Password=1111;Persist Security Info=True;User ID=SCOTT;Data Source=ORCL11G"),(_bstr_t)_T(""),(_bstr_t)_T(""),adConnectUnspecified);//adConnectUnspecified  adModeUnknown
			// hr = m_pConnection->Open( "Provider=Microsoft.Jet.OLEDB.4.0;Data Source=db1.mdb", "", "", adModeUnknown);
			//m_pConnection->PutDefaultDatabase ((_bstr_t)"DB");//设置默认数据库
			m_pCommand.CreateInstance(__uuidof(Command));
			m_pCommand->CommandTimeout = 5;
			m_pCommand->ActiveConnection = m_pConnection;

			m_pRecordset.CreateInstance(__uuidof(Recordset));

			MessageBox(_T("Successful."));
		}
	}
	catch(_com_error e)///捕捉异常
	{
		MessageBox(e.ErrorMessage());

		show_exception(e.ErrorMessage());
	}

}

void CstumanaDlg::OnBnClickedConnbtn()
{
	// TODO: 在此添加控件通知处理程序代码
	db_conn();
	m_pRecordset=m_pConnection->Execute("SELECT * FROM TAB",NULL,adCmdText);

	show_res();

	return;
	
	

	m_pRecordset.CreateInstance(__uuidof(Recordset));
	CString dname;
	CString loc;
	int deptno;
	VARIANT var;
	CString m_temp;
	try
	{
		
		m_pRecordset->Open("SELECT * FROM DEPT",// 查询DemoTable表中所有字段
		m_pConnection.GetInterfacePtr(),  // 获取库接库的IDispatch指针
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

void CstumanaDlg::add_outcol(const CString& attr_str)
{
	m_outlst.InsertColumn(++outcol_index,attr_str,LVCFMT_CENTER,100);
}

void CstumanaDlg::add_outrow(const std::vector<CString>& row)
{
	int index=m_outlst.GetItemCount();
	int row_index=m_outlst.InsertItem(index,_T(""));
	for(int i=0;i<row.size();i++)
		m_outlst.SetItemText(row_index,i,row[i]);
}


CString CstumanaDlg::VARIANT_to_CString(const VARIANT& var)
{
      CString strValue;
     _variant_t var_t;
     _bstr_t bst_t;
     time_t cur_time;
     CTime time_value;
     COleCurrency var_currency;
	 char str[100];

     switch(var.vt)
    {
          case VT_EMPTY:
                strValue=_T("");
                 break;
          case VT_UI1:
				sprintf(str,("%d"),var.bVal);
                strValue=CString(str);
                break;
         case VT_I2:
				sprintf(str,("%d"),var.iVal);
                strValue=CString(str);   
			    break;
         case VT_I4:
                sprintf(str,("%d"),var.lVal);
                strValue=CString(str);
				break;
         case VT_R4:
                sprintf(str,("%f"),var.fltVal);
                strValue=CString(str);
				break;
         case VT_R8:
                sprintf(str,("%f"),var.dblVal);
                strValue=CString(str);
				break;
        case VT_CY:
                var_currency=var;
                strValue=var_currency.Format(0);
                break;
        case VT_BSTR:
                var_t=var;
                bst_t=var_t;
                sprintf(str,("%s"),(const char*)bst_t);
                strValue=CString(str);
				break;
        case VT_NULL:
                strValue=_T("");
                break;
        case VT_DATE:
                cur_time = (long)var.date;
                time_value=cur_time;
                strValue=time_value.Format(_T("%A,%B%d,%Y"));
				break;
        case VT_BOOL:
                sprintf(str,("%d"),var.boolVal);
                strValue=CString(str);
				break;
		case VT_DECIMAL:
				//sprintf(str,("%d"),var.bVal);
				sprintf(str,("%d"),var.intVal);
                strValue=CString(str);
				break;
        default: 
                strValue=_T("");
                break;
       }
       return strValue;
}

void CstumanaDlg::show_res()
{
	VARIANT var;

	std::vector<std::vector<CString> > res;
	
	std::vector<CString> one_row;
	std::vector<CString> attr_strs;
	

	int ncols;
	
	m_outlst.DeleteAllItems();
	while(outcol_index>0)
		m_outlst.DeleteColumn(--outcol_index);
	

	
	try
	{
		ncols=m_pRecordset->GetFields()->GetCount();

		for(int i=0;i<ncols;i++)
		{
			CString str=(LPCTSTR)(m_pRecordset->GetFields()->GetItem((long)i)->GetName());
			attr_strs.push_back(str);
			add_outcol(str);
		}



		while(!m_pRecordset->adoEOF)
		{
			
			for(int i=0;i<ncols;i++)
			{
				var=m_pRecordset->GetCollect(attr_strs[i].GetString());
				one_row.push_back(VARIANT_to_CString(var));
			}
			
			

			add_outrow(one_row);
			m_pRecordset->MoveNext();
			one_row.clear();
		}
	}
	catch(_com_error &e)
	{
		show_exception(e.ErrorMessage());
	}
}



void CstumanaDlg::OnNMDblclkInlst(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	
	LVHITTESTINFO info;
	info.pt = pNMItemActivate->ptAction;

	if(m_inlst.SubItemHitTest(&info) != -1 )
	{
		hitRow = info.iItem;
		hitCol = info.iSubItem;

		if(hitCol == 0)
		{
			*pResult = 0;
			return;
		}

		if(m_tmpedt.m_hWnd == NULL)
		{
			RECT rect;
			rect.left = 0;
			rect.top = 0;
			rect.bottom = 15;
			rect.right = 200;
			m_tmpedt.Create(WS_CHILD | ES_LEFT | WS_BORDER | ES_AUTOHSCROLL | ES_WANTRETURN | ES_MULTILINE, rect, this, 101);
			m_tmpedt.SetFont(this->GetFont(), FALSE);
		}
		CRect rect;
		m_inlst.GetSubItemRect(info.iItem, info.iSubItem, LVIR_BOUNDS, rect);
		rect.top += 27;
		rect.left += 109;
		rect.right += 109;
		rect.bottom += 26;
 
		m_tmpedt.SetWindowText(m_inlst.GetItemText(info.iItem, info.iSubItem));
		m_tmpedt.MoveWindow(&rect, TRUE);
		m_tmpedt.ShowWindow(TRUE);
		m_tmpedt.SetFocus();
	}
	*pResult = 0;
}




void CstumanaDlg::OnEnKillfocusTempedt()
{
	// TODO: 在此添加控件通知处理程序代码
	if(m_tmpedt.m_hWnd != NULL)
    {
        m_tmpedt.ShowWindow(FALSE);
        if(hitRow != -1)
        {
            CString text;
            m_tmpedt.GetWindowText(text);
            m_inlst.SetItemText(hitRow, hitCol, text);
        }
    }
	hitCol = hitRow = -1;
}


void CstumanaDlg::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
	CDialogEx::OnOK();
}


BOOL CstumanaDlg::PreTranslateMessage(MSG* pMsg)
{
	// TODO: 在此添加专用代码和/或调用基类

	if(pMsg->message==WM_KEYDOWN)
	{
		//Capture the 'ENTER' and 'ESC'.
		if(pMsg->wParam==VK_RETURN)
		{
			OnEnKillfocusTempedt();
			return TRUE;
		}
		if(pMsg->wParam==VK_ESCAPE)
		{
			OnOK();
			return TRUE;
		}
	}
	


	return CDialogEx::PreTranslateMessage(pMsg);
}


CString CstumanaDlg::get_tn()
{
	int nIndex = m_tncobo.GetCurSel();
	CString tn_str;
	m_tncobo.GetLBText( nIndex, tn_str);
	return tn_str;
}


void CstumanaDlg::OnBnClickedAcbtn()
{
	// TODO: 在此添加控件通知处理程序代码
	add_incol();
}


void CstumanaDlg::add_incol()
{
	char num[100];
	sprintf(num,"%d",incol_index);
	m_inlst.InsertColumn(++incol_index,CString(num),LVCFMT_CENTER,70);
}
void CstumanaDlg::set_incol(const CString& attr_str,int col_index)
{
	m_inlst.SetItemText(0,col_index+1,attr_str);
}

void CstumanaDlg::del_incol()
{
	if(incol_index!=2)
		m_inlst.DeleteColumn(--incol_index);	
	else
		show_exception("The number of columns cannot be less than 1.");
}

void CstumanaDlg::OnBnClickedDcbtn()
{
	// TODO: 在此添加控件通知处理程序代码
	del_incol();
}

void CstumanaDlg::show_exception(const char* info)
{
	CString info_cstr(info);
	::MessageBox(NULL,info_cstr,_T("Error"),MB_ICONERROR);
}

void CstumanaDlg::show_exception(CString info)
{
	::MessageBox(NULL,info,_T("Error"),MB_ICONERROR);
}


void CstumanaDlg::exec_sql(const char* cmd)
{
	try
	{
		m_pRecordset=m_pConnection->Execute(cmd,NULL,adCmdText);
		m_pConnection->Execute("commit",NULL,adCmdText);
	}
	catch(_com_error& e)
	{
		show_exception(e.ErrorMessage());
	}
}

void CstumanaDlg::exec_sql(const CString& cmd)
{
	try
	{
		_bstr_t str=(_bstr_t)cmd.GetString();
		m_pRecordset=m_pConnection->Execute((_bstr_t)cmd,NULL,adCmdText);
		m_pConnection->Execute("commit",NULL,adCmdText);
	}
	catch(_com_error &e)
	{
		show_exception(e.ErrorMessage());
	}
}
void CstumanaDlg::exec_sql(const _bstr_t& cmd)
{
	try
	{
		m_pRecordset=m_pConnection->Execute(cmd,NULL,adCmdText);
		m_pConnection->Execute("commit",NULL,adCmdText);
	}
	catch(_com_error &e)
	{
		show_exception(e.ErrorMessage());
	}
}


void CstumanaDlg::OnBnClickedInsrtbtn()
{
	// TODO: 在此添加控件通知处理程序代码

	std::vector<CString> row;

	for(int i=1;i<=incol_index-1;i++)
	{
		if(!m_inlst.GetItemText(0,i).IsEmpty())
			row.push_back(m_inlst.GetItemText(0,i));
		else
			row.push_back(_T("NULL"));
	}

	CString tn_str=get_tn();
	//m_tnedt.GetWindowTextW(tn_str);

	CString cmd("INSERT INTO ");
	cmd+=tn_str;
	cmd+=CString(" VALUES(");

	for(int i=0;i<row.size();i++)
	{
		cmd+=row[i];
		if(i!=row.size()-1)
			cmd+=CString(",");
		else
			cmd+=CString(")");
	}

	exec_sql(cmd);
	cmd.Empty();

	cmd=CString("SELECT * FROM ")+tn_str;
	exec_sql(cmd);

	show_res();

	m_altbtn.EnableWindow(FALSE);
	
	return;
}


void CstumanaDlg::OnEnKillfocusTnedt()
{
	// TODO: 在此添加控件通知处理程序代码
	CString tn_str=get_tn();
	//m_tnedt.GetWindowTextW(tn_str);
	CString cmd=CString("SELECT * FROM ")+tn_str;
	exec_sql(cmd);
	show_res();
}


void CstumanaDlg::OnBnClickedSelbtn()
{
	// TODO: 在此添加控件通知处理程序代码
	CString tn_str=get_tn();
	CString cmd=_T("SELECT * FROM ");
	
	//m_tnedt.GetWindowTextW(tn_str);
	cmd+=tn_str;

	/*
	int len =WideCharToMultiByte(CP_ACP,0,cmd,-1,NULL,0,NULL,NULL);  
	char *ptxtTemp=new char[len+1];
	WideCharToMultiByte(CP_ACP,0,cmd,-1,ptxtTemp,len,NULL,NULL );  
  */



	exec_sql((_bstr_t)cmd.GetString());

	//exec_sql(cmd);

	show_res();

	//delete[] ptxtTemp;  
	
}


CString CstumanaDlg::elem_to_CString(const CString& elem,int type)
{
	if(elem.IsEmpty())
		return CString("NULL");


	bool is_num=false;
	switch(type)
	{
	case adSmallInt:
		is_num=true;
		break;
	case adInteger:
		is_num=true;
		break;
	case adSingle:
		is_num=true;
		break;
	case adDouble:
		is_num=true;
		break;
	case adCurrency:
		is_num=true;
		break;
	case adError:
		is_num=true;
		break;
	case adTinyInt:
		is_num=true;
		break;
	case adDecimal:
		is_num=true;
		break;
	case adUnsignedTinyInt:
		is_num=true;
		break;
	case adUnsignedSmallInt:
		is_num=true;
		break;
	case adUnsignedInt:
		is_num=true;
		break;
	case adUnsignedBigInt:
		is_num=true;
		break;
	case adNumeric:
		is_num=true;
		break;
	case adVarNumeric:
		is_num=true;
		break;
	case adFileTime:
		is_num=true;
		break;
	case adDate:
		is_num=true;
		break;
	}

	if(is_num)
		return CString(elem);
	else
		return CString("'")+CString(elem)+CString("'");

}


void CstumanaDlg::OnBnClickedDelbtn()
{
	// TODO: 在此添加控件通知处理程序代码
	
	int nld;
	int ncols;

	POSITION pos=m_outlst.GetFirstSelectedItemPosition();

	if(pos==NULL)
		show_exception("Please select one row.");
	

	nld=(int)m_outlst.GetNextSelectedItem(pos);

	CString cmd("DELETE FROM ");
	CString tn_str=get_tn();
	//m_tnedt.GetWindowTextW(tn_str);
	cmd+=tn_str;
	cmd+=CString(" WHERE ");
	
	exec_sql(CString("SELECT * FROM ")+tn_str);

	ncols=m_pRecordset->GetFields()->GetCount();
	for(int i=0;i<ncols;i++)
	{
		CString attr_name=(LPCTSTR)(m_pRecordset->GetFields()->GetItem((long)i)->GetName());
		int type=m_pRecordset->GetFields()->GetItem((long)i)->Type;
		if(!m_outlst.GetItemText(nld,i).IsEmpty())
			cmd+=attr_name+CString("=")+elem_to_CString(m_outlst.GetItemText(nld,i),type);	
		else
			cmd+=attr_name+CString(" IS NULL");	
		if(i!=ncols-1)
			cmd+=" AND ";
	}

	exec_sql(cmd);
	exec_sql(CString("SELECT * FROM ")+tn_str);
	show_res();
}


void CstumanaDlg::set_incol(int ncols)
{
	if(ncols>incol_index-1)
		while(ncols!=incol_index-1)
			add_incol();
	else
		while(ncols!=incol_index-1)
			del_incol();
}

void CstumanaDlg::OnNMClickOutlst(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	
	int nld;
	int ncols;

	POSITION pos=m_outlst.GetFirstSelectedItemPosition();
	nld=(int)m_outlst.GetNextSelectedItem(pos);

	CString tn_str=get_tn();
	//m_tnedt.GetWindowTextW(tn_str);
	
	if(tn_str.IsEmpty())
	{
		*pResult = 0;
		return;
	}

	exec_sql(CString("SELECT * FROM ")+tn_str);

	ncols=m_pRecordset->GetFields()->GetCount();

	set_incol(ncols);
	m_inlst.DeleteAllItems();
	m_inlst.InsertItem(0,_T(""));
	m_inlst.SetItemText(0,0,_T("Values"));

	upcache_wh.Empty();
	upcache_attr.clear();

	for(int i=0;i<ncols;i++)
	{
		CString attr_name=(LPCTSTR)(m_pRecordset->GetFields()->GetItem((long)i)->GetName());
		int type=m_pRecordset->GetFields()->GetItem((long)i)->Type;
		if(!m_outlst.GetItemText(nld,i).IsEmpty())
		{
			set_incol(elem_to_CString(m_outlst.GetItemText(nld,i),type),i);
			upcache_wh+=attr_name+CString("=")+elem_to_CString(m_outlst.GetItemText(nld,i),type);
			upcache_attr.push_back(attr_name);
			if(i!=ncols-1)
				upcache_wh+=CString(" AND ");
		}
		else
		{
			upcache_wh+=attr_name+CString(" IS NULL");
			upcache_attr.push_back(attr_name);
			if(i!=ncols-1)
				upcache_wh+=CString(" AND ");
		}
	}

	m_altbtn.EnableWindow(TRUE);

	*pResult = 0;
}


void CstumanaDlg::OnBnClickedAltbtn()
{
	// TODO: 在此添加控件通知处理程序代码

	std::vector<CString> row;

	for(int i=1;i<=incol_index-1;i++)
	{
		if(!m_inlst.GetItemText(0,i).IsEmpty())
			row.push_back(m_inlst.GetItemText(0,i));
		else
			row.push_back(CString("NULL"));
	}

	CString tn_str=get_tn();
	//m_tnedt.GetWindowTextW(tn_str);

	CString cmd("UPDATE ");
	cmd+=tn_str;
	cmd+=CString(" SET ");

	for(int i=0;i<row.size();i++)
	{
		//if(row[i].IsEmpty())
			//continue;
		cmd+=upcache_attr[i]+CString("=")+row[i];
		
		if(i!=row.size()-1)
			cmd+=CString(",");
	}
	cmd+=CString(" WHERE ")+upcache_wh;

	exec_sql(cmd);
	cmd.Empty();

	cmd=CString("SELECT * FROM ")+tn_str;
	exec_sql(cmd);

	show_res();

	m_altbtn.EnableWindow(FALSE);

	return;




}


void CstumanaDlg::OnCbnDropdownTncobo()
{
	// TODO: 在此添加控件通知处理程序代码

	VARIANT var;

	m_tncobo.ResetContent();

	std::vector<CString> tn_list;
	exec_sql("SELECT * FROM TAB");
	try
	{
		while(!m_pRecordset->adoEOF)
		{
			var=m_pRecordset->GetCollect("TNAME");
			tn_list.push_back(VARIANT_to_CString(var));
			m_pRecordset->MoveNext();
		}
	}
	catch(_com_error &e)
	{
		show_exception(e.ErrorMessage());
		return;
	}

	for(int i=0;i<tn_list.size();i++)
		m_tncobo.AddString(tn_list[i]);
	

}


void CstumanaDlg::OnCbnSelchangeTncobo()
{
	// TODO: 在此添加控件通知处理程序代码

	
	CString tn_str=get_tn();
	
	CString cmd("SELECT * FROM ");
	cmd+=tn_str;
	exec_sql(cmd);

	show_res();

}
