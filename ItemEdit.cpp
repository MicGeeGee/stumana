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
	// TODO: 在此添加专用代码和/或调用基类

	 //拦截ESC键和RETURN键按下的消息，解释为WM_KILLFOCUS消息，这里也可以根据需要设置其它键作为输入结束或取消输入的标志
    if( pMsg->message==WM_KEYDOWN )
    {
        if( pMsg->wParam==13 )        //回车键
            pMsg->message = WM_KILLFOCUS;
        else if( pMsg->wParam==27 )    //ESC键
        {
            m_bInputValid = FALSE;    //此时的编辑结果无效
            pMsg->message = WM_KILLFOCUS;
        }
    }
    return CEdit::PreTranslateMessage(pMsg);
}


void CItemEdit::OnKillFocus(CWnd* pNewWnd)
{
    // 得到父窗口，并通知父窗口结束编辑过程
    CEditTable *parent = (CEditTable *)GetParent();
    if( parent )
        parent->EndEdit( m_bInputValid );
    m_bInputValid = TRUE;
    CEdit::OnKillFocus(pNewWnd);
}