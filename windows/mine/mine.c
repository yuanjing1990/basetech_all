#include <windows.h>

#define DIM 5

static const TCHAR childClass[] = TEXT("ChildClass");
HWND g_block[DIM][DIM];

LRESULT CALLBACK WndProc(HWND hWnd,UINT uMsg,WPARAM wParam,LPARAM lParam);
LRESULT CALLBACK ChildProc(HWND hWnd,UINT uMsg,WPARAM wParam,LPARAM lParam);

int WINAPI WinMain(HINSTANCE hInst,HINSTANCE hPrev,LPTSTR lpCmdLine,int iCmdShow)
{
	static LPTSTR szAppName = TEXT("Mine");
	WNDCLASS wc;
	wc.style = CS_HREDRAW|CS_VREDRAW;
	wc.lpfnWndProc = WndProc;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hInstance = hInst;
	wc.hIcon = LoadIcon(NULL,IDI_APPLICATION);
	wc.hCursor = LoadCursor(NULL,IDC_ARROW);
	wc.hbrBackground = (HBRUSH)GetStockObject(COLOR_BTNFACE);
	wc.lpszMenuName = szAppName;
	wc.lpszClassName = szAppName;
	if(!RegisterClass(&wc))
	{
		MessageBox(NULL,TEXT("Required Windows NT!"),szAppName,MB_OK);
		return 0;
	}
	wc.cbWndExtra = sizeof(long);
	wc.lpfnWndProc = ChildProc;
	wc.lpszClassName = childClass;
	wc.hIcon = NULL;
	wc.hbrBackground = (HBRUSH)(COLOR_BTNFACE);
	RegisterClass(&wc);
	HWND hWnd = CreateWindow(szAppName,
		szAppName,
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		NULL,NULL,hInst,NULL);
	
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
	HDC hdc;
	PAINTSTRUCT ps;
	RECT rc;
	int i,j;
	int cxBlock,cyBlock;
	switch(uMsg)
	{
		case WM_CREATE:
			for(i = 0; i < DIM; ++i)
				for(j = 0; j < DIM; ++j)
					g_block[i][j] = CreateWindow(childClass,
						NULL,
						WS_CHILDWINDOW|WS_VISIBLE,
						0,0,0,0,
						hWnd,
						(HMENU)(j<<8|i),
						(HINSTANCE)GetWindowLong(hWnd,GWL_HINSTANCE),
						NULL);
			return 0;
		case WM_SIZE:
			cxBlock = LOWORD(lParam)/DIM;
			cyBlock = HIWORD(lParam)/DIM;
			for(i = 0; i < DIM; ++i)
				for(j = 0; j < DIM; ++j)
					MoveWindow(g_block[i][j],j*cxBlock,i*cyBlock,cxBlock,cyBlock,TRUE);
		case WM_PAINT:
			hdc = BeginPaint(hWnd,&ps);
			EndPaint(hWnd,&ps);
			return 0;
		case WM_DESTROY:
			PostQuitMessage(0);
			return 0;
		default:
			break;
	}
	return DefWindowProc(hWnd,uMsg,wParam,lParam);
}

LRESULT CALLBACK ChildProc(HWND hWnd,UINT uMsg,WPARAM wParam,LPARAM lParam)
{
	HDC hdc;
	PAINTSTRUCT ps;
	RECT rc;
	switch(uMsg)
	{
		case WM_CREATE:
			SetWindowLong(hWnd,0,0);
			return 0;
		case WM_LBUTTONDOWN:
			SetWindowLong(hWnd,0,1^GetWindowLong(hWnd,0));
			InvalidateRect(hWnd,NULL,FALSE);
			return 0;
		case WM_PAINT:
			hdc = BeginPaint(hWnd,&ps);
			GetClientRect(hWnd,&rc);
			Rectangle(hdc,0,0,rc.right,rc.bottom);
			if(GetWindowLong(hWnd,0))
			{
				SetWindowText(hWnd,TEXT("Test"));
				MoveToEx(hdc,0,0,NULL);
				LineTo(hdc,rc.right,rc.bottom);
				MoveToEx(hdc,0,rc.bottom,NULL);
				LineTo(hdc,rc.right,0);
			}
			EndPaint(hWnd,&ps);
			return 0;
		case WM_DESTROY:
			PostQuitMessage(0);
			return 0;
		default:
			break;
	}
	return DefWindowProc(hWnd,uMsg,wParam,lParam);
}