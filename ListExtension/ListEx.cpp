#include "stdafx.h"
#include "ListEx.h"

/************************** CListUIEx Start **************************/
CListUIEx::CListUIEx()
{
}

CListUIEx::~CListUIEx()
{
}

//通过代码创建列  
BOOL CListUIEx::InsertColumn(
		int nCol,
		LPCTSTR lpszColumnHeaderStr,
		UINT uTextStyle/* = DT_LEFT*/,
		int nWidth/* = -1*/
		)
{
	CListHeaderItemUI *pHeaderItem = new CListHeaderItemUI;
	pHeaderItem->SetTextStyle(uTextStyle|DT_VCENTER|DT_SINGLELINE);
	pHeaderItem->SetText(lpszColumnHeaderStr);

	pHeaderItem->SetAttribute(_T("sepimage"), _T("Headerctrl_Sperator.bmp"));
	pHeaderItem->SetAttribute(_T("sepwidth"), _T("1"));
	pHeaderItem->SetAttribute(_T("pushedimage"), _T("headerctrl_down.bmp"));
	pHeaderItem->SetAttribute(_T("hotimage"), _T("headerctrl_hot.bmp"));
	pHeaderItem->SetAttribute(_T("normalimage"), _T("headerctrl_normal.bmp"));
	pHeaderItem->SetFixedWidth(nWidth);

	return InsertColumn(nCol, pHeaderItem);
}


BOOL CListUIEx::InsertColumn(
							 int nCol,
							 CListHeaderItemUI *pHeaderItem
							 )
{
	CListHeaderUI *pHeader = CListUI::GetHeader();
	if (pHeader == NULL)
	{
		return FALSE;
	}
	
	if (pHeader->AddAt(pHeaderItem, nCol))
	{		
		return TRUE;
	}

	delete pHeaderItem;
	pHeaderItem = NULL;
	return FALSE;
}

BOOL CListUIEx::SetHeaderItemData(int nColumn, CControlUI* pControl)
{
	CListHeaderUI *pHeader = CListUI::GetHeader();
	if (pHeader == NULL)
	{
		return FALSE;
	}
	CListHeaderItemUI *pHeaderItem = (CListHeaderItemUI *)pHeader->GetItemAt(nColumn);
	pHeaderItem->Add(pControl);
}

int CListUIEx::InsertItem(int nItem, int nHeight)
{
	CListContainerElementUI *pListItem = new CListContainerElementUI;
	pListItem->SetFixedHeight(nHeight);		//固定一个行高

	CListHeaderUI* pHeader = CListUI::GetHeader();
	if ( pHeader!=NULL ) {
		for ( int i = 0; i < pHeader->GetCount(); ++i ) {
			pListItem->Add(new CHorizontalLayoutUI);
		}
	}

	if ( CListUI::AddAt(pListItem, nItem)==false ) {
		delete pListItem;
		pListItem = NULL;
		return -1;
	}

	return nItem; 
}


int CListUIEx::InsertItem(int nItem, int nHeight, CListContainerElementUI *pListItem)
{
	pListItem->SetFixedHeight(nHeight);	
	if ( !CListUI::AddAt(pListItem, nItem) )
	{
		delete pListItem;
		pListItem = NULL;
		return -1;
	}
	
	return nItem;
}

void CListUIEx::SetItemData(int nItem,
							int nColumn,
							LPCTSTR Text, LPCTSTR Name)
{
	CLabelUI *pLabel = new CLabelUI;
	pLabel->SetText(Text);//控件属性就根据需求设置吧,我简单设置一下
	pLabel->SetTextStyle(DT_CENTER);
	pLabel->SetAttribute(_T("endellipsis"), _T("true"));
	pLabel->SetName(Name);
	SetItemData(nItem, nColumn, pLabel);//添加到父控件
}

void CListUIEx::SetItemData(int nItem, int nColumn,	CControlUI* pControl)
{
	CHorizontalLayoutUI *pSubHor = GetListSubItem(nItem, nColumn);
	pSubHor->SetAttribute(_T("inset"), _T("3,1,3,1"));
	pSubHor->Add(pControl);//添加到父控件
}

CListContainerElementUI* CListUIEx::GetListItem(int iIndex)
{
	return static_cast<CListContainerElementUI*>(CListUI::GetItemAt(iIndex));
}

CHorizontalLayoutUI* CListUIEx::GetListSubItem(int iIndex, int iSubIndex)
{
	//获取具体行控件
	CListContainerElementUI *pListItem = static_cast<CListContainerElementUI*>(CListUI::GetItemAt(iIndex));
	if (pListItem == NULL)
		return NULL;
	return static_cast<CHorizontalLayoutUI*>(pListItem->GetItemAt(iSubIndex));
}
