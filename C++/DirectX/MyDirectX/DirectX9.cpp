#include "DirectX9.h"

LPDIRECT3D9 DirectX9::g_lpDirect3D = NULL;
LPDIRECT3DDEVICE9 DirectX9::g_lpDirect3DDevice = NULL;

#define SAFE_RELEASE(p) if((p) != NULL) (p)->Release();(p) = NULL;

void DirectX9::Init(HWND hWnd)
{
	if(NULL == (g_lpDirect3D = Direct3DCreate9(D3D_SDK_VERSION)))
		exit(-1);
	D3DPRESENT_PARAMETERS d3dpp;
	ZeroMemory(&d3dpp,sizeof(d3dpp));
	d3dpp.Windowed = TRUE;
	d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;
	d3dpp.BackBufferFormat = D3DFMT_UNKNOWN;
	if(FAILED(g_lpDirect3D->CreateDevice(D3DADAPTER_DEFAULT,D3DDEVTYPE_HAL,hWnd,D3DCREATE_SOFTWARE_VERTEXPROCESSING,&d3dpp,&g_lpDirect3DDevice)))
		exit(-1);
}

void DirectX9::Render()
{
	m_dxElem->Render();
}
void DirectX9::ClearUp()
{
	SAFE_RELEASE(g_lpDirect3DDevice);
	SAFE_RELEASE(g_lpDirect3D);
}

void DXElem::Render()
{
	LPDIRECT3DDEVICE9 dev = DirectX9::g_lpDirect3DDevice;
	dev->Clear(0,NULL,D3DCLEAR_TARGET,D3DCOLOR_XRGB(0,0,255),1.0F,0);
	D3DXMATRIX world;
	D3DXMatrixIdentity(&world);
	dev->SetTransform(D3DTS_WORLD,&world);
	dev->SetTransform(D3DTS_VIEW,&world);
	dev->SetTransform(D3DTS_PROJECTION,&world);
}

DXBall::DXBall()
{
	D3DXCreateBox(DirectX9::g_lpDirect3DDevice,0.5,0.5,0.5,&m_mesh,NULL);
}

void DXBall::Render()
{
	DXElem::Render();
	LPDIRECT3DDEVICE9 dev = DirectX9::g_lpDirect3DDevice;
	dev->Present(NULL,NULL,NULL,NULL);
	dev->BeginScene();
	m_mesh->DrawSubset(0);
	dev->EndScene();
}