#include "stdafx.h"
class OpenGl
{
public:
	OpenGl();
	virtual ~OpenGl();
public:
	BOOL Init(int,int);
	void Render();
	void Destroy();
	BOOL SetPixelFormat(HDC hdc);
	
public:
	HDC m_hdc;
	HGLRC m_hrc;
};