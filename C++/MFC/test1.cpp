#include <windows.h>
CHAR g_appName[] = "TestWin32";
LRESULT CALLBACK WndProc(HWND hWnd,UINT nMsg,WPARAM wParam,LPARAM lParam);
void ErrorOutput();
int WinMain(HINSTANCE hInst,HINSTANCE hPreInst,LPSTR lpCmd,int iCmdShow)
{
	WNDCLASS wc;
	wc.style = CS_HREDRAW|CS_VREDRAW;
	wc.lpfnWndProc = WndProc;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hInstance = hInst;
	wc.hIcon = LoadIcon(NULL,IDI_APPLICATION);
	wc.hCursor = LoadCursor(NULL,IDC_ARROW);
	wc.hbrBackground = (HBRUSH)COLOR_BACKGROUND;
	wc.lpszMenuName = NULL;
	wc.lpszClassName = g_appName;
	if(!RegisterClass(&wc))//user32.lib
	{
		ErrorOutput();
		return -1;
	}
	HWND hWnd = CreateWindow(g_appName,"Test",WS_OVERLAPPEDWINDOW,
							 CW_USEDEFAULT,CW_USEDEFAULT,CW_USEDEFAULT,CW_USEDEFAULT,
							 NULL,NULL,hInst,NULL);
	if(hWnd == NULL)
	{
		ErrorOutput();
		return -1;
	}
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

LRESULT CALLBACK WndProc(HWND hWnd,UINT nMsg,WPARAM wParam,LPARAM lParam)
{
	switch(nMsg)
	{
		case WM_DESTROY:
			PostQuitMessage(0);
			break;
	}
	return DefWindowProc(hWnd,nMsg,wParam,lParam);
}

void ErrorOutput()
{
	LPVOID lpMsgBuf;
	FormatMessage( 
		FORMAT_MESSAGE_ALLOCATE_BUFFER | 
		FORMAT_MESSAGE_FROM_SYSTEM | 
		FORMAT_MESSAGE_IGNORE_INSERTS,
		NULL,
		GetLastError(),
		0, // Default language
		(LPTSTR) &lpMsgBuf,
		0,
		NULL);

	MessageBox(NULL,(LPCTSTR)lpMsgBuf,"Error",MB_OK);
	LocalFree(lpMsgBuf);
}