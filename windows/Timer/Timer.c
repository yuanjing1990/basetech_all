#include <windows.h>
#define ID_TIMER 1
	
LRESULT CALLBACK WndProc(HWND hWnd,UINT uMsg,WPARAM wParam,LPARAM lParam);

int WINAPI WinMain(HINSTANCE hInst,HINSTANCE hPrev,LPTSTR lpCmdLine,int iCmdShow)
{
	static LPCTSTR szAppName = TEXT("Timer");
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
		MessageBox(NULL,TEXT("Requires Window NT!"),szAppName,MB_OK);
		return 0;
	}
	HWND hWnd;
	hWnd = CreateWindow(szAppName,
		TEXT("Beeper1 Timer Demo"),
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		NULL,
		NULL,
		hInst,NULL);
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
	static BOOL fFlipFlop = FALSE;
	HBRUSH hBrush;
	HDC hdc;
	PAINTSTRUCT ps;
	RECT rc;
	switch(uMsg)
	{
		case WM_CREATE:
			SetTimer(hWnd,ID_TIMER,1000,NULL);
			break;
		case WM_PAINT:
			hdc = BeginPaint(hWnd,&ps);
			GetClientRect(hWnd,&rc);
			hBrush = CreateSolidBrush(fFlipFlop ? RGB(255,0,0) : RGB(0,0,255));
			FillRect(hdc,&rc,hBrush);
			EndPaint(hWnd,&ps);
			DeleteObject(hBrush);
			break;
		case WM_TIMER:
			MessageBeep(-1);
			fFlipFlop = !fFlipFlop;
			InvalidateRect(hWnd,NULL,FALSE);
			break;
		case WM_DESTROY:
			KillTimer(hWnd,ID_TIMER);
			PostQuitMessage(0);
			return 0;
	}
	return DefWindowProc(hWnd,uMsg,wParam,lParam);
}