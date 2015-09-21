#include "D3D9.h"
#include "D3DX9.h"

#define D3DXEXPORT  

class DXElem
{
public:
	DXElem(){};
	virtual ~DXElem(){};
public:
	virtual void Render();
};

class DXBall : public DXElem
{
public:
	DXBall();
	~DXBall(){};
	virtual void Render();
private:
	LPD3DXMESH m_mesh;
};

class D3DXEXPORT DirectX9
{
public:
	DirectX9(){};
	~DirectX9(){};
public:
	static void Init(HWND hWnd);
	static void ClearUp();
	void Render();
	void SetElem(DXElem* e){m_dxElem = e;};
public:
	static LPDIRECT3D9 g_lpDirect3D;
	static LPDIRECT3DDEVICE9 g_lpDirect3DDevice;
private:
	DXElem* m_dxElem;
};