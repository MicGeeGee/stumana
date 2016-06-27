#include "stdafx.h"
#include "EditTable.h"


CEditTable::CEditTable(void)
{
	m_nItem = 0;
	m_nSubItem = 0;
	m_bEditing = 0;
}


CEditTable::~CEditTable(void)
{
}

void CEditTable::OnLButtonDown(UINT nFlags, CPoint point)
{
    POSITION pos;
    BOOL bSelected = FALSE;
    // ����Ƿ���Item�����༭
    if( m_bEditing ==TRUE)
        goto default_session;
    // ����Ƿ���Item��ѡ�У�û��ʱ������༭
    pos = GetFirstSelectedItemPosition();
    if( pos )
    {
        // �õ��������Item
        LVHITTESTINFO testinfo;
        testinfo.pt.x = point.x;
        testinfo.pt.y = point.y;            //���ʱ�����λ��
        testinfo.flags = LVHT_ONITEMLABEL;    //����ı����Ǳ���
        if( SubItemHitTest(&testinfo)<0 )
            goto default_session;            //û�е�����Ч���򣬲�����༭
        m_nItem = testinfo.iItem;            //�����������к�
        m_nSubItem = testinfo.iSubItem;    //�����������к�
        //if(m_nSubItem == 0)
        //{
            //goto defalt_session;            //ѡ�е�һ�У����༭
        //}
        // ���ñ����Ƿ�ѡ�У�û��ѡ�в�����༭
        while( pos )
            if( m_nItem==GetNextSelectedItem(pos) )
            {
                bSelected = TRUE;
                break;
            }
        if( bSelected==FALSE )
            goto default_session;            //û�е�����Ч���򣬲��༭
        // ��ʼ�༭
        m_bEditing = BeginEdit();
        return;
    }
default_session:
    CListCtrl::OnLButtonDown(nFlags, point);
}


BOOL CEditTable::BeginEdit()
{
    // �õ����༭���������
    CRect rect;
    if( GetSubItemRect(m_nItem, m_nSubItem, LVIR_LABEL, rect)==FALSE )
        return FALSE;
    // �����༭�ؼ�
    int style =     WS_CHILD |
                    WS_CLIPSIBLINGS |
                    WS_EX_TOOLWINDOW |
                    WS_BORDER;
    if( m_edit.Create(style, rect, this, ID_TEMPEDIT)==FALSE )
        return FALSE;
    // ȡ���༭���������
    CString txtItem = GetItemText( m_nItem, m_nSubItem );
    // ȡ����������д���༭�ؼ�
    m_edit.SetWindowText( txtItem );
    m_edit.SetFocus();
    m_edit.SetSel( 0, -1 );
    m_edit.ShowWindow( SW_SHOW );
    return TRUE;
}

void CEditTable::EndEdit( BOOL bValidate )
{
    // �༭�������Ч�ģ����豻�༭���������
    if( bValidate )
    {
        CString txtItem;
        m_edit.GetWindowText( txtItem );
        SetItemText(m_nItem, m_nSubItem, txtItem);
    }
    // ���ٱ༭����
    m_edit.DestroyWindow();
    m_bEditing = FALSE;
}