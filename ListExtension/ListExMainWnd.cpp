#include "stdafx.h"
#include "ListExMainWnd.h"

CDuiString sSortRow = _T("other");

BOOL IsNumber(LPCTSTR  pszText,int length) 
{ 
	if (pszText == NULL || length < 0)
		return FALSE;

	for(int i = 0;i < length;i++) 
		if(! isdigit(pszText[i])) 
			return  FALSE; 
	return TRUE; 
}

int CALLBACK SortCompare(LPCTSTR data1,LPCTSTR data2) 
{ 
	CDuiString strItem1 = (LPCTSTR)data1;
	CDuiString strItem2 = (LPCTSTR)data2;

	//判断为数字
	if (IsNumber(strItem1, strItem1.GetLength()))
	{
		int number1 = _tcstol(strItem1,NULL,10);
		int number2 = _tcstol(strItem2,NULL,10);

		if (number1 == number2)
			return 0;
		else if (number1 > number2)
			return 1;
		else
			return -1;
	}
	//当s1<s2时，返回值<0 　　当s1=s2时，返回值=0 　　当s1>s2时，返回值>0 
	return _tcscmp(strItem2,strItem1); 
}

DUI_BEGIN_MESSAGE_MAP(CListExMainWnd, WindowImplBase)
	DUI_ON_MSGTYPE(DUI_MSGTYPE_CLICK, OnClick)
	DUI_ON_MSGTYPE(DUI_MSGTYPE_HEADERCLICK, OnHeaderClick)
DUI_END_MESSAGE_MAP()

CListExMainWnd::CListExMainWnd()
{
}

CListExMainWnd::~CListExMainWnd()
{
}

void CListExMainWnd::OnFinalMessage(HWND hWnd)
{
	WindowImplBase::OnFinalMessage(hWnd);
	delete this;
}

CDuiString CListExMainWnd::GetSkinFolder()
{
	return _T("skin\\ListExtension\\");
}

CDuiString CListExMainWnd::GetSkinFile()
{
	return _T("main.xml");
}

UILIB_RESOURCETYPE CListExMainWnd::GetResourceType() const
{
	return UILIB_FILE;
}

LPCTSTR CListExMainWnd::GetWindowClassName(void) const
{
	return _T("ListExWnd");
}

UINT CListExMainWnd::GetClassStyle() const
{
	return UI_CLASSSTYLE_DIALOG;
}

void CListExMainWnd::Notify(TNotifyUI &msg)
{
	if (_tcsicmp(msg.sType, _T("itemactivate")) == 0 )
	{
		::MessageBox(m_hWnd, _T("aaa"), _T(""), 0);
	}
	return WindowImplBase::Notify(msg);
}

void CListExMainWnd::OnClick( TNotifyUI &msg )
{
	if( msg.pSender == m_pCloseBtn) 
	{ 
		PostQuitMessage(0); // 因为activex的原因，使用close可能会出现错误
		return; 
	}
	else if(msg.pSender == m_pMinBtn) 
	{ 
		SendMessage(WM_SYSCOMMAND, SC_MINIMIZE, 0); 
		return; 
	}
	else if (msg.pSender->GetName() == _T("phonenbr"))
	{
		::MessageBox(NULL, _T("aaa"), _T(""), 0);
	}
	else if (msg.pSender->GetName() == _T("phoneclass"))
	{
		::MessageBox(NULL, _T("bbbb"), _T(""), 0);
	}
	else if (msg.pSender->GetName() == _T("additem"))
	{
		CDialogBuilder builder;
		CListContainerElementUI* pLine = (CListContainerElementUI*)(builder.Create(_T("sigle_list_item_column.xml"),(UINT)0));
		if( pLine != NULL ) 
		{
			CListUI *pList = static_cast<CListUI*>(m_PaintManager.FindControl(_T("listex")));
			pList->InsertItem(pList->GetCount(), 60, pLine);
		}
	}
	else if (msg.pSender->GetName() == _T("additembycode"))
	{
		CListUI *pList = static_cast<CListUI*>(m_PaintManager.FindControl(_T("listex")));
		int nIndex = pList->GetCount();
		pList->InsertItem(nIndex, 60);

		CEditUI *pControl = new CEditUI; 
		pControl->SetFloat(true);
		pControl->SetFixedHeight(20);
		pControl->SetText(_T(""));
		pControl->SetName(_T("edit"));
		pControl->SetBorderColor(RGB(255, 0, 0));
		pControl->SetAttribute(_T("bordersize"), _T("1"));
		pControl->SetAttribute(_T("bordercolor"), _T("#FF4775CC"));
		pControl->SetFixedXY(CSize(0, 15));
		pList->SetSubItem(nIndex, 0, pControl);

		CButtonUI *pBtnUI = new CButtonUI;
		pBtnUI->SetFloat(true);
		pBtnUI->SetText(_T("添加"));
		pControl->SetFixedHeight(20);
		pBtnUI->SetFixedWidth(60);
		pControl->SetFixedXY(CSize(0, 15));
		pBtnUI->SetAttribute(_T("pushedimage"), _T("button_down.bmp"));
		pBtnUI->SetAttribute(_T("hotimage"), _T("button_over.bmp"));
		pBtnUI->SetAttribute(_T("normalimage"), _T("button_nor.bmp"));		
		pList->SetSubItem(nIndex, 1, pBtnUI);

		pList->SetSubItem(nIndex, 2, _T("这是一行动态添加的数据"), _T("testid"));
		if (pList->GetHeader()->GetCount() > 3)
		{
			pList->SetSubItem(nIndex, 3, _T("新增列数据"), _T("testid1"));
		}

	}
	else if (msg.pSender->GetName() == _T("addcolumn"))
	{
		CListUI *pList = static_cast<CListUI*>(m_PaintManager.FindControl(_T("listex")));

		//pList->InsertColumn(3, "新增列   ", DT_RIGHT, 150);

		CListHeaderItemUI *pHeaderItem = new CListHeaderItemUI;
		pHeaderItem->SetTextStyle(DT_RIGHT|DT_VCENTER|DT_SINGLELINE);
		pHeaderItem->SetText(_T("新增列   "));
		pHeaderItem->SetAttribute(_T("sepimage"), _T("Headerctrl_Sperator.bmp"));
		pHeaderItem->SetAttribute(_T("sepwidth"), _T("1"));
		pHeaderItem->SetAttribute(_T("pushedimage"), _T("headerctrl_down.bmp"));
		pHeaderItem->SetAttribute(_T("hotimage"), _T("headerctrl_hot.bmp"));
		pHeaderItem->SetAttribute(_T("normalimage"), _T("headerctrl_normal.bmp"));
		pHeaderItem->SetFixedWidth(150);
		pList->InsertColumn(3, pHeaderItem);

		CCheckBoxUI *pBtnUI = new CCheckBoxUI;
		pBtnUI->SetText(_T("选择"));
		pBtnUI->SetAttribute(_T("selectedimage"), _T("file='checkbox_p.png' dest='0,2,15,17'"));
		pBtnUI->SetAttribute(_T("normalimage"), _T("file='checkbox_h.png' dest='0,2,15,17'"));
		pBtnUI->SetAttribute(_T("textpadding"), _T("20,3,0,0"));
		pBtnUI->SetAttribute(_T("align"), _T("right"));
		pBtnUI->SetFloat(true);
		pBtnUI->SetAttribute(_T("pos"), _T("20,3, 65, 20"));

		pList->SetHeaderItemData(3, pBtnUI);
	}

}

