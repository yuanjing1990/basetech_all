#include <windows.h>

LRESULT CALLBACK WndProc(HWND hWnd,UINT uMsg,WPARAM wParam,LPARAM lParam);
int WINAPI WinMain(HINSTANCE hInst,HINSTANCE hPrev,LPTSTR szCmdLine,int iCmdShow)
{
	static TCHAR szAppName[] = TEXT("HelloWin");
	WNDCLASS wc;
	wc.style = CS_HREDRAW|CS_VREDRAW;
	wc.lpfnWndProc = WndProc;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hInstance = hInst;
	wc.hIcon = LoadIcon(NULL,IDI_APPLICATION);
	wc.hCursor = LoadCursor(NULL,IDC_ARROW);
	wc.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	wc.lpszMenuName = NULL;
	wc.lpszClassName = szAppName;
	
	if(!RegisterClass(&wc))
	{	
		MessageBox(NULL,TEXT("This Program requires Windows NT!"),szAppName,MB_ICONERROR);
		return 0;
	}
	
	HWND hWnd;
	hWnd = CreateWindow(
		szAppName,
		TEXT("This Hello Program"),
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
	return 0;
}

LRESULT CALLBACK WndProc(HWND hWnd,UINT uMsg,WPARAM wParam,LPARAM lParam)
{
	HDC hdc;
	PAINTSTRUCT ps;
	RECT rect;
	static BOOL bFlag = false;
	switch(uMsg)
	{
		case WM_CREATE:
			PlaySound(TEXT("hellowin.wav"),NULL,SND_FILENAME|SND_ASYNC);
			return 0;
		case WM_PAINT:
			hdc = BeginPaint(hWnd,&ps);
			GetClientRect(hWnd,&rect);
			DrawText(hdc,TEXT("Hello,Window XP!"),-1,&rect,
				DT_SINGLELINE|DT_CENTER|DT_VCENTER);
			EndPaint(hWnd,&ps);
			return 0;
		case WM_DESTROY:
			PostQuitMessage(0);
			return 0;
	}
	return DefWindowProc(hWnd,uMsg,wParam,lParam);
}