#include <windows.h>
#include <SysMets.h>

LRESULT CALLBACK WndProc(HWND hWnd,UINT uMsg,WPARAM wParam,LPARAM lParam);
int WINAPI WinMain(HINSTANCE hInst,HINSTANCE hPrev,LPTSTR szCmdLine,int iCmdShow)
{
	static TCHAR szAppName[] = TEXT("SysMet");
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
		TEXT("SysMets"),
		WS_OVERLAPPEDWINDOW|WS_VSCROLL,
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
	TEXTMETRIC tm;
	TCHAR szBuffer[10];
	static int cxClient,cyClient,iMaxWidth;
	static int iVscrollPos,iHscrollPos;
	int i,x,y;
	static int cxChar,cxCaps,cyChar;
	static BOOL bFlag = false;
	SCROLLINFO si;
	switch(uMsg)
	{
		case WM_CREATE:
			hdc = GetDC(hWnd);
			GetTextMetrics(hdc,&tm);
			cxChar = tm.tmAveCharWidth;
			cyChar = tm.tmHeight + tm.tmExternalLeading;
			cxCaps = (tm.tmPitchAndFamily & 1 ? 3 : 2) * cxChar /2;
			ReleaseDC(hWnd,hdc);
			//SetScrollRange(hWnd,SB_VERT,0,NUMLINES - 1,FALSE);
			//SetScrollPos(hWnd,SB_VERT,iVscrollPos,TRUE);
			iMaxWidth = 40 * cxChar + 22 * cxCaps;
			return 0;
		case WM_SIZE:
			cxClient = LOWORD(lParam);
			cyClient = HIWORD(lParam);
			si.cbSize = sizeof(si);
			si.fMask = SIF_RANGE|SIF_PAGE;
			si.nMin = 0;
			si.nMax = NUMLINES - 1;
			si.nPage = cyClient/cyChar;
			SetScrollInfo(hWnd,SB_VERT,&si,TRUE);
			si.cbSize = sizeof(si);
			si.fMask = SIF_RANGE|SIF_PAGE;
			si.nMin = 0;
			si.nMax = 2 + iMaxWidth / cxChar;
			si.nPage = cxClient / cxChar;
			SetScrollInfo(hWnd,SB_HORZ,&si,TRUE);
			return 0;
		case WM_VSCROLL:
			si.cbSize = sizeof(si);
			si.fMask = SIF_ALL;
			GetScrollInfo(hWnd,SB_VERT,&si);
			iVscrollPos = si.nPos;
			switch(LOWORD(wParam))
			{
				case SB_TOP:
					si.nPos = si.nMin;
					break;
				case SB_BOTTOM:
					si.nPos = si.nMax;
					break;
				case SB_LINEUP:
					si.nPos -= 1;
					break;
				case SB_LINEDOWN:
					si.nPos += 1;
					break;
				case SB_PAGEUP:
					si.nPos -= si.nPage;
					break;
				case SB_PAGEDOWN:
					si.nPos += si.nPage;
				case SB_THUMBTRACK:
					si.nPos = si.nTrackPos;
				default:
					break;
			}
			si.fMask = SIF_POS;
			SetScrollInfo(hWnd,SB_VERT,&si,TRUE);
			GetScrollInfo(hWnd,SB_VERT,&si);
			//iVscrollPos = max(0,min(iVscrollPos,NUMLINES-1));
			//if(iVscrollPos != GetScrollPos(hWnd,SB_VERT))
			if(iVscrollPos != si.nPos)
			{
				ScrollWindow(hWnd,0,cyChar * (iVscrollPos - si.nPos),NULL,NULL);
				UpdateWindow(hWnd);
				//SetScrollPos(hWnd,SB_VERT,iVscrollPos,TRUE);
				//InvalidateRect(hWnd,NULL,TRUE);
			}
			return 0;
		case WM_KEYDOWN:
			switch(wParam)
			{
				case VK_HOME:
					SendMessage(hWnd,WM_VSCROLL,SB_TOP,0);
					break;
				case VK_END:
					SendMessage(hWnd,WM_VSCROLL,SB_BOTTOM,0);
					break;
				case VK_PRIOR:
					SendMessage(hWnd,WM_VSCROLL,SB_PAGEUP,0);
					break;
				case VK_NEXT:
					SendMessage(hWnd,WM_VSCROLL,SB_PAGEDOWN,0);
					break;
				case VK_UP:
					SendMessage(hWnd,WM_VSCROLL,SB_LINEUP,0);
					break;
				case VK_DOWN:
					SendMessage(hWnd,WM_VSCROLL,SB_LINEDOWN,0);
					break;
			}
			return 0;
		case WM_PAINT:
			hdc = BeginPaint(hWnd,&ps);
			for(i = 0;i < NUMLINES; ++i)
			{
				y = cyChar * (i - iVscrollPos);
				TextOut(hdc,0,y,sysmetrics[i].szLabel,lstrlen(sysmetrics[i].szLabel));
				TextOut(hdc,22 * cxCaps,y,sysmetrics[i].szDesc,lstrlen(sysmetrics[i].szDesc));
				SetTextAlign(hdc,TA_RIGHT|TA_TOP);
				TextOut(hdc,22 * cxCaps + 40 * cxChar,y,szBuffer,
					wsprintf(szBuffer,TEXT("%5d"),GetSystemMetrics(sysmetrics[i].Index)));
				SetTextAlign(hdc,TA_LEFT|TA_TOP);
			}
			EndPaint(hWnd,&ps);
			return 0;
		case WM_DESTROY:
			PostQuitMessage(0);
			return 0;
	}
	return DefWindowProc(hWnd,uMsg,wParam,lParam);
}