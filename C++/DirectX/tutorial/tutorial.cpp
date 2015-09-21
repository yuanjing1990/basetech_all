#include <windows.h>
#include <d3d9.h>
#include <crtdbg.h>
LPDIRECT3D9 g_pd3d = NULL;
LPDIRECT3DDEVICE9 g_pd3dDevice = NULL;
LRESULT CALLBACK MsgProc(HWND,UINT,WPARAM,LPARAM);
int WINAPI WinMain(HINSTANCE hInst,HINSTANCE,LPSTR,INT)
{
	WNDCLASSEX wc = {sizeof(WNDCLASSEX),CS_CLASSDC,MsgProc,0L,0L,
		GetModuleHandle(NULL),NULL,NULL,NULL,NULL,
		"Direct3D Tutorial",NULL};
	RegisterClassEx(&wc);
	HWND hWnd = CreateWindow("Direct3D Tutorial","Direct3D Tutorial 01: CreateDevice",
		WS_OVERLAPPEDWINDOW,100,100,300,300,
		GetDesktopWindow(),NULL,wc.hInstance,NULL);
	_ASSERT(hWnd != NULL);
	if(NULL == ( g_pd3d = Direct3DCreate9(D3D_SDK_VERSION)))
		return E_FAIL;
	
	D3DPRESENT_PARAMETERS d3dpp;
	ZeroMemory(&d3dpp,sizeof(d3dpp));
	d3dpp.Windowed = TRUE;
	d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;
	d3dpp.BackBufferFormat = D3DFMT_UNKNOWN;
	if(FAILED(g_pd3d->CreateDevice(D3DADAPTER_DEFAULT,D3DDEVTYPE_HAL,hWnd,D3DCREATE_SOFTWARE_VERTEXPROCESSING,
		&d3dpp,&g_pd3dDevice)))
		return E_FAIL;
	ShowWindow(hWnd,SW_SHOWNORMAL);
	UpdateWindow(hWnd);
	MSG msg;
	while(GetMessage(&msg,NULL,0,0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	return msg.wParam;
}

void Render()
{
	g_pd3dDevice->Clear(0,NULL,D3DCLEAR_TARGET,D3DCOLOR_XRGB(0,0,255),1.0f,0);
	g_pd3dDevice->BeginScene();
	g_pd3dDevice->EndScene();
	g_pd3dDevice->Present(NULL,NULL,NULL,NULL);
}

void CleanUp()
{
	if(g_pd3dDevice != NULL)
		g_pd3dDevice->Release();
	if(g_pd3d != NULL)
		g_pd3d->Release();
}

LRESULT CALLBACK MsgProc(HWND hWnd,UINT uMsg,WPARAM wParam,LPARAM lParam)
{
	switch(uMsg)
	{
		case WM_DESTROY:
			CleanUp();
			PostQuitMessage(0);
			return 0;
		case WM_PAINT:
			Render();
			ValidateRect(hWnd,NULL);
			return 0;
		
	}
	return DefWindowProc(hWnd,uMsg,wParam,lParam);
}