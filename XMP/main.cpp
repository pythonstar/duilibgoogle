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


#include "DuiFrameWnd.h"
#include "KDetectMemoryLeak.h"

int APIENTRY _tWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPTSTR lpCmdLine, int nCmdShow)
{
    atexit(CheckOnExit);
    ::CoInitialize(NULL);
    CPaintManagerUI::SetInstance(hInstance);
    CPaintManagerUI::SetResourcePath(CPaintManagerUI::GetInstancePath() + _T("skin\\XMP"));

    CDuiFrameWnd *pFrame = new CDuiFrameWnd(_T("XMP.xml"));
    pFrame->Create(NULL, _T("迅雷看看播放器"), UI_WNDSTYLE_FRAME, WS_EX_WINDOWEDGE | WS_EX_ACCEPTFILES);
    pFrame->ShowModal();

    delete pFrame;
    ::CoUninitialize();
    return 0;
}
