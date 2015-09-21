#include "DirectX9.h"
//LPDIRECT3D9 g_pd3d = NULL;
//LPDIRECT3DDEVICE9 g_pd3dDevice = NULL;
DirectX9* g_directX9 = NULL;

#define SAFE_RELEASE(p) if((p) == NULL) {(p)->Release();p = NULL;}

//void OnPaint(HWND hWnd)
//{
//	g_pd3dDevice->Clear(0,NULL,D3DCLEAR_TARGET,D3DCOLOR_XRGB(0,0,255),1.0f,0);
//	g_pd3dDevice->BeginScene();
//	g_pd3dDevice->EndScene();
//	g_pd3dDevice->Present(NULL,NULL,NULL,NULL);
//}

//void CleanUp()
//{
//	SAFE_RELEASE(g_pd3d);
//	SAFE_RELEASE(g_pd3dDevice);
//}

LRESULT WINAPI MsgProc(HWND hWnd,UINT uMsg,WPARAM wParam,LPARAM lParam)
{
	switch(uMsg)
	{
		case WM_DESTROY:
			delete g_directX9;
			PostQuitMessage(0);
			break;
		case WM_PAINT:
			g_directX9->Render();
			break;
		default:
			break;
	}
	return DefWindowProc(hWnd,uMsg,wParam,lParam);
}
int WINAPI WinMain(HINSTANCE hInst,HINSTANCE hInstPrev,LPTSTR,int)
{
	WNDCLASSEX wc = {
		sizeof(WNDCLASSEX),CS_CLASSDC,MsgProc,0L,0L,
			GetModuleHandle(NULL),NULL,NULL,NULL,NULL,
			"Test",NULL};
	RegisterClassEx(&wc);
	HWND hWnd = CreateWindow("Test","Test",WS_OVERLAPPEDWINDOW,100,100,300,300,
		GetDesktopWindow(),NULL,wc.hInstance,NULL);
//	if(NULL == (g_pd3d = Direct3DCreate9(D3D_SDK_VERSION)))
//		return E_FAIL;
//	D3DPRESENT_PARAMETERS d3dpp;
//	ZeroMemory(&d3dpp,sizeof(d3dpp));
//	d3dpp.Windowed = TRUE;
//	d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;
//	d3dpp.BackBufferFormat = D3DFMT_UNKNOWN;
//	if(FAILED(g_pd3d->CreateDevice(D3DADAPTER_DEFAULT,D3DDEVTYPE_HAL,hWnd,D3DCREATE_SOFTWARE_VERTEXPROCESSING,&d3dpp,&g_pd3dDevice)))
//		return E_FAIL;
	g_directX9 = new DirectX9(hWnd);
//	g_directX9->Init();
	
	ShowWindow(hWnd,SW_SHOWNORMAL);
	UpdateWindow(hWnd); 
	MSG msg;
	ZeroMemory(&msg,sizeof(msg));
	while(msg.message != WM_QUIT)
	{
		if(PeekMessage(&msg,NULL,0,0,PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		else
			g_directX9->Render();
	}
	return msg.wParam;
}