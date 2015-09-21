//--------------------------------------------------------------------------------------
// File: EmptyProject.cpp
//
// Copyright (c) Microsoft Corporation. All rights reserved.
//--------------------------------------------------------------------------------------
#define UNICODE
#include "DXUT.h"

#pragma warning(disable:4006)

/*
全局变量的定义
*/
IDirect3DVertexShader9* basicShader = 0;//顶点着色器
ID3DXConstantTable* basicConstTable = 0;//常量表
D3DXHANDLE wvpMatrixHandle = 0;
D3DXHANDLE colorHandle = 0;
ID3DXMesh* teapot = 0;//茶壶模型

//--------------------------------------------------------------------------------------
// Rejects any D3D9 devices that aren't acceptable to the app by returning false
//--------------------------------------------------------------------------------------
bool CALLBACK IsD3D9DeviceAcceptable( D3DCAPS9* pCaps, D3DFORMAT AdapterFormat, D3DFORMAT BackBufferFormat,
                                      bool bWindowed, void* pUserContext )
{
    // Typically want to skip back buffer formats that don't support alpha blending
    IDirect3D9* pD3D = DXUTGetD3D9Object();
    if( FAILED( pD3D->CheckDeviceFormat( pCaps->AdapterOrdinal, pCaps->DeviceType,
                                         AdapterFormat, D3DUSAGE_QUERY_POSTPIXELSHADER_BLENDING,
                                         D3DRTYPE_TEXTURE, BackBufferFormat ) ) )
        return false;

    return true;
}


//--------------------------------------------------------------------------------------
// Before a device is created, modify the device settings as needed
//--------------------------------------------------------------------------------------
bool CALLBACK ModifyDeviceSettings( DXUTDeviceSettings* pDeviceSettings, void* pUserContext )
{
    return true;
}


//--------------------------------------------------------------------------------------
// Create any D3D9 resources that will live through a device reset (D3DPOOL_MANAGED)
// and aren't tied to the back buffer size
//--------------------------------------------------------------------------------------
HRESULT CALLBACK OnD3D9CreateDevice( IDirect3DDevice9* pd3dDevice, const D3DSURFACE_DESC* pBackBufferSurfaceDesc,
                                     void* pUserContext )
{
	D3DXCreateTeapot(pd3dDevice,&teapot,NULL);
	ID3DXBuffer* shaderBuffer = 0;
	ID3DXBuffer* errorBuffer = 0;
	HRESULT hr = 0;
	if(!SUCCEEDED(hr = D3DXCompileShaderFromFile(
		TEXT("BasicHLSL.fx"),
		0,
		0,
		"SetColor",
		"vs_2_0",
		D3DXSHADER_USE_LEGACY_D3DX9_31_DLL,
		&shaderBuffer,
		&errorBuffer,
		&basicConstTable)))
	{
		MessageBox(NULL,LPCWSTR(errorBuffer->GetBufferPointer()),TEXT("Error"),MB_OK);
		
		SAFE_RELEASE(shaderBuffer);
		SAFE_RELEASE(errorBuffer);
		return -1;
	}
	pd3dDevice->CreateVertexShader((DWORD*)shaderBuffer->GetBufferPointer(),&basicShader);
	wvpMatrixHandle = basicConstTable->GetConstantByName(0,"wvpMatrix");
	colorHandle = basicConstTable->GetConstantByName(0,"color");
	basicConstTable->SetDefaults(pd3dDevice);
	//pd3dDevice->SetVertexShader(basicShader);
	//SAFE_RELEASE(shaderBuffer);
	//SAFE_RELEASE(errorBuffer);
    return S_OK;
}


//--------------------------------------------------------------------------------------
// Create any D3D9 resources that won't live through a device reset (D3DPOOL_DEFAULT) 
// or that are tied to the back buffer size 
//--------------------------------------------------------------------------------------
HRESULT CALLBACK OnD3D9ResetDevice( IDirect3DDevice9* pd3dDevice, const D3DSURFACE_DESC* pBackBufferSurfaceDesc,
                                    void* pUserContext )
{
    return S_OK;
}


