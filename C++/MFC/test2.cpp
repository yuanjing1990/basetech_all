//±‡“Î£∫cl /c /EHsc test2.cpp
//¡¨Ω”£∫link /SUBSYSTEM:WINDOWS test2.obj
#include <afxwin.h>
class MyApp : public CWinApp
{
	public:
		virtual BOOL InitInstance();
};
class MyFrame : public CFrameWnd
{
	public:
		MyFrame();
};
MyFrame::MyFrame()
{
	Create(0,_T("My App"));
}
BOOL MyApp::InitInstance()
{
	m_pMainWnd = new MyFrame();
	m_pMainWnd->ShowWindow(m_nCmdShow);
	m_pMainWnd->UpdateWindow();
	return true;
}
MyApp g_app;