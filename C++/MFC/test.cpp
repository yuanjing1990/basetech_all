#define _AFXDLL
#include <afxwin.h>
class MyApp : public CWinApp
{
	public:
		virtual BOOL InitInstance();
};
class MyFrame : public CFrameWnd
{
	DECLARE_DYNAMIC(MyFrame)
	public:
		MyFrame();
	protected:
		afx_msg void OnLButtonDown(UINT nFlags,CPoint point);
		afx_msg void OnPaint();
		DECLARE_MESSAGE_MAP()
};
BOOL MyApp::InitInstance()
{
	m_pMainWnd = new MyFrame();
	m_pMainWnd->ShowWindow(m_nCmdShow);
	m_pMainWnd->UpdateWindow();
	return true;
}
IMPLEMENT_DYNAMIC(MyFrame,CFrameWnd)
BEGIN_MESSAGE_MAP(MyFrame,CFrameWnd)
	ON_WM_LBUTTONDOWN()
	ON_WM_PAINT()
END_MESSAGE_MAP()

MyFrame::MyFrame()
{
	Create(0,_T("My App"));
}
void MyFrame::OnLButtonDown(UINT nFlags,CPoint point)
{
	//GetRuntimeClass()->class_name;
	AfxMessageBox(_T("Left Button Clicked!"));
}
void MyFrame::OnPaint()
{
	CPaintDC dc(this);
	dc.TextOut(0,0,"Hello, World!");
}
MyApp g_app;
