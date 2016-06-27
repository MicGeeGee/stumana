#include "stdafx.h"
#include "ItemEdit.h"
#include "EditTable.h"


CItemEdit::CItemEdit(void)
{
	m_bInputValid = 0;
}


CItemEdit::~CItemEdit(void)
{
}


BOOL CItemEdit::PreTranslateMessage(MSG* pMsg)
{
	// TODO: �ڴ����ר�ô����/����û���

	 //����ESC����RETURN�����µ���Ϣ������ΪWM_KILLFOCUS��Ϣ������Ҳ���Ը�����Ҫ������������Ϊ���������ȡ������ı�־
    if( pMsg->message==WM_KEYDOWN )
    {
        if( pMsg->wParam==13 )        //�س���
            pMsg->message = WM_KILLFOCUS;
        else if( pMsg->wParam==27 )    //ESC��
        {
            m_bInputValid = FALSE;    //��ʱ�ı༭�����Ч
            pMsg->message = WM_KILLFOCUS;
        }
    }
    return CEdit::PreTranslateMessage(pMsg);
}


void CItemEdit::OnKillFocus(CWnd* pNewWnd)
{
    // �õ������ڣ���֪ͨ�����ڽ����༭����
    CEditTable *parent = (CEditTable *)GetParent();
    if( parent )
        parent->EndEdit( m_bInputValid );
    m_bInputValid = TRUE;
    CEdit::OnKillFocus(pNewWnd);
}