void CListExMainWnd::OnHeaderClick(TNotifyUI& msg)
{
	CDuiString sName = msg.pSender->GetName();
	CListUI *pList = static_cast<CListUI*>(m_PaintManager.FindControl(_T("listex")));

	sSortRow = sName;
	//pList->SortItems(ListSortItems, NULL);
}


void CListExMainWnd::InitWindow()
{
	m_pCloseBtn = static_cast<CButtonUI*>(m_PaintManager.FindControl(_T("closebtn")));
	m_pMinBtn = static_cast<CButtonUI*>(m_PaintManager.FindControl(_T("minbtn")));

	CListUI *pList = static_cast<CListUI*>(m_PaintManager.FindControl(_T("listex")));
	CDialogBuilder builder;
	CListContainerElementUI* pLine = (CListContainerElementUI*)(builder.Create(_T("sigle_list_item_column.xml"),(UINT)0, this));
	if( pLine != NULL ) 
	{
		pList->InsertItem(0, 60, pLine);
	}
	RECT rect;
	GetWindowRect(m_hWnd, &rect);

	HRGN hRgn = CreateRectRgn(rect.left, rect.top, rect.right,rect.bottom);
	EnableBlurBehind(hRgn);
	DeleteObject(hRgn);
}

HRESULT CListExMainWnd::EnableBlurBehind(HRGN hRgn )
{
	// 	DWM_BLURBEHIND bb = {0};
	// 	bb.dwFlags = DWM_BB_ENABLE | DWM_BB_BLURREGION;
	// 	bb.fEnable = true;
	// 	bb.hRgnBlur = hRgn;
	// 
	// 	return DwmEnableBlurBehindWindow(m_hWnd, &bb);
	return 0;
}

int CALLBACK CListExMainWnd::ListSortItems(UINT_PTR data1, UINT_PTR data2, UINT_PTR userDef)
{
	// 	CDuiString szSource;
	// 	CDuiString szTemp;
	// 	CLabelUI *pLabelUI ,*pNextLabelUI;
	// 
	// 	CListContainerElementUIEx *pListContainerElementUI = (CListContainerElementUIEx*)data1;
	// 	if (pListContainerElementUI == NULL)
	// 		return TRUE;
	// 
	// 	CListContainerElementUIEx *pNextListContainerElementUI = (CListContainerElementUIEx*)data2;
	// 	if (pNextListContainerElementUI == NULL)
	// 		return TRUE;
	// 
	// 	pLabelUI = (CLabelUI *)pListContainerElementUI->FindSubControl(sSortRow);
	// 	pNextLabelUI = (CLabelUI *)pNextListContainerElementUI->FindSubControl(sSortRow);
	// 	
	// 	szSource = pLabelUI->GetText();
	// 	szTemp = pNextLabelUI->GetText();
	// 	
	// 	return SortCompare(szSource,szTemp);
	return 0;
}