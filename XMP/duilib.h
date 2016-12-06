// ------------------------------------------------------------------------------------------------------------------------------------------------------------------------
// Build:   Oct/21/2013
// Author:  Alberl Lee
// Email:   ItsBird@qq.com
// Website: http://www.cnblogs.com/Alberl/p/3381820.html
//
// 温馨提示：
// 此邮箱每天都收到很多垃圾邮件，邮件名请不要随意乱取，应尽量与垃圾邮件区分开来，幸好QQ的过滤功能还算强大~O(∩_∩)O~
// 此邮箱仅供【错误指正和技术交流】，若是技术问题请直接在文章评论区提问，否则恕不回复，这样做是为了让后面的小伙伴也能看到解决方案~O(∩_∩)O~
//
// 使用协议：WTFPL
// 鉴于在天朝神马协议都被无视，甚至很多大公司都不遵守，故索性采用了【DO WHAT THE FUCK YOU WANT TO PUBLIC LICENSE】协议~O(∩_∩)O~
//
// 代码安全性：
// 此项目为示例项目，为了方便大家编译，没用三方库，因此写了一些简单的函数，很多逻辑判断也只是保证正常操作，实际使用请自行保证代码安全~O(∩_∩)O~
// ------------------------------------------------------------------------------------------------------------------------------------------------------------------------


#pragma once
#include "../duilib/UIlib.h"
using namespace DuiLib;

#ifdef _DEBUG
#   ifdef _UNICODE
#       pragma comment(lib, "..\\Lib\\DuiLib_ud.lib")
#   else
#       pragma comment(lib, "..\\Lib\\DuiLib_d.lib")
#   endif
#else
#   ifdef _UNICODE
#       pragma comment(lib, "..\\Lib\\DuiLib_u.lib")
#   else
#       pragma comment(lib, "..\\Lib\\DuiLib.lib")
#   endif
#endif

// 以XML生成界面的窗口基类
class CXMLWnd : public WindowImplBase
{
public:
    explicit CXMLWnd(LPCTSTR pszXMLName) 
        : m_strXMLName(pszXMLName){}

public:
    virtual LPCTSTR GetWindowClassName() const
    {
        return _T("XMLWnd");
    }

    virtual CDuiString GetSkinFile()
    {
        return m_strXMLName;
    }

    virtual CDuiString GetSkinFolder()
    {
        return _T("");
    }

protected:
    CDuiString m_strXMLName;    // XML的名字
};


// 将HWND显示到CControlUI上面
class CWndUI: public CControlUI
{
public:
    CWndUI(): m_hWnd(NULL){}

    virtual void SetVisible(bool bVisible = true)
    {
        __super::SetVisible(bVisible);
        ::ShowWindow(m_hWnd, bVisible);
    }

    virtual void SetInternVisible(bool bVisible = true)
    {
        __super::SetInternVisible(bVisible);
        ::ShowWindow(m_hWnd, bVisible);
    }

    virtual void SetPos(RECT rc)
    {
        __super::SetPos(rc);
        ::SetWindowPos(m_hWnd, NULL, rc.left, rc.top, rc.right - rc.left, rc.bottom - rc.top, SWP_NOZORDER | SWP_NOACTIVATE);
    }

    BOOL Attach(HWND hWndNew)
    {
        if (! ::IsWindow(hWndNew))
        {
            return FALSE;
        }

        m_hWnd = hWndNew;
        return TRUE;
    }

    HWND Detach()
    {
        HWND hWnd = m_hWnd;
        m_hWnd = NULL;
        return hWnd;
    }

    HWND GetHWND()
    {
        return m_hWnd;
    }

protected:
    HWND m_hWnd;
};
