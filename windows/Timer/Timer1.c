#include <windows.h>
#define ID_TIMER 1
	
LRESULT CALLBACK WndProc(HWND hWnd,UINT uMsg,WPARAM wParam,LPARAM lParam);
void CALLBACK TimerProc(HWND hWnd,UINT uMsg,UINT iTimerID,DWORD dwTime);

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
	switch(uMsg)
	{
		case WM_CREATE:
			SetTimer(hWnd,ID_TIMER,1000,TimerProc);
			break;
		case WM_DESTROY:
			KillTimer(hWnd,ID_TIMER);
			PostQuitMessage(0);
			return 0;
	}
	return DefWindowProc(hWnd,uMsg,wParam,lParam);
}

void CALLBACK TimerProc(HWND hWnd,UINT nMsg,UINT iTimerID,DWORD dwTime)
{
	static BOOL fFlipFlop = FALSE;
	RECT rc;
	HDC hdc;
	HBRUSH hBrush;
	MessageBeep(-1);
	fFlipFlop = !fFlipFlop;
	GetClientRect(hWnd,&rc);
	
	hdc = GetDC(hWnd);
	hBrush = CreateSolidBrush(fFlipFlop ? RGB(255,0,0) : RGB(0,0,255));
	FillRect(hdc,&rc,hBrush);
	ReleaseDC(hWnd,hdc);
	DeleteObject(hBrush);
}