//--------------------------------------------------------------------------------------
// Handle updates to the scene.  This is called regardless of which D3D API is used
//--------------------------------------------------------------------------------------
void CALLBACK OnFrameMove( double fTime, float fElapsedTime, void* pUserContext )
{
	LPDIRECT3DDEVICE9 pd3dDevice = DXUTGetD3D9Device();
	D3DXMATRIX matWorld,matView,matProj;
	pd3dDevice->GetTransform(D3DTS_WORLD,&matWorld);
	pd3dDevice->GetTransform(D3DTS_VIEW,&matView);
	pd3dDevice->GetTransform(D3DTS_PROJECTION,&matProj);
	D3DXMatrixScaling(&matWorld,0.5f,0.5f,0.5f);
	D3DXMatrixRotationX(&matView,(timeGetTime() % 1000) * 2 * D3DX_PI / 1000.0f);
	
	D3DXMATRIX matWVP = matWorld * matView * matProj;
	basicConstTable->SetMatrix(pd3dDevice,wvpMatrixHandle,&matWVP);
	D3DXVECTOR4 color(1.0f,1.0f,0.0f,1.0f);
	basicConstTable->SetVector(pd3dDevice,colorHandle,&color);
}


//--------------------------------------------------------------------------------------
// Render the scene using the D3D9 device
//--------------------------------------------------------------------------------------
void CALLBACK OnD3D9FrameRender( IDirect3DDevice9* pd3dDevice, double fTime, float fElapsedTime, void* pUserContext )
{
    HRESULT hr;

    // Clear the render target and the zbuffer 
    V( pd3dDevice->Clear( 0, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, D3DCOLOR_ARGB( 0, 45, 50, 170 ), 1.0f, 0 ) );

    // Render the scene
    if( SUCCEEDED( pd3dDevice->BeginScene() ) )
    {
    	pd3dDevice->SetVertexShader(basicShader);
    	teapot->DrawSubset(0);
        V( pd3dDevice->EndScene() );
    }
    pd3dDevice->Present(NULL,NULL,NULL,NULL);
}


//--------------------------------------------------------------------------------------
// Handle messages to the application 
//--------------------------------------------------------------------------------------
LRESULT CALLBACK MsgProc( HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam,
                          bool* pbNoFurtherProcessing, void* pUserContext )
{
    return 0;
}


//--------------------------------------------------------------------------------------
// Release D3D9 resources created in the OnD3D9ResetDevice callback 
//--------------------------------------------------------------------------------------
void CALLBACK OnD3D9LostDevice( void* pUserContext )
{
}


//--------------------------------------------------------------------------------------
// Release D3D9 resources created in the OnD3D9CreateDevice callback 
//--------------------------------------------------------------------------------------
void CALLBACK OnD3D9DestroyDevice( void* pUserContext )
{
	SAFE_RELEASE(teapot);
	SAFE_RELEASE(basicShader);
	SAFE_RELEASE(basicConstTable);
}


//--------------------------------------------------------------------------------------
// Initialize everything and go into a render loop
//--------------------------------------------------------------------------------------
INT WINAPI wWinMain( HINSTANCE, HINSTANCE, LPWSTR, int )
{
    // Enable run-time memory check for debug builds.
#if defined(DEBUG) | defined(_DEBUG)
    _CrtSetDbgFlag( _CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF );
#endif

    // Set the callback functions
    DXUTSetCallbackD3D9DeviceAcceptable( IsD3D9DeviceAcceptable );
    DXUTSetCallbackD3D9DeviceCreated( OnD3D9CreateDevice );
    DXUTSetCallbackD3D9DeviceReset( OnD3D9ResetDevice );
    DXUTSetCallbackD3D9FrameRender( OnD3D9FrameRender );
    DXUTSetCallbackD3D9DeviceLost( OnD3D9LostDevice );
    DXUTSetCallbackD3D9DeviceDestroyed( OnD3D9DestroyDevice );
    DXUTSetCallbackDeviceChanging( ModifyDeviceSettings );
    DXUTSetCallbackMsgProc( MsgProc );
    DXUTSetCallbackFrameMove( OnFrameMove );

    // TODO: Perform any application-level initialization here

    // Initialize DXUT and create the desired Win32 window and Direct3D device for the application
    DXUTInit( true, true ); // Parse the command line and show msgboxes
    DXUTSetHotkeyHandling( true, true, true );  // handle the default hotkeys
    DXUTSetCursorSettings( true, true ); // Show the cursor and clip it when in full screen
    DXUTCreateWindow( L"EmptyProject" );
    DXUTCreateDevice( true, 640, 480 );

    // Start the render loop
    DXUTMainLoop();

    // TODO: Perform any application-level cleanup here

    return DXUTGetExitCode();
}


