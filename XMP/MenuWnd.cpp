#include "MenuWnd.h"

CMenuWnd::CMenuWnd( LPCTSTR pszXMLName ) 
: CXMLWnd(pszXMLName),
m_pOwnerPM(NULL)
{

}

CMenuWnd::~CMenuWnd()
{

}

void CMenuWnd::Init(CPaintManagerUI *pOwnerPM, POINT ptPos)
{
    if( pOwnerPM == NULL ) 
    {
        return;
    }

    m_pOwnerPM = pOwnerPM;
    Create(pOwnerPM->GetPaintWindow(), _T("MenuWnd"), UI_WNDSTYLE_FRAME, WS_EX_WINDOWEDGE);
    ::ClientToScreen(pOwnerPM->GetPaintWindow(), &ptPos);
    ::SetWindowPos(*this, NULL, ptPos.x, ptPos.y, 0, 0, SWP_NOZORDER | SWP_NOSIZE | SWP_NOACTIVATE);
}

void CMenuWnd::OnFinalMessage( HWND /*hWnd*/ )
{
    delete this;
}

LRESULT CMenuWnd::HandleMessage( UINT uMsg, WPARAM wParam, LPARAM lParam )
{
    LRESULT lRes = 0;
    BOOL bHandled = TRUE;

    switch( uMsg )
    {
    case WM_KILLFOCUS:    
        lRes = OnKillFocus(uMsg, wParam, lParam, bHandled); 
        break; 

    default:
        bHandled = FALSE;
    }

    if(bHandled || m_PaintManager.MessageHandler(uMsg, wParam, lParam, lRes)) 
    {
        return lRes;
    }

    return __super::HandleMessage(uMsg, wParam, lParam);
}

LRESULT CMenuWnd::OnKillFocus( UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled )
{
    Close();
    bHandled = FALSE;
    return __super::OnKillFocus(uMsg, wParam, lParam, bHandled); 
}

void CMenuWnd::Notify( TNotifyUI& msg )
{
    if(msg.sType == DUI_MSGTYPE_ITEMCLICK)
    {
        if(m_pOwnerPM)
        {
            m_pOwnerPM->SendNotify(msg);
        }

        Close();
    }
    
    __super::Notify(msg); 
}
