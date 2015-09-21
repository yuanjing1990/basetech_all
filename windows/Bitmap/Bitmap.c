#include "resource.h"
#include <windows.h>

#include <stdio.h>
#include <string.h>
LRESULT CALLBACK WndProc(HWND hWnd,UINT uMsg,WPARAM wParam,LPARAM lParam);

int WINAPI WinMain(HINSTANCE hInst,HINSTANCE hPrev,LPTSTR lpCmdLine,int iCmdShow)
{
	static LPTSTR szAppName = TEXT("Bitmap");
	WNDCLASS wc;
	wc.style = CS_HREDRAW|CS_HREDRAW;
	wc.lpfnWndProc = WndProc;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hInstance = hInst;
	wc.hIcon = LoadIcon(NULL,IDI_INFORMATION);
	wc.hCursor = LoadCursor(NULL,IDC_ARROW);
	wc.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	wc.lpszMenuName = NULL;
	wc.lpszClassName = szAppName;
	if(!RegisterClass(&wc))
	{
		MessageBox(NULL,TEXT("Required Windows NT!"),szAppName,MB_ICONERROR);
		return 0;
	}
	HWND hWnd = CreateWindow(szAppName,TEXT("Bitbtl Demo"),
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		NULL,
		NULL,
		hInst,
		NULL);
	ShowWindow(hWnd,iCmdShow);
	UpdateWindow(hWnd);
	MSG msg;
	while(GetMessage(&msg,NULL,0,0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	return msg.wParam;
}

LRESULT CALLBACK WndProc(HWND hWnd,UINT uMsg,WPARAM wParam,LPARAM lParam)
{
	HDC hdc,hdcWnd;
	PAINTSTRUCT ps;
	static int cxClient,cyClient;
	static HBITMAP hBitmap;
	static int cxSource,cySource; 
	HINSTANCE hInstance;
	BITMAP bitmap;
	HDC hMemDc;
	switch(uMsg)
	{
		case WM_CREATE:
			hInstance = ((LPCREATESTRUCT)lParam)->hInstance;
			hBitmap = LoadBitmap(hInstance,MAKEINTRESOURCE(103));
			if(hBitmap == NULL)
			{
				int error = GetLastError();
				TCHAR buffer[64] = {0};
				sprintf(buffer,"%d",error);
				MessageBox(NULL,buffer,TEXT("Failed!"),MB_OK);
			}
			GetObject(hBitmap,sizeof(BITMAP),&bitmap);
			cxSource = bitmap.bmWidth;
			cySource = bitmap.bmHeight;
			return 0;
		case WM_SIZE:
			cxClient = LOWORD(lParam);
			cyClient = HIWORD(lParam);
			return 0;
		case WM_PAINT:
			hdc = BeginPaint(hWnd,&ps);
//			hdcWnd = GetWindowDC(hWnd);
//			BitBlt(hdc,
//				0,0,
//				GetSystemMetrics(SM_CXSIZE),
//				GetSystemMetrics(SM_CYCAPTION),
//				hdcWnd,
//				GetSystemMetrics(SM_CXSIZEFRAME),
//				GetSystemMetrics(SM_CYSIZEFRAME),
//				SRCCOPY);
//			ReleaseDC(hWnd,hdcWnd);
			hMemDc = CreateCompatibleDC(hdc);
			SelectObject(hMemDc,hBitmap);
			BitBlt(hdc,0,0,cxSource,cySource,hMemDc,0,0,SRCCOPY);
			DeleteDC(hMemDc);
			EndPaint(hWnd,&ps);
			return 0;
		case WM_DESTROY:
			PostQuitMessage(0);
			return 0;
	}
	return DefWindowProc(hWnd,uMsg,wParam,lParam);
}