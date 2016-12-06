#include "stdafx.h"
#include "ListExMainWnd.h"

int WINAPI WinMain(HINSTANCE hInstance,
					 HINSTANCE hPrevInstance,
					 LPSTR lpCmdLine,
					 int iCmdShow)
{
	CPaintManagerUI::SetInstance(hInstance);

	HRESULT Hr = ::CoInitialize(NULL);
	if( FAILED(Hr) ) return 0;

	CListExMainWnd* pFrame = new CListExMainWnd();
	if( pFrame == NULL ) return 0;
	pFrame->Create(NULL, _T("ListExDemo"), UI_WNDSTYLE_DIALOG, 0L);
	pFrame->CenterWindow();
	pFrame->ShowWindow(true);

	CPaintManagerUI::MessageLoop();

	::CoUninitialize();
	return 0;
}