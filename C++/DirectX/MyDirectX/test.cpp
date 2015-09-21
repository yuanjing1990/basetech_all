#include "DirectX9.h"
static const char* lpNameStr = "Test";
DirectX9 g_dx9;
DXElem* g_dxElem = NULL;
LRESULT CALLBACK MsgProc(HWND hWnd,UINT msg,WPARAM wParam,LPARAM lParam);
int WINAPI WinMain(HINSTANCE hInst,HINSTANCE ,LPSTR cmdLine,int cmdShow)
{
	WNDCLASS wc = {
		CS_HREDRAW|CS_VREDRAW,MsgProc,0,0,hInst,NULL,NULL,NULL,NULL,lpNameStr
	};
	if(0 == RegisterClass(&wc))
	{
		MessageBox(NULL,"Error","Error",MB_OK);
		return -1;
	}
	
	HWND hWnd = CreateWindow(lpNameStr,lpNameStr,WS_OVERLAPPEDWINDOW,
		500,500,100,100,NULL,NULL,
		hInst,NULL);
	if(hWnd == NULL)
	{
		MessageBox(NULL,"Error","Error",MB_OK);
		return -1;
	}
	g_dx9.Init(hWnd);
	g_dxElem = new DXBall();
	g_dx9.SetElem(g_dxElem);
	ShowWindow(hWnd,SW_SHOWNORMAL);
	UpdateWindow(hWnd);
	
	MSG msg;
	while(GetMessage(&msg,NULL,NULL,NULL))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	g_dx9.ClearUp();
	delete g_dxElem;
	return 0;
}

LRESULT CALLBACK MsgProc(HWND hWnd,UINT msg,WPARAM wParam,LPARAM lParam)
{
	switch(msg)
	{
	case WM_CREATE:
		return 0;
	case WM_PAINT:
		g_dx9.Render();
		return 0;
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	default:
		break;
	}
	return DefWindowProc(hWnd,msg,wParam,lParam);
}