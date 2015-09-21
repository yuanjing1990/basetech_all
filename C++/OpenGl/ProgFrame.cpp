#include "stdafx.h"
#include "OpenGl.h"
//-----全局变量定义----
HWND hWnd = NULL;
int Width = 800;
int Height = 600;
OpenGl* m_OpenGl = NULL;
HDC hdc = NULL;
//----------------------

void GameLoop()
{
	MSG msg;
	PeekMessage(&msg,NULL,NULL,NULL,PM_NOREMOVE);
	while(msg.message != WM_QUIT)
	{
		if(PeekMessage(&msg,NULL,0U,0U,PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		else
			m_OpenGl->Render();
	}
}
LRESULT WINAPI MsgProc(HWND hWnd,UINT msg,WPARAM wParam,LPARAM lParam)
{
	switch(msg)
	{
		case WM_CREATE:
			hdc = GetDC(hWnd);
			m_OpenGl->SetPixelFormat(hdc);
			return 0;
		case WM_CLOSE:
			delete m_OpenGl;
			PostQuitMessage(0);
			return 0;
		case WM_SIZE:
			Height = HIWORD(lParam);
			Width = LOWORD(lParam);
			if(Height == 0) Height = 1;
			m_OpenGl->Init(Width,Height);
			return 0;
		case WM_DESTROY:
			PostQuitMessage(0);
			return 0;
		case WM_KEYUP:
			switch(wParam)
			{
				case VK_ESCAPE:
					delete m_OpenGl;
					PostQuitMessage(0);
					return 0;
			}
		default:
			return DefWindowProc(hWnd,msg,wParam,lParam);
	}
}
INT WINAPI WinMain(HINSTANCE hInst,HINSTANCE,LPSTR,INT)
{
	bool fullScreen = TRUE;
	DWORD dwExStyle;
	DWORD dwStyle;
	RECT windowRect;
	int nX = 0,nY = 0;
	
	dwExStyle = WS_EX_APPWINDOW|WS_EX_WINDOWEDGE;
	dwStyle = WS_OVERLAPPEDWINDOW;
	int wid = GetSystemMetrics(SM_CXSCREEN);
	int hei = GetSystemMetrics(SM_CYSCREEN);
	nX = (wid - Width)/2;nY = (hei - Height)/2;
	AdjustWindowRectEx(&windowRect,dwStyle,FALSE,dwExStyle);
	
	WNDCLASSEX wc = {sizeof(WNDCLASSEX), CS_CLASSDC, MsgProc, 0L, 0L, 
                      GetModuleHandle(NULL), NULL, NULL, NULL, NULL,
                      "Test", NULL};
	RegisterClassEx(&wc);
	m_OpenGl = new OpenGl();
	hWnd = CreateWindowEx(NULL,"Test","Test",
		dwStyle|WS_CLIPCHILDREN|WS_CLIPSIBLINGS,
		nX,nY,Width,Height,
		NULL,NULL,hInst,NULL);
	ShowWindow(hWnd,SW_SHOWDEFAULT);
	UpdateWindow(hWnd);
	GameLoop();
	return 0;
}