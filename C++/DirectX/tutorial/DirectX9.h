#pragma once
#include "stdafx.h"

class Shape;
class DirectX9
{
public:
	DirectX9(HWND hWnd):m_hWnd(hWnd),m_lpDirect3D9(NULL),m_lpDirect3DDevice9(NULL),m_pvb(NULL),m_pShape(NULL){Init();};
	~DirectX9(){Clear();};
public:
	void Init();
	void Render();
	void Clear();
private:
	HWND m_hWnd;
	LPDIRECT3DVERTEXBUFFER9 m_pvb;
	LPDIRECT3D9 m_lpDirect3D9;
	LPDIRECT3DDEVICE9 m_lpDirect3DDevice9;
	Shape* m_pShape;
};

class Shape
{
public:
	Shape(LPDIRECT3DDEVICE9 lpDirect3DDevice9,LPDIRECT3DVERTEXBUFFER9 vb):m_lpDirect3DDevice9(lpDirect3DDevice9),m_vb(vb){};
	~Shape(){};
public:
	void Render(){
		D3DVERTEXBUFFER_DESC desc;
		m_vb->GetDesc(&desc);
		m_lpDirect3DDevice9->SetStreamSource(0,m_vb,0,D3DXGetFVFVertexSize(desc.FVF));
		m_lpDirect3DDevice9->SetFVF(desc.FVF);
		m_lpDirect3DDevice9->DrawPrimitive(D3DPT_TRIANGLELIST,0,1);
	};
public:
	LPDIRECT3DVERTEXBUFFER9 m_vb;
	LPDIRECT3DDEVICE9 m_lpDirect3DDevice9;
};