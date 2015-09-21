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

void DisplayDigit(HDC hdc,int iNumber)
{
	static BOOL fSevenSegment[10][7] = {
		1,1,1,0,1,1,1,
		0,0,1,0,0,1,0,
		1,0,1,1,1,0,1,
		1,0,1,1,0,1,1,
		0,1,1,1,0,1,0,
		1,1,0,1,0,1,1,
		1,1,0,1,1,1,1,
		1,0,1,0,0,1,0,
		1,1,1,1,1,1,1,
		1,1,1,1,0,1,1
	};
	static POINT ptSegment[7][6] = {
		7,6,11,2,31,2,35,6,31,10,11,10,
		6,7,10,11,10,31,6,35,2,31,2,11,
		36,7,40,11,40,31,36,35,32,31,32,11,
		7,36,11,32,31,32,35,36,31,40,11,40,
		6,37,10,41,10,61,6,65,2,61,2,41,
		36,37,40,41,40,61,36,65,32,61,32,41,
		7,66,11,62,31,62,35,66,31,70,11,70
	};
	int iSeg;
	for(iSeg = 0; iSeg < 7; ++iSeg)
		{
			if(fSevenSegment[iNumber][iSeg])
				Polygon(hdc,ptSegment[iSeg],6);
		}
}

void DisplayTwoDigits(HDC hdc,int iNumber,BOOL fSuppress)
{
	if(!fSuppress||(iNumber / 10 != 0))
		DisplayDigit(hdc,iNumber / 10);
	OffsetWindowOrgEx(hdc,-42,0,NULL);
	DisplayDigit(hdc,iNumber % 10);
	OffsetWindowOrgEx(hdc,-42,0,NULL);
}

void DisplayColon(HDC hdc)
{
	POINT ptColon[2][4] = {
		2,21,6,17,10,21,6,25,
		2,51,6,47,10,51,6,55
	};
	Polygon(hdc,ptColon[0],4);
	Polygon(hdc,ptColon[1],4);
	OffsetWindowOrgEx(hdc,-12,0,NULL);
}

void DisplayTime(HDC hdc,BOOL f24Hour,BOOL fSuppress)
{
	SYSTEMTIME st;
	GetLocalTime(&st);
	if(f24Hour)
		DisplayTwoDigits(hdc,st.wHour,fSuppress);
	else
		DisplayTwoDigits(hdc,(st.wHour %= 12)? st.wHour : 12,fSuppress);
	DisplayColon(hdc);
	DisplayTwoDigits(hdc,st.wMinute,FALSE);
	DisplayColon(hdc);
	DisplayTwoDigits(hdc,st.wSecond,FALSE);
}

LRESULT CALLBACK WndProc(HWND hWnd,UINT uMsg,WPARAM wParam,LPARAM lParam)
{
	static BOOL f24Hour,fSuppress,fFlipFlop = FALSE;
	static int cxClient,cyClient;
	RECT rc;
	HDC hdc;
	static HBRUSH hBrush;
	PAINTSTRUCT ps;
	TCHAR szBuffer[2];
	switch(uMsg)
	{
		case WM_CREATE:
			hBrush = CreateSolidBrush(RGB(255,0,0));
			SetTimer(hWnd,ID_TIMER,1000,NULL);
		case WM_SETTINGCHANGE:
			GetLocaleInfo(LOCALE_USER_DEFAULT,LOCALE_ITIME,szBuffer,2);
			f24Hour = (szBuffer[0] == '1');
			GetLocaleInfo(LOCALE_USER_DEFAULT,LOCALE_ITLZERO,szBuffer,2);
			fSuppress = (szBuffer[0] == '0');
			InvalidateRect(hWnd,NULL,TRUE);
			return 0;
		case WM_SIZE:
			cxClient = LOWORD(lParam);
			cyClient = HIWORD(wParam);
			return 0;
		case WM_PAINT:
			hdc = BeginPaint(hWnd,&ps);
			
			SetMapMode(hdc,MM_ISOTROPIC);
			SetWindowExtEx(hdc,276,72,NULL);
			SetViewportExtEx(hdc,cxClient,cyClient,NULL);
			
			//SetWindowOrgEx(hdc,138,72,NULL);
			//SetViewportOrgEx(hdc,cxClient/2,cyClient/2,NULL);
			SelectObject(hdc,GetStockObject(NULL_PEN));
			SelectObject(hdc,hBrush);
			
			DisplayTime(hdc,f24Hour,fSuppress);
			
			EndPaint(hWnd,&ps);
			break;
		case WM_TIMER:
			InvalidateRect(hWnd,NULL,TRUE);
			return 0;
		case WM_DESTROY:
			KillTimer(hWnd,ID_TIMER);
			DeleteObject(hBrush);
			PostQuitMessage(0);
			return 0;
	}
	return DefWindowProc(hWnd,uMsg,wParam,lParam);
}

void CALLBACK TimerProc(HWND hWnd,UINT nMsg,UINT iTimerID,DWORD dwTime)
{

}