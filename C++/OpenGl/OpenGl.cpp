#include "OpenGl.h"
#include "math.h"

float r = 0;
OpenGl::OpenGl()
{
}
OpenGl::~OpenGl()
{
	Destroy();
}
BOOL OpenGl::Init(int Width,int Height)
{
	glViewport(0,0,Width,Height);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(54.0f,(GLfloat)Width/(GLfloat)Height,0.1f,1000.0f);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	return TRUE;
}
void OpenGl::Render()
{
	glClearColor(0.0f,0.0f,0.3f,1.0f);
	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();
	
	glPushMatrix(); 
	glPointSize(4);	
	glTranslatef (-5, 4,-13);glRotatef(r,1.0,1.0,1.0);
	glColor3f(1.0f, 0.0f, 0.0f);
	glBegin(GL_QUAD_STRIP);//
	for(int i=0;i<=390;i+=30)
	{
		float p=(float)(i*3.14/180);
		glVertex3f((float)sin(p)/2,(float)cos(p)/2,1.0f );
		glVertex3f((float)sin(p)/2,(float)cos(p)/2,0.0f );
		//glVertex3f((float)cos(p)/2,(float)sin(p)/2,0.0f );
	}
	glEnd();	
	glPopMatrix();
	
	glFlush();
	SwapBuffers(m_hdc);
	r+=1;if(r>360) r=0;
}
void OpenGl::Destroy()
{
	wglMakeCurrent(m_hdc,NULL);
	wglDeleteContext(m_hrc);
}
BOOL OpenGl::SetPixelFormat(HDC hdc)
{
	m_hdc = hdc;
	PIXELFORMATDESCRIPTOR pfd = {
		sizeof(PIXELFORMATDESCRIPTOR),
			1,
			PFD_DRAW_TO_WINDOW|PFD_SUPPORT_OPENGL|PFD_DOUBLEBUFFER,
			PFD_TYPE_RGBA,
			16,
			0,0,0,0,0,0,
			0,
			0,
			0,
			0,0,0,0,
			16,
			0,
			0,
			PFD_MAIN_PLANE,
			0,
			0,0,0
	};
	int nPixelFormat = 0;
	if(!(nPixelFormat = ChoosePixelFormat(hdc,&pfd)))
	{
		MessageBox(NULL,"没有合适的显示模式","Error",MB_OK);
		return FALSE;
	}
	::SetPixelFormat(hdc,nPixelFormat,&pfd);
	m_hrc = wglCreateContext(hdc);
	wglMakeCurrent(hdc,m_hrc);
	return TRUE;
}