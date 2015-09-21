#include "DirectX9.h"

struct CUSTOMVERTEX
{
    FLOAT x, y, z; // The transformed position for the vertex.
    DWORD color;        // The vertex color.
};
#define D3DFVF_CUSTOMVERTEX (D3DFVF_XYZ|D3DFVF_DIFFUSE)

CUSTOMVERTEX vertices[] = {
        { -1.0f,-1.0f, 0.0f, 0xffff0000, },
        {  1.0f,-1.0f, 0.0f, 0xff0000ff, },
        {  0.0f, 1.0f, 0.0f, 0xffffffff, }
};

void DirectX9::Init()
{
	if(NULL == (m_lpDirect3D9 = Direct3DCreate9(D3D_SDK_VERSION)))
		exit(-1);
	D3DPRESENT_PARAMETERS d3dpp;
	ZeroMemory(&d3dpp,sizeof(d3dpp));
	d3dpp.Windowed = TRUE;
	d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;
	d3dpp.BackBufferFormat = D3DFMT_UNKNOWN;
	if(FAILED(m_lpDirect3D9->CreateDevice(D3DADAPTER_DEFAULT,D3DDEVTYPE_HAL,m_hWnd,D3DCREATE_SOFTWARE_VERTEXPROCESSING,&d3dpp,&m_lpDirect3DDevice9)))
		exit(-1);
	m_lpDirect3DDevice9->CreateVertexBuffer(3*sizeof(CUSTOMVERTEX),0,D3DFVF_CUSTOMVERTEX,D3DPOOL_DEFAULT,&m_pvb,NULL);
	void* pVertices; 
	m_pvb->Lock(0,sizeof(vertices),(void**)&pVertices,0);
	memcpy(pVertices,vertices,sizeof(vertices));
	m_pvb->Unlock();
	m_pShape = new Shape(m_lpDirect3DDevice9,m_pvb);
}

void DirectX9::Render()
{
	if(m_lpDirect3DDevice9 == NULL) return;
	m_lpDirect3DDevice9->Clear(0,NULL,D3DCLEAR_TARGET,D3DCOLOR_XRGB(0,0,255),1.0F,0);
	
	m_lpDirect3DDevice9->BeginScene();
	
	// For our world matrix, we will just rotate the object about the y-axis.
    D3DXMATRIXA16 matWorld;

    // Set up the rotation matrix to generate 1 full rotation (2*PI radians) 
    // every 1000 ms. To avoid the loss of precision inherent in very high 
    // floating point numbers, the system time is modulated by the rotation 
    // period before conversion to a radian angle.
    UINT iTime = timeGetTime() % 1000;
    FLOAT fAngle = iTime * ( 2.0f * D3DX_PI ) / 1000.0f;
    D3DXMatrixRotationY( &matWorld, fAngle );
    m_lpDirect3DDevice9->SetTransform( D3DTS_WORLD, &matWorld );

    // Set up our view matrix. A view matrix can be defined given an eye point,
    // a point to lookat, and a direction for which way is up. Here, we set the
    // eye five units back along the z-axis and up three units, look at the
    // origin, and define "up" to be in the y-direction.
    D3DXVECTOR3 vEyePt( 0.0f, 3.0f,-5.0f );
    D3DXVECTOR3 vLookatPt( 0.0f, 0.0f, 0.0f );
    D3DXVECTOR3 vUpVec( 0.0f, 1.0f, 0.0f );
    D3DXMATRIXA16 matView;
    D3DXMatrixLookAtLH( &matView, &vEyePt, &vLookatPt, &vUpVec );
    m_lpDirect3DDevice9->SetTransform( D3DTS_VIEW, &matView );

    // For the projection matrix, we set up a perspective transform (which
    // transforms geometry from 3D view space to 2D viewport space, with
    // a perspective divide making objects smaller in the distance). To build
    // a perpsective transform, we need the field of view (1/4 pi is common),
    // the aspect ratio, and the near and far clipping planes (which define at
    // what distances geometry should be no longer be rendered).
    D3DXMATRIXA16 matProj;
    D3DXMatrixPerspectiveFovLH( &matProj, D3DX_PI / 4, 1.0f, 1.0f, 100.0f );
    m_lpDirect3DDevice9->SetTransform( D3DTS_PROJECTION, &matProj );
	
//	D3DXMATRIX mx;
//	D3DXMatrixIdentity(&mx);
//	D3DXMatrixRotationY(&mx,timeGetTime()/150.0f);
//	m_lpDirect3DDevice9->SetTransform(D3DTS_WORLD,&mx);
	m_pShape->Render();
	m_lpDirect3DDevice9->EndScene();
	m_lpDirect3DDevice9->Present(NULL,NULL,NULL,NULL);
}

void DirectX9::Clear()
{
	if(m_lpDirect3DDevice9 != NULL)
		m_lpDirect3DDevice9->Release();
	if(m_lpDirect3D9 != NULL)
		m_lpDirect3D9->Release();
	if(m_pShape != NULL);
		delete m_pShape;
	m_lpDirect3D9 = NULL;
	m_lpDirect3DDevice9 = NULL;
	m_pShape = NULL;
}
