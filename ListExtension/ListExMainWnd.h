#ifndef LISTEX_MAINWND_H
#define LISTEX_MAINWND_H

class CListExMainWnd:public WindowImplBase
{
public:
	CListExMainWnd();
	virtual ~CListExMainWnd();

	virtual void OnFinalMessage(HWND hWnd);

	virtual CDuiString GetSkinFolder();
	virtual CDuiString GetSkinFile();
	virtual UILIB_RESOURCETYPE GetResourceType() const;

	virtual LPCTSTR GetWindowClassName(void) const;
	virtual UINT GetClassStyle() const;
	virtual void Notify(TNotifyUI &msg);

	virtual void InitWindow();
	
protected:

	HRESULT EnableBlurBehind(HRGN hRgn);

	static int CALLBACK ListSortItems(UINT_PTR data1, UINT_PTR data2, UINT_PTR userDef);

	DUI_DECLARE_MESSAGE_MAP()
		virtual void OnClick(TNotifyUI& msg);
		virtual void OnHeaderClick(TNotifyUI& msg);
private:
	CButtonUI *m_pMinBtn;
	CButtonUI *m_pCloseBtn;
};
#endif